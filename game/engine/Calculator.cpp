/*
 * Copyright (C) 2009 AUVOLAT Alex
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

/*	MagicWar 0.1 alpha
 *	by Alexis211
 *  ----------------------------
 *  	Calculator.cpp
 *  	Source code file for Calculator class
 *  	*/

#include "Calculator.h"
#include <engine/functions.h>
#include <iostream>

using namespace std;

#define POP1(name) float name = stack.back(); stack.pop_back();
#define POP2(name1, name2) float name1 = stack.back(); stack.pop_back(); \
			float name2 = stack.back(); stack.pop_back();

float Calculator::calculate(string formula) {	//TODO
	vector<string> tokens = SplitStr(formula);
	vector<float> stack;
	stack.clear();
	for (uint i = 0; i < tokens.size(); i++) {
		string &t = tokens[i];
		if (t == "+") {
			POP2(a, b);
			stack.push_back(a + b);
		} else if (t == "-") {
			POP2(a, b);
			stack.push_back(b - a);
		} else if (t == "*") {
			POP2(a, b);
			stack.push_back(a * b);
		} else if (t == "/") {
			POP2(a, b);
			stack.push_back(b / a);
		} else if (t == "+r") {
			POP2(a, b);
			b += sf::Randomizer::Random(0.f, a);
			stack.push_back(b);
		} else if (t == "Rr") {
			POP2(a, b);
			stack.push_back(sf::Randomizer::Random(a, b));
			stack.push_back(b / a);
		} else if (t == "+R") {
			POP2(a, b);
			b += sf::Randomizer::Random(0.f, (float)((int)a) + 0.999);
			stack.push_back((int)b);
		} else if (t == "RR") {
			POP2(a, b);
			stack.push_back((int)sf::Randomizer::Random((int)a, (float)((int)b) + 0.999));
		} else if (t[0] == '%') {
			stack.push_back(get(t.substr(1)));
		} else {
			stack.push_back(Str2Float(t));
		}
	}
	return stack.back();
}

float Calculator::get(string name) {
	if (m_f.find(name) == m_f.end()) throw Exception(string(_("Unknown variable in calculations : ")) + name, ERROR);
	if (m_f[name].state == F_WIP) {
		throw Exception(string(_("Infinite loop in calculations with ")) + name, ERROR);
		return 0;
	} else if (m_f[name].state == F_UNKNOWN or m_f[name].formula.substr(0, 2) == "@ ") {
		string f = m_f[name].formula;
		if (f.substr(0, 2) == "@ ") f = f.substr(2);
		m_f[name].state = F_WIP;
		m_f[name].value = calculate(f);
		m_f[name].state = F_KNOWN;
	}
	return m_f[name].value;
}

void Calculator::set(string name, string formula) {
	if (m_f.find(name) != m_f.end()) {
		m_f[name].formula = formula;
		m_f[name].state = F_UNKNOWN;
	} else {
		Formula temp = {formula, F_UNKNOWN, 0};
		m_f.insert(make_pair(name, temp));
	}
}

void Calculator::recalculate() {
	map<string, Formula>::iterator it = m_f.begin();
	while (it != m_f.end()) {
		it->second.state = F_UNKNOWN;
		it++;
	}
	it = m_f.begin();
	while (it != m_f.end()) {
		get(it->first);
		it++;
	}
}

void Calculator::combineTo(Calculator& other) {
	map<string, Formula>::iterator it = m_f.begin();
	while (it != m_f.end()) {
		other.set(it->first, it->second.formula);
		it++;
	}
}

void Calculator::copyTo(Calculator& other) {
	other.m_f.clear();
	map<string, Formula>::iterator it = m_f.begin();
	while (it != m_f.end()) {
		other.set(it->first, it->second.formula);
		it++;
	}
}

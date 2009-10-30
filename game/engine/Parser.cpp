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
 *  	Config.cpp
 *  	Code file for singleton class Config
 *  	Config is the class that manages game configuration.
 *  	*/


#include <fstream>
#include <sstream>

#include "Parser.h"
#include "Exception.h"

using namespace std;

Parser Parser::gameCfg;

Parser::Parser() {
}

Parser::~Parser() {
	//Nothing
}

void Parser::loadFromFile(string filename) {
	m_entries.clear();
	setSection();

	ifstream file(filename.c_str(), ios::in);
	if (file) {
		string line;
		while (getline(file, line)) {
			if (line == "" or line[0] == '#') continue;
			if (line[0] == '@') setSection(line.substr(1));
			ConfEntry temp;
			temp.name = m_section + ".";
			bool isvalue = false;
			for (int i = 0; i < line.length(); i++) {
				if (!isvalue) {
					if (line[i] == '=') {
						isvalue = true;
					} else {
						temp.name += line[i];
					}
				} else {
					temp.value += line[i];
				}
			}
			m_entries.push_back(temp);
		}
		file.close();
	} else {
		throw Exception(_("Cannot read from file ") + filename, ERROR);
	}
	setSection();
}

bool Parser::saveToFile(string filename) {
	setSection();
	ofstream file(filename.c_str(), ios::out);
	if (file) {
		for (unsigned int i = 0; i < m_entries.size(); i++) {
			/*
			 * if we are not in the root entry, then just skip entry, since we don't need sections in the main
			 * configuration file, which is the only one we will be using saveToFile for.
			 */
			if (m_entries[i].name[0] == '.') file << m_entries[i].name.substr(1) << "=" << m_entries[i].value << endl;
		}

		file.close();
		return true;
	} else {
		return false;
	}
}

void Parser::setSection(string name) {
	m_section = name;
}

ConfEntry& Parser::findValue(string name) {
	for (unsigned int i = 0; i < m_entries.size(); i++) {
		if (m_entries[i].name == m_section + "." + name) {
			return m_entries[i];
		}
	}
	ConfEntry temp;
	temp.name = m_section + "." + name;
	temp.value = "#UNSET#";
	m_entries.push_back(temp);
	return m_entries.back();
}

int Parser::getValueInt(string name, int defaultval) {
	ConfEntry& e = findValue(name);
	if (e.value == "#UNSET#") setValueInt(name, defaultval);

	int ret;
	stringstream v(e.value);
	v >> ret;
	return ret;
}

float Parser::getValueFloat(string name, float defaultval) {
	ConfEntry& e = findValue(name);
	if (e.value == "#UNSET#") setValueFloat(name, defaultval);

	float ret;
	stringstream v(e.value);
	v >> ret;
	return ret;
}

bool Parser::getValueBool(string name, bool defaultval) {
	ConfEntry& e = findValue(name);
	if (e.value == "#UNSET#") setValueBool(name, defaultval);

	return (e.value == "True");
}

string Parser::getValueString(string name, string defaultval) {
	ConfEntry& e = findValue(name);
	if (e.value == "#UNSET#") e.value = defaultval;
	if (e.value.substr(0, 3) == "_(\"" and e.value.substr(e.value.length() - 2, 2) == "\")") {
		e.value = _(e.value.substr(3, e.value.length() - 5).c_str());
	}

	return e.value;
}

void Parser::setValueInt(string name, int value) {
	ConfEntry& e = findValue(name);
	stringstream v;
	v << value;
	e.value = v.str();
}

void Parser::setValueFloat(string name, float value) {
	ConfEntry& e = findValue(name);
	stringstream v;
	v << value;
	e.value = v.str();
}

void Parser::setValueBool(string name, bool value) {
	ConfEntry& e = findValue(name);
	e.value = (value ? "True" : "False");
}

void Parser::setValueString(string name, string value) {
	ConfEntry& e = findValue(name);
	e.value = value;
}

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
 *  	Calculator.h
 *  	Header file for Calculator class
 *  	This class is used for making calculations (lol)
 *  	*/
#ifndef DEF_MW_CALCULATOR
#define DEF_MW_CALCULATOR

#include <string>
#include <map>
#include <../config.h>
#include <engine/Exception.h>

#define F_KNOWN 2
#define F_WIP 1
#define F_UNKNOWN 0

struct Formula {
	std::string formula;
	int state;
	float value;
};

class Calculator {
	private:
	std::map<std::string, Formula> m_f;

	float calculate(std::string formula);

	public:
	float get(std::string name);
	void set(std::string name, std::string formula);
	void recalculate();	//Recalculates all formulas

	void combineTo(Calculator& other);
	void copyTo(Calculator& other);

	float operator[] (std::string name) { return get(name); }
};

#endif

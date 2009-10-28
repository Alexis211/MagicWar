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
 *  	functions.cpp
 *  	Code file for various functions
 *  	*/

#include <cstdlib>

#include "functions.h"

std::string Int2Str(int i) {
	std::stringstream a;
	a << i;
	return a.str();
}

std::string Float2Str(float f) {
	std::stringstream a;
	a << f;
	return a.str();
}

float Str2Float(std::string s) {
	return atof(s.c_str());
}

int Str2Int(std::string s) {
	return atoi(s.c_str());
}

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
 *  	CLInterface.cpp
 *  	Code for command line interface, main game loop
 *  	*/

#include "CLInterface.h"
#include <iostream>

using namespace std;

void CLInterface::gameMain(Game& g) {
	for (int i = 0; i < g.units().size(); i++) {
		cout << i << ". " << g.units()[i].player().name() << "'s " << g.units()[i].type().m_name << " " <<
			"(" << g.units()[i].pos().x << "," << g.units()[i].pos().y << ") " <<
			g.units()[i].life() << "/" << g.units()[i].characts().maxlife.value << endl;
	}
}

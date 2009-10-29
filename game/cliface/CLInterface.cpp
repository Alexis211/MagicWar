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
 *  	Code for command line interface
 *  	*/

#include "CLInterface.h"
#include <iostream>

using namespace std;

CLInterface::CLInterface(int argc, char *argv[]) {
}

void CLInterface::splashScreen() {
	cout << _("////////////    WELCOME TO MAGICWAR !!!    ////////////") << endl;
	cout << _("This command line interface is a debugging and testing tool, don't use it seriously to play.") << endl;
	cout << _(">> Game is loading data. <<") << endl;
}

void CLInterface::mainMenu() {
}

void CLInterface::credits() {
}

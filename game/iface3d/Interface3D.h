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
 *  	Interface3D.h
 *  	Header file for Interface3D class
 *  	This class is the one managing 3D interface
 *  	*/
#ifndef DEF_MW_IFACE3D_CLASS
#define DEF_MW_IFACE3D_CLASS

#include "../engine/Interface.h"

class Interface3D : public Interface {
	public:
	Interface3D(int argc, char *argv[]);

	void splashScreen();
	void mainMenu();
	void credits(); //This function also destroys interface windows and other stuff

	//Functions that ask something to the user
	Point2D askForSomewhere();
	bool setPositionOf(Unit* unit);
	std::string askForString(std::string question);
};

#endif

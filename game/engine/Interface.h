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
 *  	Interface.h
 *  	Header file for abstract class Interface
 *  	This is the class that manages interaction with the user.
 *  	*/
#ifndef DEF_MW_CLASS_INTERFACE
#define DEF_MW_CLASS_INTERFACE

#include <string>

#include "types.h"
#include "../units/Unit.h"

enum IfaceAskingFor {
	NOTHING,
	POSITION,
	UNIT,
	TEXT
};

class Interface {
	public:
	
	//Functions for different parts of the game
	//These functions are called only once, in main.cpp::main().
	//No constructor needed
	virtual void splashScreen() {}	//This function also loads all data (graphics, etc.)
	virtual void mainMenu() {}
	virtual void credits() {} //This function also destroys interface windows and other stuff

	//Functions that ask something to the user
	virtual Point2D askForSomewhere() {}
	virtual bool setPositionOf(Unit* unit) {}
	virtual std::string askForString(std::string question) {}
	virtual Unit* askForUnit() {}
};

#endif

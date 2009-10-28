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
 *  	Programmer.h
 *  	Header file for class Programmer
 * 		This is a joke class that serves for testing purposes.
 *  	*/
#ifndef DEF_MW_CLASS_PROGRAMMER
#define DEF_MW_CLASS_PROGRAMMER

#include "MovingUnit.h"

class Programmer : public MovingUnit {		//A programmer is no more than a useless moving unit
	private:
	public:
	MW_UNIT
	
	Programmer(Player* player);

	virtual void thread();

	virtual float sight() const;
	
	virtual std::vector<std::string> getPossibleActions() const;
	virtual void doAction(std::string action);   //Does something
};

#endif

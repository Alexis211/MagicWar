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
 *  	CLInterface.h
 *  	Header file for command line interface class
 *  	*/
#ifndef DEF_MW_CLIFACE_CLASS
#define DEF_MW_CLIFACE_CLASS

#include <engine/Interface.h>
#include <engine/game/UnitRepr.h>
#include <engine/game/Game.h>

class CLInterface : public Interface {
	public:
	CLInterface(int argc, char *argv[]);

	void splashScreen();
	void mainMenu();
	void credits(); //This function also destroys interface windows and other stuff

	private:
	void localGame();
	void networkGame();

	void gameMain(Game& g, Player* p);
	
	UnitRepr* reprUnit(Unit* u) { return 0; }
};

#endif

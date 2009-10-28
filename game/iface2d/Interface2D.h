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
 *  	Interface2D.h
 *  	Header file for Interface2D class
 *  	This class is the one managing 2D interface
 *  	*/
#ifndef DEF_MW_IFACE2D_CLASS
#define DEF_MW_IFACE2D_CLASS

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "../engine/Exception.h"
#include "../engine/Interface.h"
#include "../engine/Config.h"

class Interface2D : public Interface {
	private:
	Config* m_config;

	sf::RenderWindow m_app;
	sf::Font m_font;

	public:
	Interface2D(int argc, char *argv[]);	//This function also initializes windows
	void splashScreen();
	void mainMenu();
	void credits(); //This function also destroys interface windows and other stuff

	//All the places of the game
	void localGame();
	void networkGame();
	void gameMain();
};

#endif

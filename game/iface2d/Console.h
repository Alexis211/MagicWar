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
 *  	Console.h
 *  	Header file for the game text console
 *  	*/
#ifndef DEF_MW_CONSOLE
#define DEF_MW_CONSOLE

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <engine/types.h>

#include <deque>
#include <queue>
#include <string>

class Console {
	private:
	std::string m_line;
	std::queue<std::string> m_input;
	std::deque<std::string> m_lines;
	bool m_opened;

	public:
	bool o() { return m_opened; }
	void toggle() { m_opened = (m_opened ? false : true); }
	void display(sf::RenderWindow &app, sf::Font &font);
	void print(std::string wat);
	std::string readline();

	void kp(char c);
	void bksp();
};

#endif

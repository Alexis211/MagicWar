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
#include "Console.h"
#include <iostream>

using namespace std;

#define CONSOLE_HEIGHT 250

#define VSPACE 16

#define PROMPT string("~#MW> ")

void Console::display(sf::RenderWindow &app, sf::Font &font) {
	sf::Shape r = sf::Shape::Rectangle(0, 0, app.GetWidth(), CONSOLE_HEIGHT, sf::Color(128,128,128,100));
	app.Draw(r);
	sf::String text("", font, 16);
	text.SetColor(sf::Color(255,255,255));
	for (uint i = 0; i < m_lines.size(); i++) {
		text.SetText((sf::Unicode::UTF8String)((const unsigned char*)m_lines[i].c_str()));
		app.Draw(text);
		text.Move(0, VSPACE);
	}
	text.SetText(PROMPT + m_line + "_");
	app.Draw(text);
}

void Console::print(string wat) {
	m_lines.push_back(wat);
	while (m_lines.size() > (CONSOLE_HEIGHT / VSPACE) - 1) m_lines.pop_front();
}

string Console::readline() {
	if (!m_input.empty()) {
		std::string r = m_input.front();
		m_input.pop();
		return r;
	}
	return "";
}

void Console::kp(char c) {
	if (c == '\r') {
		if (m_line != "") {
			m_input.push(m_line);
			print(PROMPT + m_line);
			m_line = "";
		} else {
			m_opened = false;
		}
	} else if (c == 8) {
		bksp();
	} else if (c >= ' ') {
		m_line += c;
	}
}

void Console::bksp() {
	if (m_line != "") {
		m_line = m_line.substr(0, m_line.length() - 1);
	}
}


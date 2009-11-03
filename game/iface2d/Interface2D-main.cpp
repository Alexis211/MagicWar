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
 *  	Interface2D-main.cpp
 *  	Code for class Interface2D
 *  	Main loop for the 2D interface
 *  	*/

#include <iostream>
#include <ctime>
#include <fstream>

#include "Interface2D.h"
#include "../../config.h"
#include <engine/functions.h>

#define PRPT m_c.print("~#MW> ")

using namespace std;

UnitRepr* Interface2D::reprUnit(Unit* u) {
	m_repr->push_back(new Repr2D(u, this));
	return m_repr->back();
}

Repr2D* Interface2D::findUnit(int x, int y) {
	for (uint i = 0; i < m_repr->size(); i++) {
		if (m_repr->at(i)->in(x, y)) return m_repr->at(i);
	}
	return 0;
}

//************************************************************************************
//*****************************************		GAME MAIN ROUTINE

void Interface2D::gameMain(Game& g, Player* p) {
	const sf::Input& input = m_app.GetInput();

	m_v.zoom = 20;
	m_v.sx = 0;
	m_v.sy = 0;
	PRPT;
	while (m_app.IsOpened()) {
		m_app.Clear(sf::Color(0, 0, 0));

		sf::Event event;
		while (m_app.GetEvent(event)) {
			if (event.Type == sf::Event::Closed or (event.Type == sf::Event::KeyPressed && event.Key.Code == sf::Key::Escape)) {
				return;
			} else if (event.Type == sf::Event::TextEntered) {
				if (event.Text.Unicode < 0x80) {
					if (m_c.o()) {
						m_c.kp((char)event.Text.Unicode);
					} else {
						if (event.Text.Unicode == '\r') m_c.toggle();
					}
				}
			} else if (event.Type == sf::Event::MouseButtonPressed) {
				if (event.MouseButton.Button == sf::Mouse::Left) {
					Repr2D* e = findUnit(input.GetMouseX(), input.GetMouseY());
					if (e != 0) {
						e->m_selected = (e->m_selected ? false : true);
					} else {
						for (uint i = 0; i < m_repr->size(); i++) m_repr->at(i)->m_selected = false;
					}
				} else if (event.MouseButton.Button == sf::Mouse::Right) {
					Repr2D* e = findUnit(input.GetMouseX(), input.GetMouseY());
					if (e != 0) {
						for (uint i = 0; i < m_repr->size(); i++) {
							Repr2D& r = *(m_repr->at(i));
							if (r.m_selected && (r.u()->player() == p or p == 0)) {
								r.m_u->target(e->u());
							}
						}
					} else {
						for (uint i = 0; i < m_repr->size(); i++) {
							Repr2D& r = *(m_repr->at(i));
							if (r.m_selected && (r.u()->player() == p or p == 0)) {
								r.m_u->goTo(m_v.Pix2Real(input.GetMouseX(), input.GetMouseY()));
							}
						}
					}
				}
			}
		}

		string s;
		while ((s = m_c.readline()) != "") {
			vector<string> cmdline = SplitStr(s);
			if (cmdline[0] == "exit") {
				return;
			} else if (cmdline[0] == "help") {
				m_c.print(_("Help for the game main loop console :"));
				m_c.print(_("- exit"));
				consoleHelp();
			} else {
				consoleExec(cmdline);
			}
			PRPT;
		}

		for (uint i = 0; i < m_repr->size(); i++) {
			m_repr->at(i)->render(m_app, m_font);
		}

		if (m_c.o()) m_c.display(m_app, m_font);
		m_app.Display();
	}
}

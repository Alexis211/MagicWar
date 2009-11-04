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
#include <sstream>

#include "Interface2D.h"
#include "../../config.h"
#include <engine/functions.h>

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
			} else if (event.Type == sf::Event::KeyPressed) {
				if (event.Key.Code == sf::Key::Up) {
					m_v.sy -= 0.5;
					if (m_v.sy < 0) m_v.sy = 0;
				} else if (event.Key.Code == sf::Key::Down) {
					m_v.sy += 0.5;
					if (m_v.sy > g.map().dim().y) m_v.sy = g.map().dim().y;
				} else if (event.Key.Code == sf::Key::Left) {
					m_v.sx -= 0.5;
					if (m_v.sx < 0) m_v.sx = 0;
				} else if (event.Key.Code == sf::Key::Right) {
					m_v.sx += 0.5;
					if (m_v.sx > g.map().dim().x) m_v.sx = g.map().dim().x;
				}
			} else if (event.Type == sf::Event::MouseButtonPressed) {
				if (event.MouseButton.Button == sf::Mouse::Left) {
					Repr2D* e = findUnit(input.GetMouseX(), input.GetMouseY());
					if (e != 0) {
						if (input.IsKeyDown(sf::Key::RShift) == input.IsKeyDown(sf::Key::LShift)) {
							for (uint i = 0; i < m_repr->size(); i++) m_repr->at(i)->m_selected = false;
						}
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
			} else if (cmdline[0] == "produce") {
				if (cmdline.size() == 2) {
					Unit& u = *g.units()[Str2Int(cmdline[1])];
					for (uint i = 0; i < u.canProduce().size(); i++) {
						m_c.print(Int2Str(i) + ". " + u.canProduce()[i]->m_name);
					}
				} else if (cmdline.size() == 3) {
					Unit& u = *g.units()[Str2Int(cmdline[1])];
					uint i = Str2Int(cmdline[2]);
					if ((u.player() == p or p == 0) and i >= 0 and i < u.canProduce().size()) {
						if (u.produce(u.canProduce()[i])) {
							m_c.print(_("Ok"));
						} else {
							m_c.print(_("Not enough money/space."));
						}
					}
				} else {
					m_c.print(_("Usage: produce <unit_id> [<product_id>]"));
				}
			} else {
				consoleExec(cmdline);
			}
		}

		for (uint i = 0; i < m_repr->size(); i++) {
			m_repr->at(i)->render(m_app, m_font);
		}

		stringstream o;
		for (uint i = 0; i < m_repr->size(); i++) {
			Repr2D& r = *(m_repr->at(i));
			if (r.m_selected && (r.u()->player() == p or p == 0)) {
				Unit& u = *r.m_u;
				o << i << ". " << u.player()->name() << "'s " << u.type().m_name << " " <<
					"(" << u.pos().x << "," << u.pos().y << ") " <<
					u.life() << "/" << u.info()["maxlife"] << " P:" << u.info()["disppower"] << " S:" <<
					u.info()["movingspeed"] << " s:" << u.info()["attackspeed"];
				for (unsigned int j = 0; j < u.gotA().size(); j++) {
					o << " " << u.gotA()[j]->m_name;
				}
				o << endl;
			}
		}
		if (p != 0) {
			o << _("Ressources : ") << p->res().gold << _(" units of gold, ") << p->res().wood << _("units of wood") << endl;
		} else {
			o << _("Ressources (gold,wood) : ");
			for (unsigned int i = 0; i < g.players().size(); i++) {
				o << g.players()[i].name() << "(" << g.players()[i].res().gold << "," << g.players()[i].res().wood << ") ";
			}
			o << endl;
		}
		o << _("Playing as : ") << (p == 0 ? _("super user") : p->name()) << endl;
		sf::String text((sf::Unicode::UTF8String)((const unsigned char*)o.str().c_str()), m_font, 16);
		text.Move(10, m_app.GetHeight() - text.GetRect().GetHeight() - 10);
		m_app.Draw(text);

		if (m_c.o()) m_c.display(m_app, m_font);
		m_app.Display();
	}
}

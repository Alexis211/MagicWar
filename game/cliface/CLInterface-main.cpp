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
 *  	Code for command line interface, main game loop
 *  	*/

#include "CLInterface.h"
#include <iostream>

using namespace std;

#define UI(id) g.units()[id]->type().m_name << " (" << g.units()[id]->player()->name() << ") "

void CLInterface::gameMain(Game& g, Player* p) {
	while (1) {
		cout << endl << endl << "******** " << _("PLAYING AS ") << 
			(p == 0 ? _("super user") : p->name()) << " ********" << endl;
		for (unsigned int i = 0; i < g.units().size(); i++) {
			Unit& u = *g.units()[i];
			cout << i << ". " << u.player()->name() << "'s " << u.type().m_name << " " <<
				"(" << u.pos().x << "," << u.pos().y << ") " <<
				u.life() << "/" << u.info()["maxlife"] << " P:" << u.info()["disppower"] << " S:" <<
				u.info()["movingspeed"] << " s:" << u.info()["attackspeed"];
			for (unsigned int j = 0; j < u.gotA().size(); j++) {
				cout << " " << u.gotA()[j]->m_name;
			}
			cout << endl;
		}
		if (p != 0) {
		   	cout << _("Ressources : ") << p->res().gold << _(" units of gold, ") << p->res().wood << _(" units of wood") << endl;
		} else {
			cout << _("Ressources (gold,wood) : ");
			for (unsigned int i = 0; i < g.players().size(); i++) {
				cout << g.players()[i].name() << "(" << g.players()[i].res().gold << "," << g.players()[i].res().wood << ") ";
			}
			cout << endl;
		}
		cout << _(":10 Exit") << endl;
		cout << _(":01 Refresh") << endl;
		cout << _(":2 Make a unit do nothing") << endl;
		cout << _(":3 Make a unit attack another unit") << endl;
		cout << _(":4 Make a unit heal/repair/build another unit") << endl;
		cout << _(":5 Make a unit mine another unit") << endl;
		cout << _(":6 Make a unit harvest another unit") << endl;
		cout << _(":7 Make a unit ameliorate") << endl;
		cout << _(":8 Make a unit build something") << endl;
		cout << _(":9 Make a unit produce something") << endl;
		cout << _("Votre choix : ");
		unsigned int c, n;
		cin >> c;
		if (c == 10) break;
		if (c == 2) {
			cout << _("Enter unit number : ");
			cin >> n;
			if (n >= 0 and n < g.units().size() and (g.units()[n]->player() == p or p == 0)) {
				g.units()[n]->doNothing();
				cout << "==> " << UI(n) << _("does nothing") << endl;
			}
		}
		if (c == 3) {
			cout << _("Enter attacker number : ");
			cin >> n;
			if (n >= 0 and n < g.units().size() and (g.units()[n]->player() == p or p == 0)) {
				unsigned int o;
				cout << _("Enter attacked unit number : ");
				cin >> o;
				if (o >= 0 and o < g.units().size()) {
					g.units()[n]->attack(g.units()[o]);
					cout << "==> " << UI(n) << _("attacks ") << UI(o) << endl;
				}
			}
		}
		if (c == 4) {
			cout << _("Enter healer number : ");
			cin >> n;
			if (n >= 0 and n < g.units().size() and (g.units()[n]->player() == p or p == 0)) {
				unsigned int o;
				cout << _("Enter healed unit number : ");
				cin >> o;
				if (o >= 0 and o < g.units().size()) {
					g.units()[n]->heal(g.units()[o]);
					cout << "==> " << UI(n) << _("heals ") << UI(o) << endl;
				}
			}
		}
		if (c == 5) {
			cout << _("Enter miner number : ");
			cin >> n;
			if (n >= 0 and n < g.units().size() and (g.units()[n]->player() == p or p == 0)) {
				unsigned int o;
				cout << _("Enter mined unit number : ");
				cin >> o;
				if (o >= 0 and o < g.units().size()) {
					g.units()[n]->mine(g.units()[o]);
					cout << "==> " << UI(n) << _("mines gold on ") << UI(o) << endl;
				}
			}
		}
		if (c == 6) {
			cout << _("Enter harvester number : ");
			cin >> n;
			if (n >= 0 and n < g.units().size() and (g.units()[n]->player() == p or p == 0)) {
				unsigned int o;
				cout << _("Enter harvested unit number : ");
				cin >> o;
				if (o >= 0 and o < g.units().size()) {
					g.units()[n]->harvest(g.units()[o]);
					cout << "==> " << UI(n) << _("harvests wood on ") << UI(o) << endl;
				}
			}
		}
		if (c == 7) {
			cout << _("Enter ameliorated unit number : ");
			cin >> n;
			if (n >= 0 and n < g.units().size() and (g.units()[n]->player() == p or p == 0)) {
				cout << _(":0 Cancel") << endl;
				for (unsigned int i = 0; i < g.units()[n]->possibleA().size(); i++) {
					cout << ":" << (i + 1) << " " << g.units()[n]->possibleA()[i]->m_name << " : " 
						<< g.units()[n]->possibleA()[i]->m_description << endl;
				}
				unsigned int o;
				cin >> o;
				if (o > 0 and o <= g.units()[n]->possibleA().size()) {
					if (!g.units()[n]->ameliorate(g.units()[n]->possibleA()[o - 1])) {
						cout << _("Not enough money/space.") << endl;
					} else {
						cout << "==> " << UI(n) << _("ameliorates with ") << g.units()[n]->possibleA()[o - 1]->m_name << endl;
					}
				}
			}
		}
		if (c == 8) {
			cout << _("Enter builder unit number : ");
			cin >> n;
			if (n >= 0 and n < g.units().size() and (g.units()[n]->player() == p or p == 0)) {
				cout << _(":0 Cancel") << endl;
				for (unsigned int i = 0; i < g.units()[n]->canBuild().size(); i++) {
					cout << ":" << (i + 1) << " " << g.units()[n]->canBuild()[i]->m_name << " : " 
						<< g.units()[n]->canBuild()[i]->m_description << endl;
				}
				unsigned int o;
				cin >> o;
				if (o > 0 and o <= g.units()[n]->canBuild().size()) {
					if (!g.units()[n]->build(g.units()[n]->canBuild()[o - 1],
						   	{sf::Randomizer::Random(0.f, 40.f), sf::Randomizer::Random(0.f, 40.f), 0})) {
						cout << _("Not enough money/space.") << endl;
					} else {
						cout << "==> " << UI(n) << _("builds ") << g.units()[n]->canBuild()[o - 1]->m_name << endl;
					}
				}
			}
		}
		if (c == 9) {
			cout << _("Enter producer unit number : ");
			cin >> n;
			if (n >= 0 and n < g.units().size() and (g.units()[n]->player() == p or p == 0)) {
				cout << _(":0 Cancel") << endl;
				for (unsigned int i = 0; i < g.units()[n]->canProduce().size(); i++) {
					cout << ":" << (i + 1) << " " << g.units()[n]->canProduce()[i]->m_name << " : " 
						<< g.units()[n]->canProduce()[i]->m_description << endl;
				}
				unsigned int o;
				cin >> o;
				if (o > 0 and o <= g.units()[n]->canProduce().size()) {
					if (!g.units()[n]->produce(g.units()[n]->canProduce()[o - 1])) {
						cout << _("Not enough money/space.") << endl;
					} else {
						cout << "==> " << UI(n) << _("produces ") << g.units()[n]->canProduce()[o - 1]->m_name << endl;
					}
				}
			}
		}
	}
}

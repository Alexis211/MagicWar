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
 *  	Game.cpp
 *  	Source code file for game class
 *  	*/

#include "Game.h"
#include <iostream>
#include <../config.h>

using namespace std;

Game::Game(Interface* iface)
	: m_initialRessources({100, 100}), m_players(), m_units(), m_thread(*this) {
	m_status = CONFIGURATION;
	m_iface = iface;
	m_players.push_back(Player(0, &Faction::factions[0], _("Nature"), {0, 0}, NETWORK, this)); 
	m_thread.Launch();
}

Game::~Game() {
	m_status = FINISHED;
	while (!m_thread.m_finished) sf::Sleep(0.01);
	for (uint i = 0; i < m_units.size(); i++) {
		delete m_units[i];
	}
}

void Game::setInitialRessources(cost_c res) {
	if (m_players.size() == 1) m_initialRessources = res;	//Only do that if no player is already registered
}

void Game::addPlayer(Faction *faction, std::string name, PlayerType type) {
	if (faction == 0) faction = &Faction::factions[0];
	m_players.push_back(Player(m_players.size(), faction, name, m_initialRessources, type, this));
}

bool Game::setupPlayers() {
	if (!m_map.loaded()) return false;
	Position p = {4, 4, 0};
	for (uint i = 1; i < m_players.size(); i++) {
		if (m_players[i].m_type != NETWORK) {
			vector<UnitType*>& sw = m_players[i].m_faction->m_startsWith;
			for (uint j = 0; j < sw.size(); j++) {
				addUnit(sw[j], &m_players[i], p, true); 
				p.x += 8;
				if (p.x > 40) p.x = 4, p.y += 8;
			}
			m_players[i].recalculateSpace();
		}
	}
	m_status = STARTED;
	return true;
}

Unit* Game::addUnit(UnitType* type, Player* player, Position pos, bool usable) {
	if (player == 0) player = &m_players[0];
	m_units.push_back(new Unit(type, pos, player, m_iface));
	if (usable) {
		m_units.back()->m_life = m_units.back()->info()["maxlife"];
		m_units.back()->m_usable = true;
	}
	player->recalculateSpace();
	return m_units.back();
}

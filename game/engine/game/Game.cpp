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

void Game::setInitialRessources(cost_c res) {
	if (m_players.empty()) m_initialRessources = res;	//Only do that if no player is already registered
}

void Game::addPlayer(Faction faction, std::string name, PlayerType type) {
	m_players.push_back(Player(m_players.size(), faction, name, m_initialRessources, type));
}

void Game::setupPlayers() {
	Position p = {2, 2, 0};
	for (int i = 0; i < m_players.size(); i++) {
		if (m_players[i].m_type != NETWORK) {
			addUnit(&UnitType::unitTypes["apparition"], &m_players[i], p); 
			m_units.back().m_life = m_units.back().characts().maxlife.value;
			p.x += 3;
			if (p.x > 20) p.x = 2, p.y += 3;
			addUnit(&UnitType::unitTypes["ritualcircle"], &m_players[i], p); 
			m_units.back().m_life = m_units.back().characts().maxlife.value;
			p.x += 3;
			p.x += 3;
			if (p.x > 10) p.x = 2, p.y += 3;
		}
	}
}

void Game::addUnit(UnitType* type, Player* player, Position pos) {
	m_units.push_back(Unit(type, pos, player));
}

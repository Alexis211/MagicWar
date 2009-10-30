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
 *  	Player.cpp
 *  	Source code file for player class
 *  	*/

#include "Player.h"
#include <engine/game/Game.h>
#include <engine/game/Unit.h>

using namespace std;

Player::Player(int id, Faction* faction, std::string name, cost_c res, PlayerType type, Game* game) : m_g(game) {
	m_id = id;
	m_faction = faction;
	m_name = name;
	m_space.provided = 0, m_space.occupied = 0;
	m_ressources = res;
	m_type = type;
}

bool Player::canSpend(cost_c res) {
	if (m_ressources.gold > res.gold and m_ressources.wood > res.wood) return true;
	return false;
}

bool Player::spend(cost_c res) {
	if (!canSpend(res)) return false;
	m_ressources.gold -= res.gold, m_ressources.wood -= res.wood;
	return true;
}

bool Player::canAllocateSpace(int qty) {
	return (m_space.occupied + qty <= m_space.provided);
}

void Player::recalculateSpace() {
	m_space.occupied = 0, m_space.provided = 0;
	vector<Unit> &u = m_g->units();	
	for (uint i = 0; i < u.size(); i++) {
		if (u[i].player() == this and !u[i].dead()) {
			m_space.occupied += u[i].characts().space.occupied;
			m_space.provided += u[i].characts().space.provided;
		}
	}
}

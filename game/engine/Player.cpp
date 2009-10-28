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
 *  	Code file for Player class
 *  	Each player has a Player object associated to him, which keeps track of player's possesions
 *  	*/

#include "Player.h"
#include "Game.h"

using namespace std;

Player::Player(string name, int number, int teamnumber) {
	m_game = Game::getInstance();
	m_name = name;
	m_number = number;
	m_teamNumber = teamnumber;
	m_faction = NO_FACTION;
	m_leader = NULL;
	m_type = NETWORK;
}

int Player::getTeamNumber() const {
	return m_teamNumber;
}

void Player::setFaction(Factions faction) {
	m_faction = faction;
}

Factions Player::getFaction() const {
	return m_faction;
}

void Player::setType(PlayerType type) {
	m_type = type;
}

void Player::setLeader(Unit* unit) {
	m_leader = unit;
}

PlayerType Player::getType() const {
	return m_type;
}

string Player::getName() const {
	return m_name;
}

int Player::getNumber() const {
	return m_number;
}

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
 *  	Game.h
 *  	Header file for game class
 *  	*/
#ifndef DEF_MW_GAME
#define DEF_MW_GAME

#include "Player.h"
#include "Unit.h"
#include <vector>

class Game {
	friend class Unit;

	private:
	cost_c m_initialRessources;
	std::vector<Player> m_players;
	std::vector<Unit> m_units;

	void addUnit(UnitType* type, Player* player, Position pos);

	public:
	Game() : m_players(), m_initialRessources({gold: 100, wood: 100}) {}
	~Game() {}

	void setInitialRessources(cost_c res);
	void addPlayer(Faction faction, std::string name, PlayerType type);	
	void setupPlayers();

	const std::vector<Player>& players() { return m_players; }
	std::vector<Unit>& units() { return m_units; }
};

#endif

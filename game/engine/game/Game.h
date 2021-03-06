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
#include <engine/types.h>
#include <vector>
#include "GameThread.h"
#include <engine/Interface.h>
#include "Map.h"

class Game {
	friend class Unit;
	friend class GameThread;
	friend class Map;

	private:
	cost_c m_initialRessources;
	std::vector<Player> m_players;
	std::vector<Unit*> m_units;
	GameThread m_thread;
	GameStatus m_status;
	Interface *m_iface;
	Map m_map;

	Unit* addUnit(UnitType* type, Player* player, Position pos, bool usable = false);

	public:
	Game(Interface* iface);
	~Game();

	void setInitialRessources(cost_c res);
	void addPlayer(Faction *faction, std::string name, PlayerType type);	
	bool setupPlayers();

	std::vector<Player>& players() { return m_players; }
	std::vector<Unit*>& units() { return m_units; }

	Map& map() { return m_map; }
};

#endif

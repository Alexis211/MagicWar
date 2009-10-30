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
 *  	Player.h
 *  	Header file for player class
 *  	*/
#ifndef DEF_MW_PLAYER
#define DEF_MW_PLAYER

#include <string>
#include <engine/characteristics.h>
#include <engine/ressources/Faction.h>

class Player {
	friend class Game;

	private:
	Player(int id, Faction* faction, std::string name, cost_c res, PlayerType type);

	int m_id;
	Faction* m_faction;
	std::string m_name;
	space_c m_space;
	cost_c m_ressources;
	PlayerType m_type;

	public:
	std::string name() const { return m_name; }
	int id() const { return m_id; }
	cost_c res() const { return m_ressources; }

	void receive(cost_c res) { m_ressources += res; }
	bool canSpend(cost_c res);
	bool spend(cost_c res);
};

#endif


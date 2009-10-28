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
 *  	Header file for Player class
 *  	Each player has a Player object associated to him, which keeps track of player's possesions
 *  	*/
#ifndef DEF_MW_PLAYER_CLASS
#define DEF_MW_PLAYER_CLASS

#include <string>
#include "types.h"

class Unit;		//Better than include unit.h
class Game;		//Better than include game.h

class Player {
	private:
	Game* m_game;

	std::string m_name;
	Factions m_faction;
	PlayerType m_type;
	int m_number, m_teamNumber, m_aiLevel;

	int m_gold, m_wood, m_food;

	Unit* m_leader;

	public:
	Player(std::string name, int number, int teamnumber);
	int getTeamNumber() const;
	void setFaction(Factions faction);
	void setType(PlayerType type);
	void setLeader(Unit* unit);
	Factions getFaction() const;
	PlayerType getType() const;

	void startAiThread(int ailevel);
	void aiThread();

	std::string getName() const;
	int getNumber() const;

	bool canTake(int gold, int wood, int food) const;
};

#endif

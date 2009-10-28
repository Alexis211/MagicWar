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
 *  	Header file for Game class
 *  	Game class is the class that keeps a list of units, players and contains the map. It's a singleton.
 *  	*/
#ifndef DEF_MW_GAME_SINGLETON_CLASS
#define DEF_MW_GAME_SINGLETON_CLASS

#include <vector>

#include "singleton.h"
#include "types.h"
#include "Player.h"
#include "../units/Unit.h"
#include "../../config.h"

class Game : public CSingleton<Game> {
	friend class CSingleton<Game>;

	private:
	Game();
	~Game();

	std::vector<Player*> m_players;
	std::vector<Unit*> m_units;

	std::vector<Point2D> m_basesPositions; //Loaded from the map, positions of the bases of all the players
	MapSquare *m_map;
	std::vector<bool*> m_knownMap;
	std::vector<int*> m_visibleMap;  // Each int is the number of units that can see there
	int m_mapWidth, m_mapHeight;

	std::vector<Message> m_messages;

	NetworkStatus m_networkStatus;
	int m_networkClientId;
	std::string m_networkUsername;

	public:
	void initialize();

	bool networkConnect(std::string server, int port, std::string username);
	void networkSendConfig(std::string playername, Factions playerfaction, int playerleader,
	int aiCount, std::vector<std::string> aiNames, std::vector<Factions> aiFactions, std::vector<int> aiLeaders);
	//void networkSendClientMessage(std::string message);		//All these done by calls to networkSend().
	//void networkSendPlayerMessage(int playernumber, std::string message);
	//void networkSendUnitConfig(Unit* unit, std::string config);
	//void networkSendPlayerConfig(Player* player, std::string config);
	bool isNetworkGame() const;
	NetworkStatus networkStatus() const;

	void networkRecvThread();
	void networkSend(std::string data);

	Player* player(int number) const;
	int addPlayer(std::string name, int teamnumber = 0);
	void configurePlayer(int number, Factions faction, int leader, PlayerType type);
	Unit* unit(int number) const;
	void addUnit(Unit* unit);

	const std::vector<Unit*>& units();
	const std::vector<Player*>& players();

	bool loadMap(std::string mapName);
	MapSquare& map(int x, int y) const;
	float mapHeight(float x, float y) const;
	Point2D mapDimensions() const;
	void setupMapKnowledge(int team);
	bool discoverMap(int team, Point2D where, float sight);	//Returns true if new zones discovered (that means the unit's path might need to be recalculated)
	bool mapKnown(int team, int x, int y);
	bool mapVisible(int team, int x, int y);
	bool mapKnown(int team, Point2D where);
	bool mapVisible(int team, Point2D where);
	bool mapWalkable(Point2D where, float radius, int team = 0);
	void mapRegisterStaticUnit(Unit* unit);
	void mapUnregisterStaticUnit(Unit* unit);

	void addMessage(std::string message);
	const std::vector<Message>& messages();
};

#endif

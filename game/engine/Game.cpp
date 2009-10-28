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
 *  	Code file for Game class
 *  	Game class is the class that keeps a list of units, players and contains the map. It's a singleton.
 *  	*/

#include <fstream>
#include <ctime>
#include <cmath>

#include "../../config.h"
#include "Game.h"
#include "../units/Programmer.h"

using namespace std;

Game::Game() {
	m_map = NULL;
	m_networkStatus = NONETWORK;
}

void Game::initialize() {
	m_players.push_back(new Player(_("Nature"), 0, 0));
	m_players.back()->setFaction(NO_FACTION);
	m_players.back()->setType(COMPUTER);
}

Game::~Game() {
	while (!m_players.empty()) {
		delete m_players.back();
		m_players.pop_back();
	}
	while (!m_units.empty()) {
		if (m_units.back() != NULL) delete m_units.back();
		m_units.pop_back();
	}
}

Player* Game::player(int number) const {
	return m_players[number];
}

int Game::addPlayer(string name, int teamnumber) {
	if (teamnumber == 0) teamnumber = m_players.size();
	Player* p = new Player(name, m_players.size(), teamnumber);
	m_players.push_back(p);
	setupMapKnowledge(teamnumber);
	return m_players.size() - 1;
}

void Game::configurePlayer(int number, Factions faction, int leader, PlayerType type) {
	m_players[number]->setFaction(faction);
	m_players[number]->setType(type);
	if (type != NETWORK) {
		//TO BE COMPLETED
		addUnit(new Programmer(m_players[number]));
		m_units.back()->setPosition(m_basesPositions[number]);
		if (type == HUMAN) {
			//TO BE COMPLETED.
		}
	}
	addMessage(m_players[number]->getName() + _(" enters the game"));
}

Unit* Game::unit(int number) const {
	return m_units[number];
}

void Game::addUnit(Unit* unit) {
	//TO BE ADAPTED FOR NETWORKING
	m_units.push_back(unit);
}

const vector<Unit*>& Game::units() {
	return m_units;
}

const vector<Player*>& Game::players() {
	return m_players;
}

//  *********************************************************
//	*	*	*	*	Functions for networking	*	*	*	*
void* startRecvThread(void* data) {
	Game::getInstance()->networkRecvThread();
}

bool Game::networkConnect(string server, int port, string username) {
	//TO BE COMPLETED
}

void Game::networkSendConfig(string playername, Factions playerfaction, int playerleader, 
		int aicount, vector<string> aiNames, vector<Factions> aiFactions, vector<int> aiLeaders) {
	//TO BE COMPLETED
}

bool Game::isNetworkGame() const {
	return (m_networkStatus != NONETWORK);
}

NetworkStatus Game::networkStatus() const {
	return m_networkStatus;
}

void Game::networkRecvThread() {
	//TO BE COMPLETED
}

void Game::networkSend(string data) {
	//TO BE COMPLETED
}

//  *****************************************************
//	*	*	*	*	Functions for the map	*	*	*	*
bool Game::loadMap(string mapName) {
	addMessage(_("Loading map ") + mapName);
	if (m_map != NULL) delete m_map;
	
	ifstream file(string(string(DATAPATH) + "/maps/" + mapName + ".map").c_str(), ios::in);
	if (!file) {
		addMessage(_("Failed to load map ") + mapName);
		return false;
	} else {
		file >> m_mapWidth;
		file >> m_mapHeight;
		m_map = new MapSquare[(m_mapWidth + 1) * (m_mapHeight + 1)];

		for (int x = 0; x <= m_mapWidth; x++) {
			for (int y = 0; y <= m_mapHeight; y++) {
				MapSquare temp;
				file >> temp.height;
				file >> temp.texture;
				file >> temp.textureVariant;
				file >> temp.walkable;
				float r = x;
				if (y < r)  r = y;
				if ((m_mapWidth - x) < r) r = m_mapWidth - x;
				if ((m_mapHeight - y) < r) r = m_mapHeight - y;
				map(x, y) = temp;
			}
		}

		m_basesPositions.clear();
		Point2D temppt;
		temppt.x = 0;
		temppt.y = 0;
		m_basesPositions.push_back(temppt);

		int nbpts; // Number of base positions included in map

		file >> nbpts;

		for (int i = 0; i < nbpts; i++) {
			file >> temppt.x;
			file >> temppt.y;
			m_basesPositions.push_back(temppt);
		}

		int nbunits, utype;	// Number of decorative units included in map

		file >> nbunits;

		for (int i = 0; i < nbunits; i++) {
			file >> temppt.x;
			file >> temppt.y;
			file >> utype;
			//TO BE COMPLETED
		}
		//TO BE ADAPTED FOR NETWORKING

		file.close();
		return true;
	}
}

MapSquare& Game::map(int x, int y) const {
	return m_map[x * m_mapWidth + y];
}

float Game::mapHeight(float x, float y) const {
	if (x < 0 or y < 0 or x >= m_mapWidth or y >= m_mapHeight) return 0;
	int bx = (int)x, by = (int)y;
	float mx = x - bx, my = y - by;
	float a = (map(x, y).height * (1 - mx)) + (map(x + 1, y).height * mx);
	float b = (map(x, y + 1).height * (1 - mx)) + (map(x + 1, y + 1).height * mx);
	return (a * (1 - my)) + (b * my);
}

Point2D Game::mapDimensions() const {
	Point2D ret;
	ret.x = m_mapWidth;
	ret.y = m_mapHeight;
	return ret;
}

void Game::setupMapKnowledge(int team) {
	while (m_knownMap.size() < team) {
		m_knownMap.push_back(NULL);
		m_visibleMap.push_back(NULL);
	}
	if (m_knownMap[team - 1] == NULL) {
		m_knownMap[team - 1] = new bool[(m_mapWidth + 1) * (m_mapHeight + 1)];
		for (int i = 0; i < m_mapWidth * m_mapHeight; i++) {
			m_knownMap[team - 1][i] = true;
		}
	}
	if (m_visibleMap[team - 1] == NULL) {
		m_visibleMap[team - 1] = new int[(m_mapWidth + 1) * (m_mapHeight + 1)];
		for (int i = 0; i < m_mapWidth * m_mapHeight; i++) {
			m_visibleMap[team - 1][i] = 0;
		}
	}
}

bool Game::discoverMap(int team, Point2D where, float sight) {
	bool ret = false;
	int x1 = where.x - sight, y1 = where.y - sight, x2 = where.x + sight, y2 = where.y + sight;
	if (x1 < 0) {
		x1 = 0;
	} else if ((where.x - sight) - (float)x1 > 0.5) {
		x1++;
	}
	if (y1 < 0) {
		y1 = 0;
	} else if ((where.y - sight) - (float)y1 > 0.5) {
		y1++;
	}
	if ((where.x + sight) - (float)x2 > 0.5) x2++;
	if ((where.y + sight) - (float)y2 > 0.5) y2++;
	if (x2 > m_mapWidth) x2 = m_mapWidth;
	if (y2 > m_mapHeight) y2 = m_mapHeight;
	for (int x = x1; x <= x2; x++) {
		for (int y = y1; y < y2; y++) {
			if (!mapKnown(team, x, y)) {
				if (sqrt(pow((float)x - where.x, 2) + pow((float)y - where.y, 2)) <= sight) {
					if (x < 0 or x > m_mapWidth or y < 0 or y > m_mapHeight) {
						//PASS
					} else {
						ret = true;
						m_knownMap[team - 1][x * m_mapWidth + y] = true;
					}
				}
			}
		}
	}
	return ret;
}

bool Game::mapKnown(int team, int x, int y) {
	if (x < 0 or x > m_mapWidth or y < 0 or y > m_mapHeight) return false;
	return m_knownMap[team - 1][x * m_mapWidth + y];
}

bool Game::mapVisible(int team, int x, int y) {
	if (x < 0 or x > m_mapWidth or y < 0 or y > m_mapHeight) return false;
	return m_visibleMap[team - 1][x * m_mapWidth + y] > 0;
}

bool Game::mapKnown(int team, Point2D where) {
	int x = (int)where.x, y = (int)where.y;
	if (where.x - (float)x > 0.5) x++;
	if (where.y - (float)y > 0.5) y++;
	return mapKnown(team, x, y);
}

bool Game::mapVisible(int team, Point2D where) {
	int x = (int)where.x, y = (int)where.y;
	if (where.x - (float)x > 0.5) x++;
	if (where.y - (float)y > 0.5) y++;
	return mapVisible(team, x, y);
}

bool Game::mapWalkable(Point2D where, float radius, int team) {
	if (where.x - radius < 0.0 or where.y - radius < 0.0 or where.x + radius > (float)m_mapWidth or where.y + radius > (float)m_mapHeight) return false;
	if (team != 0 && !mapKnown(team, where)) return true;
	int x = (int)where.x, y = (int)where.y;
	//TO BE ADAPTED FOR PATHFINING
	if (where.x - (float)x > 0.5) x++;
	if (where.y - (float)y > 0.5) y++;
	return map(x, y).walkable and map(x, y).height > -0.5;
}

void Game::mapRegisterStaticUnit(Unit* unit) {
	//TO BE COMPLETED FOR PATHFINDING
}

void Game::mapUnregisterStaticUnit(Unit* unit) {
	//TO BE COMPLETED FOR PATHFINDING
}

//  *********************************************************
//	*	*	*	*	*	Functions for messages	*	*	*	*
void Game::addMessage(string message) {
	Message temp;
	temp.time = time(0);
	temp.msg = message;
	m_messages.push_back(temp);
}

const vector<Message>& Game::messages() {
	while (!m_messages.empty() && m_messages.front().time < time(0) - 7) {
		for (unsigned int i = 1; i < m_messages.size(); i++) {
			m_messages[i - 1] = m_messages[i];
		}
		m_messages.pop_back();
	}
	return m_messages;
}

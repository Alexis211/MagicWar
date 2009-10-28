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
 *  	types.h
 *  	Definitions for types used everywhere in the game
 *  	*/
#ifndef DEF_MW_TYPES_DEFINITIONS
#define DEF_MW_TYPES_DEFINITIONS

#include <string>

class Point2D {
	public:
	float x, y;
	Point2D() {}
	Point2D(float xx, float yy) : x(xx), y(yy) {}
};

class Point2DInt {
	public:
	int x, y;
	Point2DInt() {}
	Point2DInt(int xx, int yy) : x(xx), y(yy) {}
};

enum PowerType {
	PHYSIC, FIRE, ICE, STORM
};

enum PlayerType {
	HUMAN,	 	//Human player on this computer
	NETWORK,	//Human/AI player on another computer in a network game
   	COMPUTER	//AI player on this computer
};

enum Factions {
	NO_FACTION = 0, FORECASTERS = 1, DRUIDS = 2, PRIESTS = 3, MYSTICALS = 4
};

enum NetworkStatus {
	NONETWORK,	//Game is not a network game
    CONFIGURATION,  //Game is waiting for local user to configure the client
   	WAITING,		//Game is waiting for other players to configure their clients
	PLAYING			//Game started
};

enum UnitType {
	ABSTRACT,	//For abstract classes
	MOVING,		//For moving units. Not visible on map when players don't have an unit seeing there
	STATIC,		//For buildings on trees. Visible on map when map revealed to player
	OTHER		//Don't use this
};

enum MoveLayer {
	NO_MOVE_LAYER,		//Unit doesn't move
	WATER,
	GROUND,
	AIR
};

struct MapSquare {
	float height;
	float unitMaxRadius;		//Used for pathfinding
	int texture;
	int textureVariant;
	bool walkable;
};

struct Message {
	int time;
	std::string msg;
};

#endif

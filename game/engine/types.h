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
#include <cmath>
#include <engine/Exception.h>
#include <../config.h>

// GLOBAL TYPES
#define MAX_PLAYERS 8

typedef unsigned int uint;

class Point2D {
	public:
	float x, y;
	Point2D() {}
	Point2D(float xx, float yy) : x(xx), y(yy) {}
	bool operator==(const Point2D& other) const {
		return x == other.x and y == other.y;
	}

	//Vector related methods
	float vecLen() {
		return sqrt(pow(x, 2) + pow(y, 2));
	}
	Point2D vecNormalize() {
		return Point2D(x / vecLen(), y / vecLen());
	}
	Point2D vecOpp() {
		return Point2D(-x, -y);
	}
	Point2D vecAdd(Point2D o) {
		return Point2D(x + o.x, y + o.y);
	}
	Point2D vecMul(float f) {
		return Point2D(x * f, y * f);
	}
};

class Point2DInt {
	public:
	int x, y;
	Point2DInt() {}
	Point2DInt(int xx, int yy) : x(xx), y(yy) {}
	bool operator==(const Point2D& other) const {
		return x == other.x and y == other.y;
	}
};

enum PowerType {
	PHYSIC = 0, FIRE = 1, WATER = 2, STORM = 3, PLANT = 4
};

// PLAYER RELATED TYPES
enum PlayerType {
	HUMAN,	 	//Human player on this computer
	NETWORK,	//Human/AI player on another computer in a network game
   	COMPUTER	//AI player on this computer
};

// GAME RELATED TYPES
enum GameStatus {
	CONFIGURATION,		//Waiting for user to enter game configuration
	STARTED,
	PAUSED,
	FINISHED
};

struct Message {
	int time;
	std::string msg;
};

// UNIT RELATED TYPES
enum UnitAction {
	IDLE, ATTACK, HEAL, MINE, HARVEST, MOVE
};

struct ActionTimer {
	float time, elapsed;
	void set(float t) { time = t; elapsed = 0; }
	int times(float t) {
		int r = 0;
		if (time != 0) {
			elapsed += t;
			r = elapsed / time;
			elapsed -= r * time;
			if (elapsed < 0) throw Exception("CORRECT ME PLZ, Types.h:ActionTimer", ERROR);
		}
		return r;
	}
};

class Unit;
class Amelioration;
struct Action {
	UnitAction what;
	Unit* who;
	Point2D where;
	Amelioration* how;
	ActionTimer timer;
};

// MOVING RELATED TYPES
enum MoveLayer {
	NO_MOVE_LAYER = 0,		//Unit doesn't move
	ML_WATER = 1,
	ML_GROUND = 2,
	ML_AIR = 3
};

struct MapSquare {
	float height, waterHeight;
	float unitMaxRadius;		//Used for pathfinding
	int texture;
	int textureVariant;
	bool walkable;
};

struct Position {
	float x, y, angle;
	Position() {}
	Position(float xx, float yy, float aa) : x(xx), y(yy), angle(aa) {}
};

#endif

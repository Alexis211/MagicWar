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
 *  	characteristics.h
 *  	Header file for characteristics structures
 *  	*/
#ifndef DEF_MW_CHARACTERISTICS
#define DEF_MW_CHARACTERISTICS

#include "types.h"

#include "Parser.h"

#include <string>

struct cost_c {
	int gold;
	int wood;
	void load(Parser& p, std::string prefix) {
		gold = p.getValueInt(prefix + "gold", 0);
		wood = p.getValueInt(prefix + "wood", 0);
	}	
	void operator+= (const cost_c& other) {
		gold += other.gold, wood += other.wood;
	}
};

struct maxlife_c {
	int value;
	int autoheals;	//in life points per second
	void load(Parser& p) {
		value = p.getValueInt("maxlife", 0);
		autoheals = p.getValueInt("autoheals", 0);
	}
	void operator+= (const maxlife_c& other) {
		value += other.value;
		autoheals += other.autoheals;
	}
};

struct power_c {
	int value;
	float speed;	//attacks per second
	float range;	//distance where it can attack (0 = hand to hand)
	PowerType type;
	void load(Parser& p) {
		value = p.getValueInt("power", 0);
		range = p.getValueInt("attackrange", 0);
		speed = p.getValueFloat("attackspeed", 0);
		type = (PowerType)p.getValueInt("attacktype", PHYSIC);
	}
	void operator+= (const power_c& other) {
		value += other.value, speed += other.speed, range += other.range;
	}
};

struct defense_c {
	int main;
	int physic, fire, ice, storm;	//values added to main defense depending on the attack type
	void load(Parser& p) {
		main = p.getValueInt("defense", 0);
		physic = p.getValueInt("defensephysic", 0);
		fire = p.getValueInt("defensefire", 0);
		ice = p.getValueInt("defenseice", 0);
		storm = p.getValueInt("defensestorm", 0);
	}
	void operator+= (const defense_c& other) {
		main += other.main;
		physic += other.physic, fire += other.fire, ice += other.ice, storm += other.storm;
	}
};

struct mobility_c {
	float speed;  //in square units per second
	float radius; //in square units
	float sight;
	MoveLayer layer;
	void load(Parser& p) {
		speed = p.getValueFloat("movingspeed", 0);
		radius = p.getValueFloat("radius", 0);
		sight = p.getValueFloat("sight", 0);
		layer = (MoveLayer)p.getValueInt("layer", NO_MOVE_LAYER);
	}
	void operator+= (const mobility_c& other) {
		speed += other.speed;
		radius += other.radius;
		sight += other.sight;
	}
};

struct space_c {
	int provided;
	int occupied;
	void load(Parser& p) {
		provided = p.getValueInt("spaceprovided", 0);
		occupied = p.getValueInt("spaceoccupied", 0);
	}
	void operator+= (const space_c& other) {
		provided += other.provided;
		occupied += other.occupied;
	}
};

struct unit_c {
	cost_c cost;
	cost_c provides;	//in [gold|wood units] per second if unit is owned by a player, or in maximum [gold|wood units] to be harvested/mined if a player's unit harvests/mines it (meaning the unit belongs to player 0, nature).
	power_c power;
	defense_c defense;
	maxlife_c maxlife;
	cost_c canFetch;	//in [gold|wood units] per 10 seconds
	mobility_c mobility;
	space_c space;
	int buildSpeed;	//In HP per second
	void load(Parser& p) {
		cost.load(p, "cost");
		provides.load(p, "provides");
		power.load(p);
		defense.load(p);
		maxlife.load(p);
		canFetch.load(p, "canfetch");
		mobility.load(p);
		space.load(p);
		buildSpeed = p.getValueInt("buildspeed", 0);
	}
	unit_c& operator+= (const unit_c& other) {
		cost += other.cost;
		provides += other.provides;
		power += other.power;
		defense += other.defense;
		maxlife += other.maxlife;
		canFetch += other.canFetch;
		mobility += other.mobility;
		space += other.space;
		buildSpeed += other.buildSpeed;
	}
};	

#endif

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
 *  	Unit.cpp
 *  	Source code file for unit class
 *  	*/

#include "Unit.h"
#include <engine/Exception.h>
#include <engine/game/Game.h>
#include "UnitRepr.h"
#include <iostream>

using namespace std;

Unit::Unit(UnitType* type, Position pos, Player* player, Interface* iface) 
	:m_canBuild(), m_canProduce(), m_possibleAmeliorations(), m_ameliorations(), m_producing() {
	m_produceTimer.set(0);
	m_player = player;
	m_type = type;
	m_pos = pos;
	recalculateCharacteristics();
	m_life = 0, m_usable = false;
	doNothing();
	m_repr = iface->reprUnit(this);
}

void Unit::recalculateCharacteristics() {
	int lifediff;
	try {
		lifediff = m_info["maxlife"] - m_life;
	} catch (const Exception& e) {
		lifediff = -1;
	}

	m_healTimer.set(0);
	m_provideWTimer.set(0);
	m_provideGTimer.set(0);

	//Take basics characteristics from unit type
	m_type->m_info.copyTo(m_info);
	m_canBuild = m_type->m_canBuild;
	m_canProduce = m_type->m_canProduce;
	//Compute possible ameliorations
	m_possibleAmeliorations.clear();
	std::map<std::string, Amelioration>::iterator it = m_type->m_ameliorations.begin();
	while (it != m_type->m_ameliorations.end()) {
		Amelioration& e = it->second;
		bool possible = true;
		//Check if we don't have it yet
		for (uint j = 0; j < m_ameliorations.size(); j++) {
			if (m_ameliorations[j] == &e) possible = false;
		}
		if (!possible) {
			it++;
			continue;
		}
		//Check for dependencies
		for (uint j = 0; j < e.m_requires.size(); j++) {
			Amelioration* r = e.m_requires[j];
			bool ok = false;
			for (uint k = 0; k < m_ameliorations.size(); k++) {
				if (m_ameliorations[k] == r) {
					ok = true;
					break;
				}
			}
			if (!ok) {
				possible = false;
				break;
			}
		}
		if (possible) {
			m_possibleAmeliorations.push_back(&e);
		}
		it++;
	}
	//Take into account currently possesed ameliorations
	for (uint i = 0; i < m_ameliorations.size(); i++) {
		m_ameliorations[i]->m_info.combineTo(m_info);
		for (uint j = 0; j < m_ameliorations[i]->m_canBuild.size(); j++) {
			m_canBuild.push_back(m_ameliorations[i]->m_canBuild[j]);
		}
		for (uint j = 0; j < m_ameliorations[i]->m_canProduce.size(); j++) {
			m_canProduce.push_back(m_ameliorations[i]->m_canProduce[j]);
		}
	}
	m_info.recalculate();

	m_life = m_info["maxlife"] - lifediff;
	if (lifediff == -1) m_life = 0;

	if (m_info["autoheals"] > 0)
		m_healTimer.set(1.f / (float)m_info["autoheals"]);
	m_providesRes.wood = m_info["provideswood"];
	if (m_player->id() != 0 && m_info["provideswood"] > 0) {
		m_provideWTimer.set(1.f / (float)m_providesRes.wood);
	}
	m_providesRes.gold = m_info["providesgold"];
	if (m_player->id() != 0 && m_info["providesgold"] > 0) {
		m_provideGTimer.set(1.f / (float)m_providesRes.gold);
	}
}


/***************************
 * 					ACTION INITALIZERS
 * 				(functions that tell the unit to do something)
 * 													*********************/

void Unit::doNothing() {
	m_action.what = IDLE;
	m_action.timer.set(0);
}

void Unit::attack(Unit* other) {
	if (other->m_player == m_player) return;
	if (m_info["attackspeed"] == 0) return;
	m_action.what = ATTACK;
	m_action.who = other;
	m_action.timer.set(1.f / (float)m_info["attackspeed"]);
}

void Unit::heal(Unit* other) {
	if (other->m_player != m_player) return;
	if (other->info()["movingspeed"] == 0) {
		if (m_info["buildspeed"] == 0) return;
		m_action.what = HEAL;
		m_action.who = other;
		m_action.timer.set(1.f / m_info["buildspeed"]);
	} else {
		if (m_info["autoheals"] == 0) return;
		m_action.what = HEAL;
		m_action.who = other;
		m_action.timer.set(1.f / m_info["autoheals"]);
	}
}

bool Unit::build(UnitType* t, Position p) {
	for (uint i = 0; i < m_canBuild.size(); i++) {
		if (m_canBuild[i] == t) {
			if (!m_player->spend(t->m_cost)) return false;
			heal(m_player->g().addUnit(t, m_player, p));
			return true;
		}
	}
	return false;
}

bool Unit::produce(UnitType* t) {
	for (uint i = 0; i < m_canProduce.size(); i++) {
		if (m_canProduce[i] == t) {
			if (!m_player->canAllocateSpace(t->m_info["spaceoccupied"])) return false;
			if (!m_player->spend(t->m_cost)) return false;
			Point2D p(sf::Randomizer::Random(-100, 100), sf::Randomizer::Random(-100, 100));
			p = p.vecNormalize().vecMul(m_info["radius"] + t->m_info["radius"]);
			p = p.vecAdd(Point2D(m_pos.x, m_pos.y));
			Unit* u = m_player->g().addUnit(t, m_player, {p.x, p.y, 0});
			m_producing.push_back(ProductionItem({PR_UNIT, {u: u}}));
			return true;
		}
	}
	return false;
}

void Unit::mine(Unit* other) {
	if (other->m_player->id() != 0) return;	//We can only mine nature's possesions
	m_action.what = MINE;
	m_action.who = other;
	m_action.timer.set(1.f / m_info["canfetchgold"]);
}

void Unit::harvest(Unit* other) {
	if (other->m_player->id() != 0) return;	//We can only mine nature's possesions
	m_action.what = HARVEST;
	m_action.who = other;
	m_action.timer.set(1.f / m_info["canfetchwood"]);
}

void Unit::goTo(Point2D position) {
	m_action.what = MOVE;
	m_action.where = position;
	m_action.timer.set(0);
}

bool Unit::ameliorate(Amelioration* how) {
	bool ok = false;
	for (uint i = 0; i < m_possibleAmeliorations.size(); i++) {
		if (m_possibleAmeliorations[i] == how) {
			ok = true;
			break;
		}
	}
	if (!ok) return false;
	if (!m_player->canAllocateSpace(how->m_info["spaceoccupied"])) return false;
	if (!m_player->spend(how->m_cost)) return false;
	ProductionItem i = {PR_AMELIORATE, {a: how}};
	m_producing.push_back(i);
	return true;
}

/**************************
 * 					ACTION RECEIVERS
 * 		(functions called by other units that have an action on this one)
 * 													********************/

int Unit::receiveDamage(Calculator& info, Unit* from) {
	int v = info["power"];
	if (info["powertype"] == PHYSIC) v *= (1 - (m_info["defenseneutral"] / 100));
	if (info["powertype"] == FIRE) v *= (1 - (m_info["defensefire"] / 100));
	if (info["powertype"] == WATER) v *= (1 - (m_info["defensewater"] / 100));
	if (info["powertype"] == STORM) v *= (1 - (m_info["defensestorm"] / 100));
	if (info["powertype"] == PLANT) v *= (1 - (m_info["defenseplant"] / 100));
	if (v > m_life) v = m_life;
	m_life -= v;
	attack(from);
	if (dead() && v != 0) m_player->recalculateSpace();
	return v;
}

int Unit::beHealed(int howMany) {
	if (m_life + howMany > m_info["maxlife"]) howMany = m_info["maxlife"] - m_life;
	m_life += howMany;
	if (m_life == m_info["maxlife"]) {
		m_usable = true;
		m_player->recalculateSpace();
	}
	return howMany;
}

int Unit::getWood(int howMany) {
	if (m_player->id() != 0) return 0;
	if (howMany > m_providesRes.wood) howMany = m_providesRes.wood;
	m_providesRes.wood -= howMany;
	return howMany;
}

int Unit::getGold(int howMany) {
	if (m_player->id() != 0) return 0;
	if (howMany > m_providesRes.gold) howMany = m_providesRes.gold;
	m_providesRes.gold -= howMany;
	return howMany;
}

/**************************
 *					ACTION LOOP
 *				(called by game thread regularly)
 *													********************/

void Unit::doAction(float time) {
	if (dead()) doNothing();		//If we are dead or unusable, do nothing
	//Calculate how many times action should have been done in the elapsed time
	int times = m_action.timer.times(time);
	//Do action
	if (m_action.what == ATTACK) {
		for (int i = 0; i < times; i++) {
			if (doMove(m_action.who, true, time)) {
				if (m_action.who->receiveDamage(m_info, this) == 0) {
					doNothing();
					if (m_action.who->m_player->id() == 0 and m_action.who->m_providesRes.wood > 0) harvest(m_action.who);
					if (m_action.who->m_player->id() == 0 and m_action.who->m_providesRes.gold > 0) mine(m_action.who);
				}
			}
		}
	} else if (m_action.what == HEAL) {
		if (doMove(m_action.who, false, time)) {
			if (m_action.who->beHealed(times) < times) doNothing();
		}
	} else if (m_action.what == MINE) {
		if (doMove(m_action.who, false, time)) {
			int i = m_action.who->getGold(times);
			m_player->receive({gold: i});
			if (i < times) doNothing();
		}
	} else if (m_action.what == HARVEST) {
		if (doMove(m_action.who, false, time)) {
			int i = m_action.who->getWood(times);
			m_player->receive({gold: 0, wood: i});
			if (i < times) doNothing();
		}
	} else if (m_action.what == MOVE) {
		if (doMove(m_action.where, m_info["movingspeed"] * time * 2, time)) doNothing();
	}

	if (!dead()) {
		times = m_healTimer.times(time);
		if (times > 0) {
			m_life += times;
			if (m_life > m_info["maxlife"]) m_life = m_info["maxlife"];
		}
		times = m_provideGTimer.times(time);
		if (times > 0) m_player->receive({gold: times, wood: 0});
		times = m_provideWTimer.times(time);
		if (times > 0) m_player->receive({gold: 0, wood: times});
	}

	if (!m_producing.empty() && !dead()) {
		if (m_produceTimer.time == 0) {
			if (m_producing.front().type == PR_UNIT) {
				m_produceTimer.set(1.f / (float)m_producing.front().u->m_type->m_productionSpeed);
			} else if (m_producing.front().type == PR_AMELIORATE) {
				m_produceTimer.set(m_producing.front().a->m_time);
			}
		} else {
			times = m_produceTimer.times(time);
			if (times != 0) {
				if (m_producing.front().type == PR_UNIT) {
					int n = m_producing.front().u->beHealed(times);
					if (n != times) {
						m_producing.pop_front();
						m_produceTimer.set(0);
					}
				} else if (m_producing.front().type == PR_AMELIORATE) {
					doAmeliorate(m_producing.front().a);
					m_producing.pop_front();
					m_produceTimer.set(0);
				}
			}
		}
	}
	if (m_repr != 0) m_repr->update(time);
}

////**********************
//				Action loop depends on these.
//										************************
void Unit::doAmeliorate(Amelioration* how) {
	m_ameliorations.push_back(how);
	recalculateCharacteristics();
}

bool Unit::doMove(Point2D pos, float precision, float t) {	//TODO : pathfind
	if (m_info["movingspeed"] == 0) return false;
	m_pos.x = pos.x;
	m_pos.y = pos.y;
	return true;
}

bool Unit::doMove(Unit* unit, bool forAttacking, float t) {
	Point2D vec(unit->m_pos.x - m_pos.x, unit->m_pos.y - m_pos.y);
	vec = vec.vecNormalize().vecOpp();
	Point2D location = Point2D(unit->m_pos.x, unit->m_pos.y);
	location = location.vecAdd(vec.vecMul(unit->info()["radius"] + m_info["radius"]));
	if (forAttacking) location = location.vecAdd(vec.vecMul(info()["attackrange"]));
	return doMove(location, info()["attackrange"] / 2, t);
}

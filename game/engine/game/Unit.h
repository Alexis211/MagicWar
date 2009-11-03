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
 *  	Unit.h
 *  	Header file for unit class
 *  	*/
#ifndef DEF_MW_UNIT
#define DEF_MW_UNIT

#include <engine/ressources/UnitType.h>
#include "Player.h"
#include <deque>
class Game;

#define PR_UNIT 1
#define PR_AMELIORATE 2

class Unit;
struct ProductionItem {
	char type;
	union {
		Unit* u;
		Amelioration* a;
	};
};

class UnitRepr;
class Interface;

class Unit {
	friend class Game;

	private:
	UnitType* m_type;
	UnitRepr* m_repr;

	Calculator m_info;
	std::vector<UnitType*> m_canBuild;
	std::vector<UnitType*> m_canProduce;
	std::vector<Amelioration*> m_possibleAmeliorations;

	Player* m_player;
	int m_life;
	std::vector<Amelioration*> m_ameliorations;
	Position m_pos;
	bool m_usable;	//false when unit is being built/produced
	cost_c m_providesRes;
	Action m_action;	
	ActionTimer m_healTimer, m_provideWTimer, m_provideGTimer, m_produceTimer;
	std::deque<ProductionItem> m_producing;

	Unit(UnitType* type, Position pos, Player* player, Interface* iface);

	//Receive damage, be healed, get gold/wood - this is what another unit can do to this unit
	int receiveDamage(Calculator& info, Unit* from);	//Returns actual dammage, taking defense into account
	int beHealed(int howMany);			//Called when another unit builds/repairs or produces this
	int getWood(int howMany);			//Called when another unit harvests this
	int getGold(int howMany);			//Called when another unit mines this
	
	public:
	void recalculateCharacteristics();
	Calculator &info() { return m_info; }
	const UnitType& type() const { return *m_type; }
	const std::vector<Amelioration*> possibleA() const { return m_possibleAmeliorations; }
	const std::vector<Amelioration*> gotA() const { return m_ameliorations; }
	const std::vector<UnitType*> canBuild() const { return m_canBuild; }
	const std::vector<UnitType*> canProduce() const { return m_canProduce; }
	Player* player() const { return m_player; }
	int life() const { return m_life; }
	Position pos() const { return m_pos; }
	bool dead() const {
		return (!m_usable or m_life == 0);
	}

	void doAction(float time);	//Called by the game thread.
	void doAmeliorate(Amelioration* how);
	bool doMove(Point2D pos, float precision, float t);	//Called by doAction when unit goes somewhere (true when arrived)
	bool doMove(Unit* unit, bool forAttcking, float t);	//Called by doAction when unit has to go to another unit
	//Start doing something - this is what user/AI could ask the unit to do
	void doNothing();	//Called to put unit in an idle state
	void attack(Unit* other);
	void heal(Unit* other);	//For buildings : repair with buildspeed. For moving units, heal using autoheal factor
	bool build(UnitType* t, Position p);	//False if not enough money
	bool produce(UnitType* t);
	void mine(Unit* other);
	void harvest(Unit* other);
	void goTo(Point2D position);	
	bool ameliorate(Amelioration* how);
};

#endif

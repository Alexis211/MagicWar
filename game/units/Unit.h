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
 *  	Header file for abstract class Unit
 *  	Unit is the abstract mother class of all unit classes.
 *  	*/
#ifndef DEF_MW_CLASS_UNIT
#define DEF_MW_CLASS_UNIT

#define MW_UNIT static int typeIdentifier(); \
	static std::string name(); \
	static std::string description(); \
	static UnitType unitType(); \
	static MoveLayer moveLayer(); \
	static float radius(); \
	virtual int getTypeIdentifier() { return typeIdentifier(); } \
	virtual std::string getName() { return name(); } \
	virtual std::string getDescription() { return description(); } \
	virtual UnitType getUnitType() { return unitType(); } \
	virtual MoveLayer getMoveLayer() { return moveLayer(); } \
	virtual float getRadius() { return radius(); }

#include <vector>
#include <string>

#include "../engine/types.h"
#include "../engine/Player.h"

class Game;	//better than include game.h

class Unit {
	protected:
	Game* m_game;
	Player* m_player;
	int m_teamNumber;

	Point2D m_position;
	float m_sight;

	int m_life;
	int m_maxLife;

	PowerType m_attackType;
	int m_power, m_healingPower;
	int m_defensePhysic, m_defenseIce, m_defenseFire, m_defenseStorm;

	bool m_selected;

	public:
	MW_UNIT

	Unit(Player* player);
	virtual ~Unit();

	void setPosition(Point2D position);
	virtual Point2D getPosition(float moveTime = 0);		//set moveTime > 0 when calling from display loop, to update position
	virtual bool isDead() const;
	int getLife() const;
	Player* getPlayer() const;
	int getTeamNumber() const;

	void startThread();
	virtual void thread() = 0;

	virtual float sight() const;

	//Functions called by other units when they attack/heal the unit. Returns quantity of life points added/removed.
	virtual int beAttacked(PowerType type, int value);
	virtual int beHealed(int value);

	virtual std::vector<std::string> getPossibleActions() const = 0;
	virtual bool startAction(std::string action);  //Starts a thread for the action
	virtual void doAction(std::string action) = 0;   //Does something

	void select();		//This just keeps track of which units are selected in the UI
	void deselect();
	bool isSelected() const;

	virtual void target(Unit* otherUnit);
	virtual void target(Point2D where);
};

struct FctInfo {
	Unit* unit;
	std::string fctName;
};

#endif

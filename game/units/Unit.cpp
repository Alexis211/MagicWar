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
 *  	Some code for abstract class Unit
 *  	Unit is the abstract mother class of all unit classes.
 *  	*/

#include <pthread.h>

#include "Unit.h"
#include "../engine/Game.h"

using namespace std;

int Unit::typeIdentifier() {
	return 0;
}

string Unit::name() {
	return _("Unit Root Class");
}

string Unit::description() {
	return _("The class that is the parent of all the different unit classes");
}

UnitType Unit::unitType() {
	return ABSTRACT;
}

MoveLayer Unit::moveLayer() {
	return NO_MOVE_LAYER;
}

float Unit::radius() {
	return 0;
}

Unit::Unit(Player* player) {
	m_game = Game::getInstance();
	m_player = player;
	m_teamNumber = m_player->getTeamNumber();
	m_selected = false;

	//Some default values
	m_life = 0;
	m_maxLife = 0;
	m_attackType = PHYSIC;
	m_power = 0;
	m_healingPower = 0;
	m_defensePhysic = 0;
	m_defenseStorm = 0;
	m_defenseIce = 0;
	m_defenseFire = 0;
	m_sight = 0;
}

Unit::~Unit() {
}

void Unit::setPosition(Point2D position) {
	m_position = position;
}

Point2D Unit::getPosition(float moveTime) {
	return m_position;
}

bool Unit::isDead() const {
	return (m_life == 0 && m_maxLife != 0);
}

int Unit::getLife() const {
	return m_life;
}

Player* Unit::getPlayer() const {
	return m_player;
}

int Unit::getTeamNumber() const {
	return m_teamNumber;
}

void* threadLauncher(void* data) {
	Unit* unit = (Unit*)data;
	unit->thread();
}

void Unit::startThread() {
	if (m_player->getType() == NETWORK) return;
	pthread_t *thread = new pthread_t;
	pthread_create(thread, NULL, threadLauncher, this);
}

float Unit::sight() const {
	return m_sight;
}

int Unit::beAttacked(PowerType type, int value) {
	int initlife = m_life;
	if (type == PHYSIC) {
		m_life -= (value - m_defensePhysic);
	} else if (type == FIRE) {
		m_life -= (value - m_defenseFire);
	} else if (type == ICE) {
		m_life -= (value - m_defenseIce);
	} else if (type == STORM) {
		m_life -= (value - m_defenseStorm);
	}
	if (m_life < 0) m_life = 0;
	return (initlife - m_life);
}

int Unit::beHealed(int value) {
	int initlife = m_life;
	m_life += value;
	if (m_life > m_maxLife) m_life = m_maxLife;
	return (m_life - initlife);
}

void* actionLauncher(void* data) {
	FctInfo* info = (FctInfo*)data;
	info->unit->doAction(info->fctName);
	delete info;
}

bool Unit::startAction(string action) {
	vector<string> actions = getPossibleActions();
	bool doAction = false;
	for (int i = 0; i < actions.size(); i++) {
		if (actions[i] == action) doAction = true;
	}
	if (doAction) {
		FctInfo* info = new FctInfo;
		info->unit = this;
		info->fctName = action;

		pthread_t *actThread = new pthread_t;
		pthread_create(actThread, NULL, actionLauncher, info);
	}
	return doAction;
}

void Unit::select() {
	m_selected = true;
}

void Unit::deselect() {
	m_selected = false;
}

bool Unit::isSelected() const {
	return m_selected;
}

void Unit::target(Unit* other) {
}

void Unit::target(Point2D where) {
}	

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
 *  	Programmer.cpp
 *  	Code file for class Programmer
 * 		This is a joke class that serves for testing purposes.
 *  	*/

#include <SFML/System.hpp>
#include <ctime>

#include "Programmer.h"

using namespace std;

int Programmer::typeIdentifier() {
	return 99;
}

string Programmer::name() {
	return _("Programmer");
}

string Programmer::description() {
	return _("A programmer is stupid and useless. It's only purpose of existence is testing.");
}

UnitType Programmer::unitType() {
	return MOVING;
}

MoveLayer Programmer::moveLayer() {
	return GROUND;
}

float Programmer::radius() {
	return 1.1; //Our programmer is fat.
}

float Programmer::sight() const {
	return 12; //Our programmer can see very far.
}

Programmer::Programmer(Player* player) : MovingUnit(player) {
}

void Programmer::thread() {
	sf::Clock c;
	while (!isDead()) {
		c.Reset();
		movingUnitThreadFunc();
		usleep((0.1 - c.GetElapsedTime()) * 1000000.f);
	}
}

vector<string> Programmer::getPossibleActions() const {
	vector<string> ret;
	return ret;
}

void Programmer::doAction(string action) {
}

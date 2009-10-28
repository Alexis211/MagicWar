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
 *  	MovingUnit.cpp
 *  	Code file for class MovingUnit
 *  	This class implements basic handling of path
 *  	*/

#include "MovingUnit.h"
#include <cmath>

using namespace std;

int MovingUnit::typeIdentifier() {
	return 1;
}

string MovingUnit::name() {
	return _("Moving Unit");
}

string MovingUnit::description() {
	return _("The class handles path and movement");
}

UnitType MovingUnit::unitType() {
	return ABSTRACT;
}

MoveLayer MovingUnit::moveLayer() {
	return NO_MOVE_LAYER;
}

float MovingUnit::radius() {
	return 0;
}

MovingUnit::MovingUnit(Player* player) : Unit(player) {
	m_pathNeedsRecomputing = false;
	m_precPos = Point2D(-1, -1);
}

Point2D MovingUnit::getPosition(float moveTime) {
	if (moveTime == 0) return m_position;
}

void MovingUnit::target(Point2D where) {
	m_path.setDestination(where);
}

void MovingUnit::movingUnitThreadFunc() {
	if (m_sightPoints.empty()) {
		for (int x = -1 - this->sight(); x <= this->sight() + 1; x++) {
			for (int y = -1 - this->sight(); y <= this->sight() + 1; y++) {
				if (sqrt(pow(x, 2) + pow(y, 2)) <= this->sight()) {
					m_sightPoints.push_back(Point2DInt(x, y));
				}
			}
		}
	}
	if (!(m_precPos == m_position)) {
		int ox = m_precPos.x, oy = m_precPos.y;
		int nx = m_position.x, ny = m_position.y;
		//TO BE COMPLETED
	}
	if (m_pathNeedsRecomputing) {
		m_path.compute(getRadius(), m_position, getMoveLayer());
	}
}

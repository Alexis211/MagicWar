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
 *  	Path.cpp
 *  	Code file for class Path
 *  	This class handles pathfinding for each unit.
 *  	*/

#include "Path.h"

Path::Path() {
	m_destination.x = 0;
	m_destination.y = 0;
}

void Path::setUnitTeamNumber(int unitTeamNumber) {
	m_unitTeamNumber = unitTeamNumber;
}

bool Path::compute(float unitRadius, Point2D actualPosition, MoveLayer layer) {
	m_unitRadius = unitRadius;

	if (m_destination.x == 0 and m_destination.y == 0) return false;

	if (layer == AIR) {
		m_path.clear();
		m_path.push_back(actualPosition);
		m_path.push_back(m_destination);
	} else {
		//do something
		m_path.clear();
		m_path.push_back(actualPosition);
		m_path.push_back(m_destination);
	}

	return true;
}

Point2D Path::getNextTarget() {
	Point2D ret = m_path.front();
	m_path.pop_front();
	return ret;
}

void Path::setDestination(Point2D destination) {
}

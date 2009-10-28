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
 *  	Path.h
 *  	Header file for class Path
 *  	This class handles pathfinding for each unit.
 *  	*/
#ifndef DEF_MW_CLASS_PATH
#define DEF_MW_CLASS_PATH

#include <list>

#include "Game.h"

class Path {
	private:
	float m_unitRadius;
	Game* m_game;
	std::list<Point2D> m_path;
	Point2D m_destination;
	int m_unitTeamNumber;

	public:
	Path();
	void setUnitTeamNumber(int unitTeamNumber);
	bool compute(float unitRadius, Point2D actualPosition, MoveLayer layer);		//Returns true if path found
	Point2D getNextTarget();
	void setDestination(Point2D destination);
};

#endif

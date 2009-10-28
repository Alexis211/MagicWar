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
 *  	MovingUnit.h
 *  	Header file for class MovingUnit
 *  	This class implements basic handling of path
 *  	*/
#ifndef DEF_MW_CLASS_MOVINGUNIT
#define DEF_MW_CLASS_MOVINGUNIT

#include "Unit.h"
#include "../engine/Path.h"

class MovingUnit : public Unit {
	protected:
	Path m_path;
	Point2D m_moveTarget;
	Point2D m_precPos;
	std::vector<Point2DInt> m_sightPoints;

	bool m_pathNeedsRecomputing;

	void movingUnitThreadFunc();

	public:
	MW_UNIT

	MovingUnit(Player* player);
	
	virtual void target(Point2D where);
	virtual Point2D getPosition(float moveTime = 0);		//set moveTime > 0 when calling from display loop, to update position
};

#endif

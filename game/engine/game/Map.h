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
 *  	Map.h
 *  	Header file for the map handling class
 *  	*/
#ifndef DEF_MW_MAP
#define DEF_MW_MAP

#include <engine/types.h>
#include <vector>
#include <string>

class Game;

class Map {
	private:
	MapSquare* m_map;
	Point2D m_basesPositions[MAX_PLAYERS];
	uint m_width, m_height;

	public:
	Map();
	bool load(std::string mapname, Game& g);
	bool loaded() { return m_map != 0; }
	Point2D basePos(int id);

	MapSquare &at(uint x, uint y);
	Point2DInt dim() const { return Point2DInt(m_width, m_height); }

	static std::vector<std::string> mapList;
	static void loadList();
};

#endif

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

class Unit {
	friend class Game;

	private:
	UnitType* m_type;

	unit_c m_characteristics;
	std::vector<UnitType*> m_canBuild;
	std::vector<UnitType*> m_canProduce;
	std::vector<Amelioration*> m_possibleAmeliorations;

	Player* m_player;
	int m_life;
	std::vector<Amelioration*> m_ameliorations;
	Position m_pos;
	

	Unit(UnitType* type, Position pos, Player* player);
	
	public:
	void recalculateCharacteristics();
	const unit_c& characts() const { return m_characteristics; }
	const UnitType& type() const { return *m_type; }
	Player& player() const { return *m_player; }
	int life() const { return m_life; }
	Position pos() const { return m_pos; }
};

#endif

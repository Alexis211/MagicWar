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
 *  	Source code file for unit class
 *  	*/

#include "Unit.h"

Unit::Unit(UnitType* type, Position pos, Player* player) 
	: m_canBuild(), m_canProduce(), m_possibleAmeliorations(), m_ameliorations() {
	m_player = player;
	m_type = type;
	m_pos = pos;
	recalculateCharacteristics();
	m_life = 0;
}

void Unit::recalculateCharacteristics() {
	//Take basics characteristics from unit type
	m_characteristics = m_type->m_characteristics;
	m_canBuild = m_type->m_canBuild;
	m_canProduce = m_type->m_canProduce;
	//Compute possible ameliorations
	m_possibleAmeliorations.clear();
	std::map<std::string, Amelioration>::iterator it = m_type->m_ameliorations.begin();
	while (it != m_type->m_ameliorations.end()) {
		Amelioration& e = it->second;
		bool possible = true;
		//Check for dependencies
		for (int j = 0; j < e.m_requires.size(); j++) {
			Amelioration* r = e.m_requires[j];
			bool ok = false;
			for (int k = 0; k < m_ameliorations.size(); k++) {
				if (m_ameliorations[k] == r) {
					ok = true;
					break;
				}
			}
			if (!ok) {
				possible = false;
				break;
			}
		}
		if (possible) {
			m_possibleAmeliorations.push_back(&e);
		}
		it++;
	}
	//Take into account currently possesed ameliorations
	for (int i = 0; i < m_ameliorations.size(); i++) {
		m_characteristics += m_ameliorations[i]->m_characteristics;
		for (int j = 0; j < m_ameliorations[i]->m_canBuild.size(); j++) {
			m_canBuild.push_back(m_ameliorations[i]->m_canBuild[j]);
		}
		for (int j = 0; j < m_ameliorations[i]->m_canProduce.size(); j++) {
			m_canProduce.push_back(m_ameliorations[i]->m_canProduce[j]);
		}
	}
}

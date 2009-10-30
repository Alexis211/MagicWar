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
 *  	Amelioration.cpp
 *  	Source code file for amelioration class
 *  	*/

#include "Amelioration.h"
#include "UnitType.h"
#include <engine/functions.h>

using namespace std;

void Amelioration::load(Parser& p, map<string, Amelioration> other_ameliorations) {
	m_name = p.getValueString("name", "NONAMED UNIT");
	m_description = p.getValueString("description", "NODESCRIPTED UNIT");
	m_characteristics.load(p);

	{
		vector<string> cb = SplitStr(p.getValueString("canbuild", ""));
		for (int i = 0; i < cb.size(); i++) m_canBuild.push_back(&UnitType::unitTypes[cb[i]]);
			}

	{
		vector<string> cp = SplitStr(p.getValueString("canproduce", ""));
		for (int i = 0; i < cp.size(); i++) m_canProduce.push_back(&UnitType::unitTypes[cp[i]]);
	}

	{
		vector<string> r = SplitStr(p.getValueString("requires", ""));
		for (int i = 0; i < r.size(); i++) m_requires.push_back(&other_ameliorations[r[i]]);
	}
}

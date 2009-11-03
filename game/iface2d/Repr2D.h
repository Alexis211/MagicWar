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
 *  	Repr2D.h
 *  	Header file for 2D representation for units
 *  	*/
#ifndef DEF_MW_2DREPR
#define DEF_MW_2DREPR

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <engine/game/UnitRepr.h>

class Interface2D;

class Repr2D : public UnitRepr {
	friend class Interface2D;
	bool m_selected;
	Interface2D* m_i;

	private:
	Repr2D(Unit* u, Interface2D* iface);
	virtual ~Repr2D();
	virtual void update(float time);

	bool in(int x, int y);
	
	void render(sf::RenderWindow &app, sf::Font &font);
};

#endif

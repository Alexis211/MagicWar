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
 *  	Repr2D.cpp
 *  	Code file for 2D representation for units
 *  	*/

#include "Repr2D.h"
#include "Interface2D.h"

#define LIFEBARWIDTH 30

sf::Color playerColor[9] =
	{sf::Color(100, 50, 0),
		sf::Color(0, 0, 255),
		sf::Color(255, 0, 0),
		sf::Color(0, 255, 0),
		sf::Color(0, 255, 255),
		sf::Color(255, 0, 255),
		sf::Color(255, 255, 0),
		sf::Color(255, 255, 255),
		sf::Color(0, 0, 0)};

Repr2D::Repr2D(Unit* u, Interface2D* i) {
	m_u = u;
	m_i = i;
	m_selected = false;
}

Repr2D::~Repr2D() {
}

void Repr2D::update(float time) {
}

bool Repr2D::in(int x, int y) {
	View &v = m_i->m_v;
	int cx = (m_u->pos().x - v.sx) * v.zoom, cy = (m_u->pos().y - v.sy) * v.zoom, r = m_u->info()["radius"] * v.zoom;
	if (((x - cx) * (x - cx)) + ((y - cy) * (y - cy)) <= r * r) return true;
	return false;
}

void Repr2D::render(sf::RenderWindow &app, sf::Font &font) {
	View &v = m_i->m_v;
	Point2DInt pxpos = v.Real2Pix(m_u->pos().x, m_u->pos().y);
	sf::Shape c = sf::Shape::Circle(pxpos.x, pxpos.y, m_u->info()["radius"] * v.zoom,
		   	playerColor[m_u->player()->id()], (m_selected ? 1 : 0), sf::Color(255, 255, 255));
	app.Draw(c);
	if (m_u->dead()) {
		c.SetColor(sf::Color(0, 0, 0, 128));
		app.Draw(c);
	} else {
		sf::Shape r = sf::Shape::Rectangle(pxpos.x - (LIFEBARWIDTH / 2),
			   	pxpos.y - 3, pxpos.x + (LIFEBARWIDTH / 2), pxpos.y + 3, sf::Color(128, 128, 128));
		app.Draw(r);
		float f = (float)m_u->life() / m_u->info()["maxlife"];
		r = sf::Shape::Rectangle(pxpos.x - (LIFEBARWIDTH / 2)
				, pxpos.y - 3, pxpos.x - (LIFEBARWIDTH / 2) + (float)(LIFEBARWIDTH * f), pxpos.y + 3, sf::Color(255, 255, 255));
		app.Draw(r);
	}
}

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
 *  	GameThread.cpp
 *  	Source code file for game thread
 *  	The game thread is the thread that handles what happens in the game : units attacking eachother, building, ...
 *  	*/

#include "GameThread.h"
#include "Game.h"

const float interval = 0.02;	//Minimum time between two loops

void GameThread::Run() {
	sf::Clock c;
	float e = interval;
	while (g.m_status != FINISHED) {
		c.Reset();
		if (g.m_status == STARTED) {
			for (int i = 0; i < g.units().size(); i++) {
				g.units()[i].doAction(e);
			}
		}
		e = c.GetElapsedTime();
		if (e < interval) {
			sf::Sleep(interval - e);
			e = c.GetElapsedTime();
		}
	}

	m_finished = true;
}

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
 *  	GameThread.h
 *  	Header file for game thread
 *  	The game thread is the thread that handles what happens in the game : units attacking eachother, building, ...
 *  	*/
#ifndef DEF_MW_GAMETHREAD
#define DEF_MW_GAMETHREAD

#include <SFML/System.hpp>
class Game;

class GameThread : public sf::Thread {
	private:
	Game& g;

	virtual void Run();

	public:
	bool m_finished;
	GameThread(Game& game) : g(game), m_finished(false) {}
};

#endif

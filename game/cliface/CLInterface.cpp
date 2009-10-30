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
 *  	CLInterface.cpp
 *  	Code for command line interface
 *  	*/

#include "CLInterface.h"
#include <iostream>

using namespace std;

CLInterface::CLInterface(int argc, char *argv[]) {
}

void CLInterface::splashScreen() {
	cout << _("////////////    WELCOME TO MAGICWAR !!!    ////////////") << endl;
	cout << _("This command line interface is a debugging and testing tool, don't use it seriously to play.") << endl;
	cout << _(">> Game is loading data. <<") << endl;
}

void CLInterface::mainMenu() {
	while (1) {
		cout << _("MagicWar main menu :") << endl
			<< _("0. Quit") << endl
			<< _("1. Local game") << endl
			<< _("2. Network game") << endl
			<< _("Your choice : ");
		int choice;
		cin >> choice;
		if (choice == 0) break;
		if (choice == 1) localGame();
		if (choice == 2) networkGame();
	}
}

void CLInterface::credits() {
	cout << _("KTHXBYE!") << endl
		<< _("MagicWar was created by the people listed in the --about screen.") << endl;
}

/*******************
 * 			GAME CONFIGURATION SCREENS
 *			 					************************/

void CLInterface::localGame() {
	Game g;

	int nbplayers;
	cout << _("How many players do you want ? (0 = exit) ");
	cin >> nbplayers;
	if (nbplayers == 0) return;

	cost_c initres;
	cout << _("Initial gold for each player : ");
	cin >> initres.gold;
	cout << _("Initial wood for each player : ");
	cin >> initres.wood;
	g.setInitialRessources(initres);

	for (int i = 0; i < nbplayers; i++) {
		cout << _("*** Configuration for player ") << i << endl;
		if (i == 0) cout << _("This player will be you!") << endl;
		cout << _("Enter player name : ");
		string name;
		cin >> name;
		cout << _("Enter player faction : ");
		uint f;
		cin >> f;
		if (f < 0 or f >= Faction::factions.size()) f = 0;
		g.addPlayer(&Faction::factions[f], name, (i == 0 ? HUMAN : COMPUTER));
	}
	cout << _("Play in superuser mode (1 = yes, other = no) ? ");
	int su;
	cin >> su;

	cout << _("Ok, starting game !") << endl;
	g.setupPlayers();
	gameMain(g, (su == 1 ? 0 : &g.players()[1]));
}

void CLInterface::networkGame() {
	cout << _("Not implemented yet.") << endl;
}

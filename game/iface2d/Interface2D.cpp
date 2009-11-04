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
 *  	Interface2D.cpp
 *  	Code for class Interface2D
 *  	This class is the one for the 2D interface to the game
 *  	*/

#include <iostream>
#include <ctime>
#include <fstream>

#include "Interface2D.h"
#include "../../config.h"
#include <engine/functions.h>

using namespace std;

Interface2D::Interface2D(int argc, char *argv[]) {
	if (m_c.o()) m_c.toggle();
	m_repr = 0;
	m_c.print(_("Welcome to the MagicWar game console ! Type 'help' for... help. duh."));
}

//********************************************************************************************
//***********************		SPLASH/CREDITS SCREENS && MAIN MENU    ****

void Interface2D::splashScreen() {
	sf::VideoMode mode(Parser::gameCfg.getValueInt("ScreenWidth", 640),
	   	Parser::gameCfg.getValueInt("ScreenHeight", 480),
	   	Parser::gameCfg.getValueInt("ScreenBPP", 32));
	if (!mode.IsValid()) {
		cerr << _("Invalid video mode. Reverting to best supported.") << endl;
		mode = sf::VideoMode::GetMode(0);
		Parser::gameCfg.setValueInt("ScreenWidth", mode.Width);
		Parser::gameCfg.setValueInt("ScreenHeight", mode.Height);
		Parser::gameCfg.setValueInt("ScreenBPP", mode.BitsPerPixel);
	}
	m_app.Create(mode, _("MagicWar 2D interface main window"),
		(Parser::gameCfg.getValueBool("FullScreen", false) ? sf::Style::Fullscreen : sf::Style::Close));
	m_app.UseVerticalSync(Parser::gameCfg.getValueBool("UseVerticalSync", true));

	if (!m_font.LoadFromFile(string(DATAPATH) + "/arial.ttf")) {
		throw Exception(_("cannot load font (2D interface)"), CRITICAL);
	}

	m_app.Clear(sf::Color(0,0,0));
		
	sf::String text(U_("Welcome to MagicWar. Game engine is currently loading ressources."), m_font, 16);

	text.SetColor(sf::Color(255,255,255));
	text.Move((Parser::gameCfg.getValueInt("ScreenWidth") / 2) - (text.GetRect().GetWidth() / 2), 100);
	m_app.Draw(text);

	m_app.Display();
}

void Interface2D::mainMenu() {
	bool running = true;

	while (running && m_app.IsOpened()) {
		sf::Event event;
		while (m_app.GetEvent(event)) {
			if ((event.Type == sf::Event::Closed) or (event.Type == sf::Event::KeyPressed and event.Key.Code == sf::Key::Escape)) {
				running = false;
			}
			if (event.Type == sf::Event::KeyPressed && !m_c.o()) {
				switch (event.Key.Code) {
					case sf::Key::L:
						localGame();
						break;
					case sf::Key::N:
						networkGame();
						break;
					case sf::Key::Q:
						running = false;
						break;
					default:
						break;
				}
			} else if (event.Type == sf::Event::TextEntered) {
				if (event.Text.Unicode < 0x80) {
					if (m_c.o()) {
						m_c.kp((char)event.Text.Unicode);
					} else {
						if (event.Text.Unicode == '\r') m_c.toggle();
					}
				}
			}
		}

		string s;
		while ((s = m_c.readline()) != "") {
			vector<string> cmdline = SplitStr(s);
			if (cmdline[0] == "exit") {
				return;
			} else if (cmdline[0] == "help") {
				m_c.print(_("- localgame"));
				m_c.print(_("- netgame"));
				m_c.print(_("- exit"));
				consoleHelp();
			} else if (cmdline[0] == "localgame") {
				localGame();
			} else if (cmdline[0] == "netgame") {
				networkGame();
			} else {
				consoleExec(cmdline);
			}
		}

		if (m_repr != 0) {
			for (uint i = 0; i < m_repr->size(); i++) delete m_repr->at(i);
			delete m_repr;
			m_repr = 0;
		}
		
		m_app.Clear(sf::Color(0, 0, 0));

		sf::String text(U_("Hai ! Welcome to MagicWar's main menu.\n\nYour choices are :\nL : Local game\nN : Network game\nQ or Escape : exit"), m_font, 16);

		text.SetColor(sf::Color(255,255,255));
		text.Move((Parser::gameCfg.getValueInt("ScreenWidth") / 2) - (text.GetRect().GetWidth() / 2), 100);
		m_app.Draw(text);

		if (m_c.o()) m_c.display(m_app, m_font);

		m_app.Display();
	}
}

void Interface2D::credits() {
	sf::Clock clock;
	clock.Reset();

	while (clock.GetElapsedTime() < 10 && m_app.IsOpened()) {
		sf::Event event;
		while (m_app.GetEvent(event)) {
			if ((event.Type == sf::Event::Closed) or (event.Type == sf::Event::KeyPressed) or (event.Type == sf::Event::MouseButtonReleased)) {
				m_app.Close();
			}
		}

		m_app.Clear(sf::Color(0, 0, 0));

		sf::String text(U_("Bye, and thanks for playing MagicWar."), m_font, 16);

		text.SetColor(sf::Color(255,255,255));
		text.Move((Parser::gameCfg.getValueInt("ScreenWidth") / 2) - (text.GetRect().GetWidth() / 2), 100);
		m_app.Draw(text);

		m_app.Display();
	}
}

//*********************************************************************
//****************************************		GAME MENUS

void Interface2D::localGame() {
	Game g(this);
	m_repr = new vector<Repr2D*>;

	bool isHuman = true;

	while (m_app.IsOpened()) {
		m_app.Clear(sf::Color(0, 0, 0));

		sf::Event event;
		while (m_app.GetEvent(event)) {
			if (event.Type == sf::Event::Closed or (event.Type == sf::Event::KeyPressed && event.Key.Code == sf::Key::Escape)) {
				return;
			} else if (event.Type == sf::Event::TextEntered) {
				if (event.Text.Unicode < 0x80) {
					if (m_c.o()) {
						m_c.kp((char)event.Text.Unicode);
					} else {
						if (event.Text.Unicode == '\r') m_c.toggle();
					}
				}
			}
		}

		string s;
		while ((s = m_c.readline()) != "") {
			vector<string> cmdline = SplitStr(s);
			if (cmdline[0] == "exit") {
				return;
			} else if (cmdline[0] == "help") {
				m_c.print(_("Help for the local game configuration screen console :"));
				m_c.print(_("- initres <initial_gold> <initial_wood>"));	
				m_c.print(_("- addplayer <name> <faction_id>"));
				m_c.print(_("- start [su]"));
				m_c.print(_("- exit"));
				consoleHelp();
			} else if (cmdline[0] == "initres") {
				if (cmdline.size() != 3) {
					m_c.print(_("Usage: initres <initial_gold> <initial_wood>"));
				} else {
					g.setInitialRessources({gold: Str2Int(cmdline[1]), wood: Str2Int(cmdline[2])});
					m_c.print(_("Ok."));
				}
			} else if (cmdline[0] == "addplayer") {
				if (cmdline.size() != 3) {
					m_c.print(_("Usage: addplayer <name> <faction_id>"));
				} else {
					uint f = Str2Int(cmdline[2]);
					if (f < 0 or f >= Faction::factions.size()) f = 1;
					g.addPlayer(&Faction::factions[f], cmdline[1], (isHuman ? HUMAN : COMPUTER));
					if (isHuman) {
						m_c.print(string(_("Human player added : ")) + cmdline[1]);
					} else {
						m_c.print(string(_("AI player added : ")) + cmdline[1]);
					}
					isHuman = false;
				}
			} else if (cmdline[0] == "start") {
				bool isSu = (cmdline.size() == 2 && cmdline[1] == "su");
				g.setupPlayers();
				gameMain(g, (isSu ? 0 : &g.players()[1]));
				return;
			} else {
				consoleExec(cmdline);
			}
		}

		sf::String text(U_("Please use the console to configure the game (show by pressing return)"), m_font, 16);
		text.SetColor(sf::Color(255,255,255));
		text.Move((Parser::gameCfg.getValueInt("ScreenWidth") / 2) - (text.GetRect().GetWidth() / 2), 300);
		m_app.Draw(text);

		if (m_c.o()) m_c.display(m_app, m_font);

		m_app.Display();
	}
}

void Interface2D::networkGame() {

}

//************************************************************************************
//*****************************************		GAME CONSOLE FUNCTIONS

void Interface2D::consoleExec(vector<string>& cmdline) {
	m_c.print(_("Unknown command..."));
}

void Interface2D::consoleHelp() {
	m_c.print(_("Global help for game console :"));
	m_c.print(_("- nothing exists yet."));
}

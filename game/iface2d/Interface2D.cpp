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

Interface2D::Interface2D(int argc, char *argv[]) {
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
			if (event.Type == sf::Event::KeyPressed) {
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
			}
		}
		
		m_app.Clear(sf::Color(0, 0, 0));

		sf::String text(U_("Hai ! Welcome to MagicWar's main menu.\n\nYour choices are :\nL : Local game\nN : Network game\nQ or Escape : exit"), m_font, 16);

		text.SetColor(sf::Color(255,255,255));
		text.Move((Parser::gameCfg.getValueInt("ScreenWidth") / 2) - (text.GetRect().GetWidth() / 2), 100);
		m_app.Draw(text);

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

}

void Interface2D::networkGame() {

}

//************************************************************************************
//*****************************************		GAME MAIN ROUTINE

void Interface2D::gameMain() {

}


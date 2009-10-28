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
#include "../engine/Game.h"
#include "../engine/functions.h"

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
	m_config = Config::getInstance();
	m_askingFor = NOTHING;
}

//********************************************************************************************
//***********************		SPLASH/CREDITS SCREENS && MAIN MENU    ****

void Interface2D::splashScreen() {
	sf::VideoMode mode(m_config->getValueInt("ScreenWidth", 640),
	   	m_config->getValueInt("ScreenHeight", 480),
	   	m_config->getValueInt("ScreenBPP", 32));
	if (!mode.IsValid()) {
		cerr << _("Invalid video mode. Reverting to best supported.") << endl;
		mode = sf::VideoMode::GetMode(0);
		m_config->setValueInt("ScreenWidth", mode.Width);
		m_config->setValueInt("ScreenHeight", mode.Height);
		m_config->setValueInt("ScreenBPP", mode.BitsPerPixel);
	}
	m_app.Create(mode, _("MagicWar 2D interface main window"),
		(m_config->getValueBool("FullScreen", false) ? sf::Style::Fullscreen : sf::Style::Close));
	m_app.UseVerticalSync(m_config->getValueBool("UseVerticalSync", true));

	sf::Clock clock;
	clock.Reset();

	if (!m_font.LoadFromFile(string(DATAPATH) + "/arial.ttf")) {
		throw Exception(_("cannot load font (2D interface)"), CRITICAL);
	}

	while (clock.GetElapsedTime() < 1) {		//Show splash screen for 3 seconds
		m_app.Clear(sf::Color(0,0,0));
		
		sf::String text(U_("Welcome to MagicWar. This is the crappy 2D interface, used for dev."), m_font, 16);

		text.SetColor(sf::Color(255,255,255));
		text.Move((m_config->getValueInt("ScreenWidth") / 2) - (text.GetRect().GetWidth() / 2), 100);
		m_app.Draw(text);

		m_app.Display();
	}
}

void Interface2D::mainMenu() {
	bool running = true;

	//sf::Unicode::UTF32String entry = sf::Unicode::Text(L"tèst");

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
				}
			}
			//if (event.Type == sf::Event::TextEntered) {
			//	entry += event.Text.Unicode;
			//}
		}
		
		m_app.Clear(sf::Color(0, 0, 0));

		sf::String text(U_("Hai ! Welcome to MagicWar's main menu.\n\nYour choices are :\nL : Local game\nN : Network game\nQ or Escape : exit"), m_font, 16);

		text.SetColor(sf::Color(255,255,255));
		text.Move((m_config->getValueInt("ScreenWidth") / 2) - (text.GetRect().GetWidth() / 2), 100);
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
		text.Move((m_config->getValueInt("ScreenWidth") / 2) - (text.GetRect().GetWidth() / 2), 100);
		m_app.Draw(text);

		m_app.Display();
	}
}

//*********************************************************************
//****************************************		GAME MENUS

void Interface2D::localGame() {
	Game::kill();

	string mapName;

	vector<string> mapList;
	
	ifstream maps((string(DATAPATH) + "/maps/maps.list").c_str());
	if (maps) {
		while (!maps.eof()) {
			getline(maps, mapName);
			mapList.push_back(mapName);
		}
		mapName = "";
	} else {
		throw Exception(_("cannot load map list"), CRITICAL);
	}

	bool running = true, ok = true;
	const sf::Input &input = m_app.GetInput();
	while (running) {
		sf::Event event;
		while (m_app.GetEvent(event)) {
			if (event.Type == sf::Event::Closed or (event.Type == sf::Event::KeyPressed && event.Key.Code == sf::Key::Escape)) {
				running = false;
				ok = false;
			} else if (event.Type == sf::Event::MouseButtonReleased && event.MouseButton.Button == sf::Mouse::Left) {
				int mapId = (input.GetMouseY() - 70) / 20;
				if (mapId >= 0 && mapId < mapList.size()) {
					mapName = mapList[mapId];
					running = false;
				}
			}
		}
		
		m_app.Clear(sf::Color(0, 0, 0));

		sf::String text(U_("Please select a map or press escape to go back to main menu :"), m_font, 16);
		text.Move(30, 30);
		text.SetColor(sf::Color(255, 255, 255));
		m_app.Draw(text);
		text.Move(0, 20);

		for (unsigned int i = 0; i < mapList.size(); i++) {
			text.SetText(mapList[i]);
			if (input.GetMouseY() > i*20+70 && input.GetMouseY() < i*20+90) {
				text.SetColor(sf::Color(0, 255, 255));
			} else {
				text.SetColor(sf::Color(255, 255, 255));
			}
			text.Move(0, 20);
			m_app.Draw(text);
		}

		m_app.Display();
	}
	
	if (ok == false) return;

	string playerName[8];
	PlayerType playerType[8] = {NETWORK, NETWORK, NETWORK, NETWORK, NETWORK, NETWORK, NETWORK, NETWORK};
	Factions playerFaction[8] = {NO_FACTION};
	int playerLeader[8] = {0}, playerTeam[8] = {0};

	playerFaction[0] = FORECASTERS; playerType[0] = HUMAN; playerLeader[0] = 0; playerTeam[0] = 1; playerName[0] = _("Human");
	playerFaction[1] = DRUIDS; playerType[1] = COMPUTER; playerLeader[1] = 0; playerTeam[1] = 2; playerName[1] = _("Computer");

	running = true;
	int playerChangingName = -1;
	while (running) {
		sf::Event event;
		while (m_app.GetEvent(event)) {
			if (event.Type == sf::Event::Closed or (event.Type == sf::Event::KeyPressed && event.Key.Code == sf::Key::Escape)) {
				running = false;
				ok = false;
			} else if (event.Type == sf::Event::MouseButtonReleased) {
				playerChangingName = -1;
				if (input.GetMouseY() > 400) {
					running = false;
					if (input.GetMouseX() < 300) {
						ok = false;
					} else {
						ok = true;
					}
				} else {
					int playerId = (input.GetMouseY() - 90) / 20;
					if (playerId >= 0 && playerId < 8) {
						if (input.GetMouseX() > 30 && input.GetMouseX() < 180) {		//Change name
							playerChangingName = playerId;
						} else if (input.GetMouseX() > 180 && input.GetMouseX() < 280) {	//Change player type
							if (playerType[playerId] == NETWORK) {
								playerType[playerId] = COMPUTER;
								playerName[playerId] = string(_("Computer")) + Int2Str(playerId);
								playerFaction[playerId] = MYSTICALS;
								playerLeader[playerId] = 0;
								playerTeam[playerId] = playerId + 1;
							} else if (playerType[playerId] == COMPUTER) {
								playerType[playerId] = NETWORK;
							}
						} else if (input.GetMouseX() > 280 && input.GetMouseX() < 380) {	//Change player faction
							switch (playerFaction[playerId]) {
								case FORECASTERS:
									playerFaction[playerId] = DRUIDS;
									break;
								case DRUIDS:
									playerFaction[playerId] = PRIESTS;
									break;
								case PRIESTS:
									playerFaction[playerId] = MYSTICALS;
									break;
								case MYSTICALS:
									playerFaction[playerId] = FORECASTERS;
									break;
							}
						} else if (input.GetMouseX() > 380 && input.GetMouseX() < 480) {	//Change player leader
							playerLeader[playerId]++;
							if (playerLeader[playerId] > 2) playerLeader[playerId] = 0;
						} else if (input.GetMouseX() > 480 && input.GetMouseX() < 580) {	//Change player team
							playerTeam[playerId]++;
							if (playerTeam[playerId] > 8) playerTeam[playerId] = 1;
						}
					}
				}
			} else if (event.Type == sf::Event::KeyReleased) {
				if (event.Key.Code == sf::Key::Back && playerChangingName != -1) {
					if (playerName[playerChangingName] != "") playerName[playerChangingName] = playerName[playerChangingName].substr(0, playerName[playerChangingName].size() - 2);
				}
			} else if (event.Type == sf::Event::TextEntered) {
				if (event.Text.Unicode < 0x80 and playerChangingName != -1) {
					if (playerName[playerChangingName].size() < 14) playerName[playerChangingName] += (char)event.Text.Unicode;
				}
			}
		}

		m_app.Clear(sf::Color(0, 0, 0));

		sf::String text(U_("Please configure players :"), m_font, 16);
		text.Move(30, 30);
		text.SetColor(sf::Color(255, 255, 255));
		m_app.Draw(text);

		text.SetText(U_("Name")); text.Move(0, 30); m_app.Draw(text);
		text.SetText(U_("Type")); text.Move(150, 0); m_app.Draw(text);
		text.SetText(U_("Faction")); text.Move(100, 0); m_app.Draw(text);
		text.SetText(U_("Leader")); text.Move(100, 0); m_app.Draw(text);
		text.SetText(U_("Team")); text.Move(100, 0); m_app.Draw(text);

		text.SetText(U_("Back to main menu")); text.SetPosition(40, 420); m_app.Draw(text);
		text.SetText(U_("Start game")); text.SetPosition(440, 420); m_app.Draw(text);

		text.SetColor(sf::Color(200, 255, 200));

		for (unsigned int i = 0; i < 8; i++) {
			text.SetPosition(180, i*20+90);
			if (playerType[i] == NETWORK) {
				text.SetText(U_("Closed"));
				m_app.Draw(text);
			} else {
				if (playerType[i] == COMPUTER) {
					text.SetText(U_("Computer"));
				} else if (playerType[i] == HUMAN) {
					text.SetText(U_("Human"));
				}
				m_app.Draw(text);
				text.SetText(playerName[i] + (playerChangingName == i ? "_" : "")); text.SetPosition(30, i*20+90); m_app.Draw(text);
				switch (playerFaction[i]) {
					case FORECASTERS:
						text.SetText(U_("Forecasters"));
						break;
					case DRUIDS:
						text.SetText(U_("Druids"));
						break;
					case PRIESTS:
						text.SetText(U_("Priests"));
						break;
					case MYSTICALS:
						text.SetText(U_("Mysticals"));
						break;
				}
				text.SetPosition(280, i*20+90); m_app.Draw(text);
				text.SetText(Int2Str(playerLeader[i])); text.SetPosition(380, i*20+90); m_app.Draw(text);
				text.SetText(Int2Str(playerTeam[i])); text.SetPosition(480, i*20+90); m_app.Draw(text);
			}
		}

		m_app.Display();
	}

	if (!ok) return;

	//Setup everything
	Game *game = Game::getInstance();
	game->initialize();

	if (!game->loadMap(mapName)) {
		throw Exception(string(_("Cannot load map : ")) + mapName, ERROR);
	}

	for (int i = 0; i < 8; i++) {
		if (playerType[i] != NETWORK) {
			int j = game->addPlayer(playerName[i], playerTeam[i]);
			game->configurePlayer(j, playerFaction[i], playerLeader[i], playerType[i]);
		}
	}

	gameMain();

	Game::kill();
}

void Interface2D::networkGame() {
	Game::kill();


	Game::kill();
}

//************************************************************************************
//*****************************************		GAME MAIN ROUTINES

void Interface2D::gameMain() {
	Game *game = Game::getInstance();
	bool running = true;

	Player *humanPlayer = NULL;
	for (unsigned int i = 0; i < game->players().size(); i++) {
		if (game->players()[i]->getType() == HUMAN) humanPlayer = game->players()[i];
	}

	int viewStartX = 0, viewStartY = 0, zoom = 16;

	const vector<Unit*> &units = game->units();

	while (running) {
		sf::Event event;
		while (m_app.GetEvent(event)) {
			if (event.Type == sf::Event::Closed or (event.Type == sf::Event::KeyPressed && event.Key.Code == sf::Key::Escape)) {
				running = false;
			}
		}

		m_app.Clear(sf::Color(0, 0, 0));

		for (int x = viewStartX; x < game->mapDimensions().x; x++) {
			for (int y = viewStartY; y < game->mapDimensions().y; y++) {
				if (game->mapKnown(humanPlayer->getTeamNumber(), x, y)) {
					int i = (game->mapVisible(humanPlayer->getTeamNumber(), x, y) ? 100 : 0);
					sf::Color col = (game->map(x, y).height > -0.5 ? (game->map(x, y).walkable ? sf::Color(0, 255, 0, 150 + i) : sf::Color(128, 128, 128, 150 + i)) : sf::Color(0, 0, 255, 150 + i));
					sf::Shape rect = sf::Shape::Rectangle(x, y, x+1, y+1, col);
					rect.Scale(zoom, zoom);
					m_app.Draw(rect);
				}
			}
		}

		for (int i = 0; i < units.size(); i++) {
			if (units[i] != NULL) {
				Point2D pos = units[i]->getPosition();
				cout << units[i]->getTeamNumber() << endl;
				cout << pos.x << " " << pos.y << endl;
				if (units[i]->getTeamNumber() == humanPlayer->getTeamNumber() or
						game->mapVisible(humanPlayer->getTeamNumber(), pos)) {
					sf::Shape circle = sf::Shape::Circle(pos.x + viewStartX, pos.y + viewStartY, units[i]->getRadius(), sf::Color(0, 0, 0), 0.5, playerColor[units[i]->getPlayer()->getNumber()]);
					circle.Scale(zoom, zoom);
					m_app.Draw(circle);
				}
			}
		}
		
		sf::String text("", m_font, 16);
		const vector<Message> &msgs = game->messages();
		for (unsigned int i = 0; i < msgs.size(); i++) {
			text.SetText(msgs[i].msg);
			text.Move(0, 20);
			m_app.Draw(text);
		}

		m_app.Display();
	}
}

//********************************************************************************
//****************************************		Other functions

Point2D Interface2D::askForSomewhere() {
	m_askingFor = POSITION;
	m_posAnswer.x = 0;
	m_posAnswer.y = 0;
	while (m_askingFor == POSITION) {
		usleep(10);
	}
	return m_posAnswer;
}

bool Interface2D::setPositionOf(Unit* unit) {
	m_askingFor = POSITION;
	m_posAnswer.x = 0;
	m_posAnswer.y = 0;
	while (m_askingFor == POSITION) {
		usleep(10);
	}
	if (m_posAnswer.x == 0 && m_posAnswer.y == 0) {
		return false;
	} else {
		unit->setPosition(m_posAnswer);
		return true;
	}
}

string Interface2D::askForString(string question) {
	m_askingFor = TEXT;
	m_stringQuestion = question;
	m_stringAnswer = "";
	while (m_askingFor == TEXT) {
		usleep(10);
	}
	return m_stringAnswer;
}

Unit* Interface2D::askForUnit() {
	m_askingFor = UNIT;
	m_unitAnswer = NULL;
	while (m_askingFor == UNIT) {
		usleep(10);
	}
	return m_unitAnswer;
}

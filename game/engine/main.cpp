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


#include <string>
#include <iostream>

#include "Parser.h"
#include "Calculator.h"

#ifdef WIN32
#include <direct.h>
#else
#include <sys/types.h>
#include <sys/stat.h>
#include <cstdlib>
#endif

#include "Interface.h"
#include "../iface2d/Interface2D.h"
#include "../iface3d/Interface3D.h"
#include "../cliface/CLInterface.h"

#include "ressources/UnitType.h"

using namespace std;

string gameCfgFile() {
	//TO BE ADAPTED ALSO FOR MAC, AND MODIFIED FOR WINDOWS
#ifdef WIN32
	string ret("C:/WINDOWS/magicwar.conf");
#else
	string ret(getenv("HOME"));
	ret += "/.config";
	mkdir(ret.c_str(), 0777);
	ret += "/magicwar";
	mkdir(ret.c_str(), 0777);
	ret += "/main.conf";
#endif
	return ret;
}

int main(int argc, char *argv[]) {
	//Set up gettext
	setlocale(LC_ALL, "");
	bindtextdomain(PACKAGE, LOCALEDIR);
	textdomain(PACKAGE);

	try {
		Parser::gameCfg.loadFromFile(gameCfgFile());
	} catch (const Exception& e) {
		//Nothing bad happend, the file just didn't exist. We can use default values
		cout << _("Configuration file does not exist, using default configuration values.") << endl;
	}

	//Look for some intresting command lind arguments
	string whichinterface = Parser::gameCfg.getValueString("Interface", "cli");
	for (int i = 1; i < argc; i++) {
		string arg(argv[i]);
		if (arg == "--about") {
			cout << _(" *** MagicWar 0.1 alpha ***") << endl;
			cout << _("MagicWar is free software, distributed under GNU GPL.") << endl;
			cout << _("MagicWar is written by :") << endl;
			cout << _("  Ideas : Bhan666") << endl;
			cout << _("  Code : Alexis211") << endl;
			cout << _("  Graphics : (nobody)") << endl;
			cout << _("  Translation : (translators, insert your names here)") << endl; 
			return 0;
		} else if (arg == "--help") {
			cout << _("Usage : magicwar [OPTIONS]") << endl << endl;
			cout << _("Options :") << endl;
			cout << _("	--about		prints various informations about program") << endl;
			cout << _("	--help		prints this help screen") << endl;
			cout << _(" --cliface	use command line interface for game (used for developpement)") << endl;
			cout << _("	--iface2d	use 2D interface for game (used for developpement)") << endl;
			cout << _("	--iface3d	use 3D interface for game") << endl << endl;
			cout << _("For more options, try editing configuration file : ") << gameCfgFile() << endl;
			return 0;
		} else if (arg == "--cliface") {
			whichinterface = "cli";
		} else if (arg == "--iface2d") {
			whichinterface = "2d";
		} else if (arg == "--iface3d") {
			whichinterface = "3d";
		}
	}

	//Because we are in a developpment phase, disable iface3d
	if (whichinterface == "3d") {
		cerr << _("3D interface disabled, reverting to CL interface.") << endl;
		whichinterface = "cli";
	}

	Parser::gameCfg.setValueString("Interface", whichinterface);

	Interface* interface;

	if (whichinterface == "cli") {
		interface = new CLInterface(argc, argv);
	} else if (whichinterface == "2d") {
		interface = new Interface2D(argc, argv);
	} else {
		Parser::gameCfg.setValueString("Interface", "cli");
		interface = new CLInterface(argc, argv);
	}

	try {
		interface->splashScreen();
		UnitType::loadUnitTypes();
		Faction::loadFactions();
		interface->mainMenu();
		interface->credits();
	} catch(const exception& except) {
		cerr << "Exception : " << except.what() << endl;
	}

	delete interface;

	Parser::gameCfg.saveToFile(gameCfgFile());

	return 0;
}

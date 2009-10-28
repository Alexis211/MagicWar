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

#include "../../config.h"

#include "Config.h"

#include "Interface.h"
#include "../iface2d/Interface2D.h"
#include "../iface3d/Interface3D.h"

using namespace std;

int main(int argc, char *argv[]) {
	//Set up gettext
	setlocale(LC_ALL, "");
	bindtextdomain(PACKAGE, LOCALEDIR);
	textdomain(PACKAGE);

	Config* config = Config::get();
	config->loadConfig();

	//Look for some intresting command lind arguments
	bool useiface3d = config->getValueBool("Use3DInterface", true);
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
			cout << _("	--iface2d	use 2D interface for game (used for developpement)") << endl;
			cout << _("	--iface3d	use 3D interface for game") << endl << endl;
			cout << _("For more options, try editing configuration file : ") << config->configFile() << endl;
			return 0;
		} else if (arg == "--iface2d") {
			useiface3d = false;
		} else if (arg == "--iface3d") {
			useiface3d = true;
		}
	}

	//Because we are in a developpment phase, disable iface3d
	if (useiface3d) {
		cerr << _("3D interface disabled, reverting to 2D interface.") << endl;
		useiface3d = false;
	}

	config->setValueBool("Use3DInterface", useiface3d);

	Interface* interface;

	if (useiface3d) {
		interface = new Interface3D(argc, argv);
	} else {
		interface = new Interface2D(argc, argv);
	}

	try {
		interface->splashScreen();
		interface->mainMenu();
		interface->credits();
	} catch(const exception& except) {
		cerr << "Exception : " << except.what() << endl;
	}

	delete interface;

	config->saveConfig();
	Config::kill();

	return 0;
}

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
 *  	Config.h
 *  	Header file for singleton class Config
 *  	Config is the class that manages game configuration.
 *  	*/
#ifndef DEF_MW_CONFIG_SINGLETON_CLASS
#define DEF_MW_CONFIG_SINGLETON_CLASS

#include <vector>
#include <string>

#include "singleton.h"

struct ConfEntry {
	std::string name;
	std::string value;
};

class Parser {
	private:
	std::vector<ConfEntry> m_entries;

	std::string m_section;

	ConfEntry& findValue(std::string name);

	public:
	Parser();
	~Parser();

	static Parser gameCfg;

	void loadFromFile(std::string filename);
	bool saveToFile(std::string filename);

	void setSection(std::string name = "");

	int getValueInt(std::string name, int defaultval = 0);
	float getValueFloat(std::string name, float defaultval = 0);
	bool getValueBool(std::string name, bool defaultval = false);
	std::string getValueString(std::string name, std::string defaultval = "");

	void setValueInt(std::string name, int value);
	void setValueFloat(std::string name, float value);
	void setValueBool(std::string name, bool value);
	void setValueString(std::string name, std::string value);
};

#endif

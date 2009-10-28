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
 *  	Config.cpp
 *  	Code file for singleton class Config
 *  	Config is the class that manages game configuration.
 *  	*/

#if defined (linux)
#include <sys/types.h>
#include <sys/stat.h>
#include <cstdlib>
#elif defined (WIN32)
#include <direct.h>
#endif
#include <fstream>
#include <sstream>

#include "Config.h"

using namespace std;

Config::Config() {
	m_configLoaded = false;
}

Config::~Config() {
	//Nothing
}

string Config::configFile() const {
	//TO BE ADAPTED ALSO FOR MAC, AND MODIFIED FOR WINDOWS
#if defined (linux)
	string ret(getenv("HOME"));
	ret += "/.config";
	mkdir(ret.c_str(), 777);
	ret += "/magicwar";
	mkdir(ret.c_str(), 777);
	ret += "/main.conf";
#elif defined (WIN32)
	string ret("C:/WINDOWS/magicwar.conf");
#endif
	return ret;
}

void Config::loadConfig() {
	m_entries.clear();
	string filename = configFile();

	ifstream file(filename.c_str(), ios::in);
	if (file) {
		string line;
		while (getline(file, line)) {
			ConfEntry temp;
			bool isvalue = false;
			for (int i = 0; i < line.length(); i++) {
				if (!isvalue) {
					if (line[i] == '=') {
						isvalue = true;
					} else {
						temp.name += line[i];
					}
				} else {
					temp.value += line[i];
				}
			}
			m_entries.push_back(temp);
		}
		file.close();
	}
	m_configLoaded = true;
}

bool Config::saveConfig() {
	string filename = configFile();

	ofstream file(filename.c_str(), ios::out);
	if (file) {
		for (unsigned int i = 0; i < m_entries.size(); i++) {
			file << m_entries[i].name << "=" << m_entries[i].value << endl;
		}

		file.close();
		return true;
	} else {
		return false;
	}
}

ConfEntry& Config::findValue(string name) {
	if (!m_configLoaded) loadConfig();
	for (unsigned int i = 0; i < m_entries.size(); i++) {
		if (m_entries[i].name == name) {
			return m_entries[i];
		}
	}
	ConfEntry temp;
	temp.name = name;
	temp.value = "#UNSET#";
	m_entries.push_back(temp);
	return m_entries.back();
}

int Config::getValueInt(string name, int defaultval) {
	ConfEntry& e = findValue(name);
	if (e.value == "#UNSET#") setValueInt(name, defaultval);

	int ret;
	stringstream v(e.value);
	v >> ret;
	return ret;
}

float Config::getValueFloat(string name, float defaultval) {
	ConfEntry& e = findValue(name);
	if (e.value == "#UNSET#") setValueFloat(name, defaultval);

	float ret;
	stringstream v(e.value);
	v >> ret;
	return ret;
}

bool Config::getValueBool(string name, bool defaultval) {
	ConfEntry& e = findValue(name);
	if (e.value == "#UNSET#") setValueBool(name, defaultval);

	return (e.value == "True");
}

string Config::getValueString(string name, string defaultval) {
	ConfEntry& e = findValue(name);
	if (e.value == "#UNSET#") e.value = defaultval;

	return e.value;
}

void Config::setValueInt(string name, int value) {
	ConfEntry& e = findValue(name);
	stringstream v;
	v << value;
	e.value = v.str();
}

void Config::setValueFloat(string name, float value) {
	ConfEntry& e = findValue(name);
	stringstream v;
	v << value;
	e.value = v.str();
}

void Config::setValueBool(string name, bool value) {
	ConfEntry& e = findValue(name);
	e.value = (value ? "True" : "False");
}

void Config::setValueString(string name, string value) {
	ConfEntry& e = findValue(name);
	e.value = value;
}

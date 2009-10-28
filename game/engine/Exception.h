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
 *  	Exception.h
 *  	Header file for class Exception
 *  	This class is a basic class for handling exceptions
 *  	*/
#ifndef DEF_MW_EXCEPTION_CLASS
#define DEF_MW_EXCEPTION_CLASS

#include <exception>
#include "../../config.h"

enum ExceptionType {
	NOTICE, WARNING, ERROR, CRITICAL
};

class Exception : public std::exception {
	private:
	std::string m_message;
	ExceptionType m_type;

	public:
	Exception(const std::string message, ExceptionType type = ERROR) throw() : m_type(type), m_message(message) {
	}

	virtual const char* what() const throw() {
		std::string v;
		if (m_type == NOTICE) {
			v = _("NOTICE : ");
		} else if (m_type == WARNING) {
			v = _("WARNING : ");
		} else if (m_type == ERROR) {
			v = _("ERROR : ");
		} else if (m_type == CRITICAL) {
			v = _("CRITICAL : ");
		}
		v += m_message;
		return v.c_str();
	}

	virtual ~Exception() throw() {
	}
};

#endif

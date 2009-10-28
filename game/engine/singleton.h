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

#ifndef		__SINGLETON_H
#define		__SINGLETON_H

template <typename T> class CSingleton {
    protected:
	CSingleton( void ) { }
	~CSingleton( void ) { }


    public:
	static T *get() {
		if(m_Singleton == 0) {
			m_Singleton = new T;
		}
		return (T*)m_Singleton;
	}

	static void kill(void) {
		if( m_Singleton != 0 ) {
			delete m_Singleton;
			m_Singleton = 0;
		}
	}


    protected:
	static T	*m_Singleton;

};

template <typename T> T *CSingleton<T>::m_Singleton = 0;

#endif

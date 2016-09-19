/*
* Mabon v0.1.0
* (c) Kamil Dubik 2013
*
*
* This file is part of Mabon.
*
* Mabon is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* Mabon is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with Mabon.  If not, see <http://www.gnu.org/licenses/>.
*
*/

# ifndef mabonCORE_HPP
# define mabonCORE_HPP

# include <iostream>
# include <string>
# include <string.h>
# include <ctime>
# include <cstdlib>

# include "parser.hpp"

using namespace std;

const string ver = "0.1.0";

struct _mkOptions {
	bool showAll;
	bool showNames;
	bool showVer;
	bool silent;
	bool noDia;	// No diakritics in names
	string lng;	// Which language
	string tradition;	// Which tradition
};

struct _mkNameData {
	int day, month, year;
	string lng;
	string name;	// Meno klasicky   
	string wdname;	// Meno bez diakritiky
};

class mkNames {
	private:
	
	public:
	_mkNameData *names;
	
	int count;
	int loadNames();
	void freeNames ();
	
};

class mkEngine {
	private:
		_mkNameData actual;	// Info o aktualnom dni...
				
	public:
		_mkOptions options;	// Command line nastavenia
		mkNames namesData;	// Databaza s menami
		int mkErrors[10];	// Mozne chyby, o ktorych budeme informovat na konci
		
		int initKalendar();
		void showHelp();
		void showIntro();
		void computeData ();
		void showData ();
		void showNames ();
		void showVersion ();
};

# endif
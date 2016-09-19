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

# include <iostream>
# include "core.hpp"

int main(int argc, char *args[])
{
	int b,tmp;
	
	// Hlavny objekt programu
	mkEngine mabon;

	// Inicializacia premennych, menneho kalendara atd...
	if (mabon.initKalendar()!=0) mabon.mkErrors[2] = 1;	// Problem s nacitanim mena??
		
	if (argc==1) mabon.showHelp(); else {	
		// Spracovanie CMD argumentov
		for (b=1;b<argc;b++) {
			if (strcmp(args[b],"-a")==0) mabon.options.showAll = true;
			if (strcmp(args[b],"-n")==0) mabon.options.showNames = true;
			if (strcmp(args[b],"-v")==0) mabon.options.showVer = true;
			if (strcmp(args[b],"-s")==0) mabon.options.silent = true;
			if (strcmp(args[b],"-d")==0) mabon.options.noDia = true;
			if (strcmp(args[b],"-l")==0)  {
				if (b<(argc-1)) {
					mabon.options.lng = args[b+1];
					b++; 
				} else mabon.mkErrors[1] = 1;	// Parameter l nema dodatocne udaje
			}	
		}
	
		if (!mabon.options.silent) mabon.showIntro();
	
		// Errors
		if (mabon.mkErrors[1]==1) cout << "[1] Chyba parametra '-l' : Potrebne su dalsie vstupne udaje.\n";
		if (mabon.mkErrors[2]==1) cout << "[2] Chyba pri inicializacii kalendara: Problem s nacitanim 'names.dat'.\n";
		
		// Ak bol nejaky error, oddelime spravy prazdnym riadkom
		tmp = 0;
		for (b=1;b<9;b++) tmp = tmp + mabon.mkErrors[b];
		if (tmp>0) cout << endl; 
	
		mabon.computeData();

		if ((mabon.mkErrors[2]==0) &&(mabon.options.showAll)) mabon.showData();
		if ((mabon.mkErrors[2]==0) && (mabon.options.showNames)) mabon.showNames();
		if (mabon.options.showVer) mabon.showVersion();
	}
 
	if (mabon.mkErrors[2]==0) mabon.namesData.freeNames ();	// Databaza s menami, treba vymazat pamat
	return 0;
}
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

# include "core.hpp"

using namespace std;

int mkEngine::initKalendar()
{
	int error = 0;
	int a;
	
	// Errory v mabone pripravime na zapis,zatial je vsetko OK
	for (a=1;a<10;a++) mkErrors[a] = 0;
	
	// Hlavne nastavenia programu, pred nacitanim konfigu z CMD
	options.lng = "svk"; // 1 = svk
	options.tradition = "svk"; // 1 = svk
	options.showAll = false;
	options.showNames = false;
	options.showVer = false;
	options.silent = false;
	options.noDia = false;	// Mena chceme s diakritikou by default
	
	// Databaza s menami, init
	error = namesData.loadNames();
	if (error==0) cout << "Chyba pri nacitani databazy mien !";
	
	// Kedze 0 znamena ziadna chyba pri vystupe funkcie, musime ju invertnut
	if (error==0) error = 1; else error = 0;
	
	return error;
}

void mkEngine::showHelp()
{
	cout << "Pouzitie:\n";
	cout << "mabon -a          : Ukaze aktualny datum a suvisiace veci\n";
	cout << "mabon -v          : Ukaze verziu programu\n";
	cout << "mabon -n          : Ukaze iba mena pre aktualny den\n";
  cout << "      -s          : Tichy mod (ukaze len vyziadane udaje)\n";
	cout << "      -d          : Menny kalendar zobrazi mena bez diakritiky\n";	 
	cout << "      -l JAZYK    : Ktory menny kalendar pouzit (default SSK)\n";
	cout << "      -t TRADICIA : Sviatky ktorej tradicie sa budu ukazovat (default SSK)\n";
	
	cout << "\n JAZYKY  : SKY, CZE, SSK (staroslovansky)\n";		
	cout << "TRADICIE : SKY, SSK\n\n";	
}

void mkEngine::showIntro()
{
  cout << "Mabon kalendar v" << ver << endl;
  cout << "Kamil Dubik (c) marec - jun, 2013\n\n";
}

void mkEngine::showVersion()
{
  cout << ver << endl;
}

void mkEngine::computeData ()
{
	// current date/time based on current system
	
	time_t now = time(0);
	tm *ltm = localtime(&now);
	
	// convert now to string form
	char* dt = ctime(&now);
   
	actual.month = 1+ltm->tm_mon;
	actual.day = ltm->tm_mday;
	actual.year =  1900 + ltm->tm_year;

//	cout << 1+ltm->tm_mon;
}


void mkEngine::showNames ()
{
	int a;
	
	for (a=0;a<namesData.count;a++) {
		if ((actual.day == namesData.names[a].day) &&
		(actual.month == namesData.names[a].month)) {
			if (options.lng == namesData.names[a].lng) {
		
			 	if (options.noDia) cout << namesData.names[a].wdname; else
			 	cout << namesData.names[a].name; 
			 	
			 	cout << endl;
			}					
		// cout << namesData.names[a].name << " ("<< namesData.names[a].lng << ")" << endl;
		// cout << (int) namesData.names[a].month << endl;
		// actual.name = namesData.names[a].name;
		// actual.wdname = namesData.names[a].wdname;
		}
	}
}

void mkEngine::showData () 
{  
	int a;
	
	cout << "Aktualny datum: ";	
  cout << actual.day << "." << actual.month << " " << actual.year<< endl;	
  cout << "Aktualny menny kalendar (Jazyk): ";	
  cout << options.lng << endl;
  cout << "Aktualny kalendar tradicii (Sviatky): ";	
  cout << options.tradition << endl;
  cout << "Meniny ma: " << endl;
   
	showNames();
   
	//cout << "The local date and time is: " << dt << endl;	
	//cout << 1+ltm->tm_mon;

}

int mkNames::loadNames ()
{
	int x = 0,c = 0;
	PARSER *parser = new PARSER;
	
	// Najprv iba spocitame pocet mien ---------------------
	if (parser->load("names.dat")) {
  	while (!parser->isend()) {
    	if (parser->scan()) x++;    
  	}
  	// cout << "Mam X - " << x << " c-" << c << endl;
		parser->close();
	
		delete parser;
  	parser = 0;


		// A teraz kompletne nacitame mena --------------------
		count = x;
	
		names = new _mkNameData [count];
		parser = new PARSER;
	
		parser->load("names.dat");
  	while (!parser->isend()) {
    	if (parser->scan()) { 
    
    		names[c].day = atoi(parser->get_word(0).c_str());
    		names[c].month = atoi(parser->get_word(1).c_str());
 				names[c].lng = parser->get_word(2);
    		names[c].name = parser->get_word(3);
    		if (parser->get_word_count()>4)	names[c].wdname = parser->get_word(4);
    			else names[c].wdname = names[c].name;
    	
    		// if (names[c].wdname =="Anezka") cout << "Anzwe - " <<(int) names[c].month;
    		// cout << names[c].name << " " << names[c].wdname << " " <<(int) names[c].month << endl;
    		c++;
  		}
  	}
  
		parser->close();
	}
	
	delete parser;
  parser = 0;

	return x;
}

void mkNames::freeNames ()
{
	if ( names ) {
  	delete[] names;
  	names = 0;
 	}
}
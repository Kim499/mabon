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
# include <fstream>
# include <string>
# include "parser.hpp"

using namespace std;

bool PARSER::load(string fname) {
  fin.open(fname.c_str());
  return fin.is_open();
}

bool PARSER::isend() {
  return fin.eof();
}

bool PARSER::scan() {
  int a,x;
  bool is_word, empty_string;
  string ss;
  char ch;

	if (fin.good()) {
  	ss="";
  	empty_string = true;
  	getline(fin,ss);
  
 		for (a=0;a<25;a++) words[a]="";
  
  	word_count = 0;
  	is_word = false;
    
		if ((ss[0]!=35) && (ss!="")) {         
		
			empty_string = false;
			word_count = 0;
      
			for (x=0;x<ss.length();x++) {
			ch = ss[x];
			if (ch!=32) {
				if (!is_word) { is_word = true; word_count++; }
				words[word_count-1] = words[word_count-1] + ch;     	
    		}
      	if (ch==32) is_word = false;	
    	}
  	}
  } else empty_string = true;
  
	return (!empty_string); 
}

char PARSER::get_word_count() {
  return word_count;
}

string PARSER::get_word(char index) {
  return words[index];
}

void PARSER::close() {
  fin.close();
}

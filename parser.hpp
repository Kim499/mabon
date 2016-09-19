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

# ifndef KPARSER_HPP
# define KPARSER_HPP

# include <string>
# include <fstream>

using namespace std;

class PARSER {
private:
  ifstream fin;  
  string words[25];
  short int word_count;  
  
public:
    PARSER () {}
    ~PARSER() {}
    bool load(string fname);
    bool isend();
    bool scan();
    char get_word_count();
    string get_word(char index);
    void close();
};

# endif
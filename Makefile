# Mabon v0.1.0
# (c) Kamil Dubik 2013
#
# This file is part of Mabon.
#
# Mabon is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# Mabon is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with Mabon.  If not, see <http://www.gnu.org/licenses/>.

CC=g++
CCARG=-c -Wall

all: mabon
	
build: mabon

mabon: main.o parser.o core.o
	$(CC) -o mabon core.o parser.o main.o

main.o: main.cc
	$(CC) $(CCARG) main.cc

parser.o: parser.cc
	$(CC) $(CCARG) parser.cc
	
core.o: core.cc
	$(CC) $(CCARG) core.cc	
	
clean:
	rm -rf *o
	
back:
	cp -f -v * backup
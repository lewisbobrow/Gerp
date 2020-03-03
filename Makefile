#
# Author: Lewis Bobrow
# Filename: Makefile
# Contains: Makefile
# Part of: Project 2 assignment "Grep" for Comp 15 Fall 2018
# 

CXX = clang++
CXXFLAGS = -Wall -Wextra -c -O2 -std=c++11
DEPS = Gerp.h DirNode.h FSTree.h 
 
 %.o: %.cpp $(DEPS)
	$(CXX) -o $@ $< $(CXXFLAGS)

gerp: main.o Gerp.o DirNode.o FSTree.o
	$(CXX) -o gerp Gerp.o main.o DirNode.o FSTree.o

gerptest: gerptest.o Gerp.o DirNode.o FSTree.o
	$(CXX) -o gerptest gerptest.o Gerp.o DirNode.o FSTree.o

clean:
	rm -f gerp* *~ search
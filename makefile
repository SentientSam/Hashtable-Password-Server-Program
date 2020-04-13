##############################################
# Author: Samuel Lamb												 #
# Class: cop4530                             #
# Assignment: Assignemnt 5                   # 
# Filename: makefile                         #
# Date Created: 4/6/2020                     #
# Description: makefile for assignment 5     #
##############################################

CC = g++ -lcrypt -o
CCC = g++ -std=c++11 -lcrypt -c

main: proj5.x
proj5.x: proj5.o
	$(CC) proj5.x proj5.o 
proj5.o: proj5.cpp hashtable.h hashtable.hpp passserver.h passserver.cpp
	$(CCC) proj5.cpp

clean: 
	-rm *.x
	-rm *.o




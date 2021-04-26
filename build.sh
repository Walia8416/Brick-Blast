#!/bin/bash

appRunning=1


while [ $appRunning == 1 ]; do

	echo Running...
	g++ -c src/*.cpp -std=c++14 -Werror
	g++ *.o -o bin/Game -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-network
	./bin/Game
	read -n 1 -s
	clear
	exit
	
	
done

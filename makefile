make: 
	mkdir -p bin
	g++ main.cpp src/* example/* -o bin/game -lsfml-system -lsfml-window -lsfml-graphics
	bin/game

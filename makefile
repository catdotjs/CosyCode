make: 
	mkdir -p bin
	g++ main.cpp src/* -o bin/game -lsfml-system -lsfml-window -lsfml-graphics
	bin/game

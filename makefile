make: 
	mkdir -p bin
	g++ main.cpp src/* -o bin/game -lsfml-system
	bin/game

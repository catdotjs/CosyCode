make: 
	mkdir -p bin
	g++ main.cpp src/* example/* -o bin/game -lsfml-system -lsfml-window -lsfml-graphics
	cp assets/ bin/assets -r
	bin/game
	rm core

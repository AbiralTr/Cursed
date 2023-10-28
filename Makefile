all:
	g++ -std=c++11 -I src/include -L src/lib -o game game.cpp -lmingw32 -lSDL2main -lSDL2
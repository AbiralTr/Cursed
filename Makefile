all:
	g++ -std=c++11 -I src/SDL2/include -L src/SDL2/lib -o main.exe *.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image
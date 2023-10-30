all:
	g++ -std=c++11 -I src/include -I src/SDL2_image/include -L src/lib -o main.exe *.cpp -lmingw32 -lSDL2main -lSDL2
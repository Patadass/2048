CPP_FILES := $(wildcard src/*.cpp)

all: terminal

terminal:
	g++ -o 2048 ./src/main.cpp ./src/graphics_terminal.cpp ./src/util.cpp

curses:
	g++ -o 2048 ./src/main_curses.cpp ./src/graphics_curses.cpp ./src/util.cpp -lncurses

windows:
	g++ -o 2048.exe .\src\main.cpp .\src\graphics_terminal.cpp

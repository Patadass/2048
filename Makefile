all: terminal

terminal:
	g++ -o 2048 src/main.cpp src/graphics_terminal.cpp

CPP_FILES := $(wildcard src/*.cpp)

all: terminal

terminal:
	g++ -o 2048 $(CPP_FILES)

windows:
	g++ -o 2048.exe src/main.cpp src/graphics_terminal.cpp

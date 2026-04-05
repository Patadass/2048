t_src = $(wildcard ./src/*terminal.cpp ./src/util.cpp)
c_src = $(wildcard ./src/*curses.cpp ./src/util.cpp)

FLAGS = -Wall -lncurses

all: curses

terminal:
	$(CXX) -o 2048 $(t_src) 

curses:
	$(CXX) -o 2048 $(c_src) $(FLAGS)

static:
	$(CXX) -static $(c_src) -o 2048s $(FLAGS) -ltinfo

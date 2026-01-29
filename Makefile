t_src = $(wildcard ./src/*terminal.cpp)
c_src = $(wildcard ./src/*curses.cpp)

FLAGS = -lncurses

all: curses

terminal:
	$(CXX) -o 2048 $(t_src) ./src/util.cpp

curses:
	$(CXX) -o 2048 $(c_src) ./src/util.cpp $(FLAGS)


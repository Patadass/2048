T_SRC = $(wildcard ./src/*terminal.cpp ./src/util.cpp)
CXX_SRC = $(wildcard ./src/*curses.cpp ./src/util.cpp)
OBJS = $(CXX_SRC:.cpp=.o)

CXXFLAGS = -Wall -lncurses

all: curses

terminal:
	$(CXX) -o 2048 $(t_src) 

curses:
	$(CXX) -o 2048 $(c_src) $(FLAGS)

static:
	$(CXX) -static $(c_src) -o 2048s $(FLAGS) -ltinfo

objects: $(OBJS)
	$(CXX) -o 2048 $(OBJS) $(CXXFLAGS)

./src/graphics_curses.o: ./src/graphics_curses.cpp
	$(CXX) -c $< -o $@ $(CXXFLAGS)

./src/main_curses.o: ./src/main_curses.cpp
	$(CXX) -c $< -o $@ $(CXXFLAGS)

./src/util.o: ./src/util.cpp
	$(CXX) -c $< -o $@ $(CXXFLAGS)

clean:
	rm $(OBJS)

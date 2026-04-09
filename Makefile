T_SRC = $(wildcard ./src/*terminal.cpp ./src/util.cpp)
CXX_SRC = $(wildcard ./src/*curses.cpp ./src/util.cpp)
OBJS = $(CXX_SRC:.cpp=.o)

CXXFLAGS = -Wall -lncurses

all: curses

terminal:
	$(CXX) -o 2048 $(T_SRC) 

curses:
	$(CXX) -o 2048 $(CXX_SRC) $(CXXFLAGS)

static:
	$(CXX) -static $(CXX_SRC) -o 2048s $(CXXFLAGS) -ltinfo

objects: $(OBJS)
	$(CXX) -o 2048 $(OBJS) $(CXXFLAGS)

./src/%.o: ./src/%.cpp
	$(CXX) -c $< -o $@ $(CXXFLAGS)

clean:
	rm $(OBJS)

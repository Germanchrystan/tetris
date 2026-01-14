CXX = g++
CFLAGS = -Wall -Wextra -Werror
COMPILER_CALL = $(CXX) $(CFLAGS)
LDFLAGS = -lraylib

CSOURCES = $(wildcard *.cpp) # Get all .cpp files in the current directory
COBJS = $(patsubst %.cpp, %.o, $(CSOURCES))

all: tetris

tetris: $(COBJS)
	$(COMPILER_CALL) -o tetris main.o block.o blocks.o grid.o colors.o game.o position.o $(LDFLAGS)
	rm -f $(COBJS)

%.o: %.cpp
	$(COMPILER_CALL) -c $< -o $@

clean:
	rm -f $(COBJS)

run:
	./tetris
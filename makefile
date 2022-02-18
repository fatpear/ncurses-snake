all: snake
snake: player.cpp snake.h snake.cpp
	g++ player.cpp snake.cpp Food.cpp -o snake -lncurses

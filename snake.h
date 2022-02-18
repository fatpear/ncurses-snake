#ifndef _SNAKE_H_
#define _SNAKE_H_
#include <ncurses.h>
class Snake
{
	public:
		Snake(WINDOW * win, int starty, int startx, char c); //set default variable
		void grow(); //grow snake
		void shiftDown(int newx, int newy); //move down each value in an array, put new values at top
		int getmv(); //get input to move/change direction
		void mv(); //move according to direction value
		void display(); //display snake in window
		bool collision(); //check for collision with self or borders
		int getLength(); //return length of snake
		void increase_speed(int multiplier); //increase speed of snake by a multiplier
		
	private:
		int x, y, length, direction;
		int * growth = new int[2];
		int * location = new int[1];
		char character;
		int movement_delay = 100000;
		WINDOW * curwin;
};

#endif

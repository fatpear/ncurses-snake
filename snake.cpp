#include <ncurses.h>
#include <unistd.h>
#include "snake.h"

#define DELAY 50000

//set default variable
Snake::Snake(WINDOW * win, int starty, int startx, char c)
{
	int * growth = new int[2];
	growth[0] = 0;
	growth[1] = 0;
	curwin = win;

	y = starty;
	x = startx;

	length = 0;

	character = c;
	movement_delay = 150000;

	direction = 4;

	location[0] = y;
	location[1] = x;
}

//grow snake
void Snake::grow()
{
	//make new array of incremented length
	int * new_array = new int[(length+1) * 2 + 2];

	//copy current array to new array
	for (int i = 0; i < length+1; i++)
	{
		new_array[i * 2] = location[i * 2];
		new_array[i * 2 + 1] = location[i * 2 + 1];
	}

	//add new tail
	new_array[(length+1) * 2] = growth[0];
	new_array[(length+1) * 2 + 1] = growth[1];

	//increment length
	length++;

	//update location array
	location = new_array;
}

//allows movement, 'shifting' array or moving down each value in array so that snake can move and 'forget' the tail end position
void Snake::shiftDown(int newx, int newy)
{
	//remembers last location
	growth[0] = location[length*2];
	growth[1] = location[length*2+1];
	
	//move down each value in array
	for (int i = length; i > 0; i--)
	{
		location[i * 2] = location[i * 2 - 2];
		location[i * 2 + 1] = location[i * 2 - 1];
	}

	//new head position
	location[0] = newy;
	location[1] = newx;
}

//get input to move
int Snake::getmv()
{
	//get input
	char choice = wgetch(curwin);
	
	//gets rid of any typeahead that has not been read by wgetch() if duplicates exist
	//However, holding a key for a while and then immediately pressing a new key will not switch the direction, as the new key would also be affected by flushinp().
	//i have no idea how to fix this
	if (choice == 'w' && direction == 1)
        {
                flushinp();
        }
        if (choice == 's' && direction == 2)
        {
                flushinp();
        }
        if (choice == 'a' && direction == 3)
        {
                flushinp();
        }
        if (choice == 'd' && direction == 4)
        {
                flushinp();
        }
	
	//disallow moving in opposite direction if tail exists
	if(length>0){
		if(choice == 'w' and direction == 2)
		{
			return 0;
		}
		else if(choice == 's' and direction == 1)
		{
			return 0;
		}
		else if(choice == 'a' and direction == 4)
		{
			return 0;
		}
		else if(choice == 'd' and direction == 3)
		{
			return 0;
		}
	}
	
	//set direction according to key pressed
	switch(choice)
	{
		case 'w':
			direction = 1;
			break;
		case 's':
			direction = 2;
			break;
		case 'a':
			direction = 3;
			break;
		case 'd':
			direction = 4;
			break;
		case 'p':
			grow();
			break;
		default:
			break;
	}

	return choice;
}

//move
void Snake::mv()
{
	//make tail end blank before moving
	mvwaddch(curwin, location[length * 2], location[length * 2 + 1], ' ');
	
	//move according to direction value
	switch(direction)
	{
		case 1:
			y--;
			shiftDown(x, y);
			break;
		case 2:
			y++;
			shiftDown(x, y);
			break;
		case 3:
			x--;
			shiftDown(x, y);
			break;
		case 4:
			x++;
			shiftDown(x, y);
			break;
		default:
			break;
	}
	
	//delay between each movement
	usleep(movement_delay);
}

//display snake
void Snake::display()
{
	//run through every value in location array and display
	for (int i = 0; i <= length; i++)
	{
		//display head as character, display tail as '#'
		if (i == 0)
		{
			mvwaddch(curwin, location[i*2], location[i*2+1], character);
		} else
		{
			mvwaddch(curwin, location[i*2], location[i*2+1], '#');
		}
	}
}

//checks if snake has collided with tail or borders
bool Snake::collision()
{		
	//checks collision with borders
	if(location[0]>19  or location[0]<0 or location[1]>49  or location[1]<0)
	{
		return true;	
	}
	
	//checks collision with self
	if(mvwinch(curwin, location[0], location[1]) == '#')
	{
		return true;
	}
	
	return false;
}

//return length of snake
int Snake::getLength()
{
	return length;
}

//increase speed by a multiplier
void Snake::increase_speed(int multiplier){
	movement_delay = multiplier;
}

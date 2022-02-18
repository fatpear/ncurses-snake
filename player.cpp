#include <ncurses.h>
#include <string>
#include <ctime>
#include "snake.h"
#include "Food.h"
using namespace std;

int main(int argc, char ** argv)
{
	/* ncurses start */
	initscr();
	noecho();
	cbreak();
	curs_set(0);
	start_color();

	// get screen size
	int yMax, xMax;
	getmaxyx(stdscr, yMax, xMax);

	// create a window for our input
	WINDOW * playwin = newwin(20, 50, (yMax/2)-10, (xMax/2)-25);

	//stops getch() or wgetch() from waiting for input, allowing automatic movement
	nodelay(playwin, true);

	//draw border
	for(int i = 0; i<50;i++){

		mvprintw((yMax/2)-11, (xMax/2)-25+i, "-");
		mvprintw((yMax/2)+10, (xMax/2)-25+i, "-");

		}

	for(int i = 0; i<20;i++){

		mvprintw((yMax/2)-10+i, (xMax/2)-26, "|");
		mvprintw((yMax/2)-10+i, (xMax/2)+25, "|");

		}

	//box(playwin,0,0);
	
	refresh();
	wrefresh(playwin);

	//create new snake and food variables
	Snake * p = new Snake(playwin, 1, 1, '@');
	Food * apple = new Food(playwin, xMax, yMax, 'a');
	Food * lemon = new Food(playwin, xMax, yMax, 'l');
	Food * orange = new Food(playwin, xMax, yMax, 'o');

	//mvwaddch(playwin, 0, 0, 'a');
	while(1) 
	{
		//display score (length)
		move((yMax/2)-11, (xMax/2)-26);
		printw("Score: %d", p->getLength());
		refresh();

		//if collided, end while loop
		if (p->collision() == true){
			attron(COLOR_RED);
			p->display();
			attroff(COLOR_RED);
			break;
		}
		
		//get input, move accordingly, display on window
		p->getmv();
		p->mv();
		p->display();
		wrefresh(playwin);

		//if food is eaten, grow snake, regenerate food
		if (apple->food_eaten()==true){
				p->grow();
				apple->generate_food();
				apple->display_food();
		}
		
		//if food is not present, generate food
		if (apple->food_present()==false){
			apple->generate_food();
			apple->display_food();
		}
		
		//if score is 5/10/20, increase speed
		if (p->getLength() == 5){
			p->increase_speed(70000);
		}
		
		else if (p->getLength() == 10){
			p->increase_speed(50000);
		}
		
		else if (p->getLength() == 20){
			p->increase_speed(30000);		
		}
	}

	//death message shown until user presses key
	nodelay(playwin, false);
	move(0,0);
	printw("toekneeknow");
	getch();

	endwin();
	return 0;
}

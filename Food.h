#ifndef _FOOD_H_
#define _FOOD_H_
#include <iostream>
#include <ncurses.h>
#include <random>
#include <ctime>
using namespace std;
class Food
{

    public:
        Food(WINDOW * current_window, int xsize, int ysize, char fruit);
        void generate_food(); //generate food
        void display_food(); //display food in window
        bool food_present(); //check if food is present
        bool food_eaten(); //check if food is eaten

    private:
        int xwindow;
        int ywindow;
        int location[2];
        //position 1: apple, position 2: lemon, position 3: orange
        int food_counter;
        bool food_onscreen;
        char type;
        WINDOW * curwin;

};

#endif

#include "Food.h"
#include "snake.h"
#include <ncurses.h>
using namespace std;

//set default variable
Food::Food(WINDOW * current_window, int xsize, int ysize, char fruit){

    xwindow = xsize;
    ywindow = ysize;

    location[0] = -1;
    location[1] = -1;

    food_counter = 0;

    type = fruit;

    food_onscreen = false;

    curwin = current_window;

}

//generate food
void Food::generate_food(){

    //generate random position
    srand(time(NULL));

    bool valid_position = false;

    while(valid_position == false){

        location[0] = rand()%50;
        location[1] = rand()%20;

        //check if position is blank
        if(mvwinch(curwin, location[1], location[0]) == ' '){

            valid_position = true;
        }
    }
    
    food_counter++;


}

//checks if food is present
bool Food::food_present(){

    int food_found = 0;
    
    //checks every position in window for food character
    for (int rows = 0; rows<20; rows++){
        for (int columns = 0; columns<50;columns++){

            int current_position = mvwinch(curwin, rows, columns);

            if (current_position == int(type)){
                food_found++;
            }
        }
    }

    //cout<<food_found<<endl;

    if(food_found == 0){
        return false;
    }

    else{

        return true;
    }

}

//display food on screen
void Food::display_food() {
    mvwaddch(curwin, location[1], location[0], type);
}

//checks if food is eaten
bool Food::food_eaten(){

    //checks if food position is overwritten by snake head
    if(mvwinch(curwin, location[1], location[0]) == '@'){
        return true;
    }

    return false;

}

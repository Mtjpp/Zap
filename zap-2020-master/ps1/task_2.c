#include<superkarel.h>
#define SPEED 1000

void turn_right();
void turn_back();
void run();
void run_back();

int main(){

    turn_on("task_2.kw");
    set_step_delay(SPEED);

    run();
    pick_beeper();
    turn_back();
    run_back();

    turn_off();
    return 0;
}

void turn_right(){  // Zdroj: prednaska P. Pietrikovej
    set_step_delay(0);
    turn_left();
    turn_left();
    set_step_delay(SPEED);
    turn_left();
}

void turn_back(){ // Zdroj: prednaska P. Pietrikovej
    turn_left();
    turn_left();
}

void run(){ // vlastna funkcia
    while ( no_beepers_present() ){
        if ( front_is_clear() ){
            step();
        }
        else if ( front_is_blocked() && right_is_blocked() ){
            turn_left();
            step();
        }
    }
}

void run_back(){ // vlastna funkcia
    while ( no_beepers_present() ){
        if ( front_is_clear() ){
            step();
        }
        else if ( front_is_blocked() && left_is_blocked() && right_is_blocked() ){
            break;
        }
        else if ( front_is_blocked() && left_is_blocked() ){
            turn_right();
            step();
        }
    }
}
#include<superkarel.h>
#define SPEED 80

void turn_right();
void turn_back();
void run();
void run_back();
void face_north();


int main(){

    turn_on("task_1.kw");
    set_step_delay(SPEED);

    put_beeper();
    run();
    pick_beeper();
    turn_back();
    run_back();
    pick_beeper();
    face_north();

    turn_off();
    return 0;
}

void turn_right(){ // Zdroj: prednaska P. Pietrikovej
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
    do{
        if ( front_is_clear() && right_is_blocked() ){
            step();
        }
        else if ( right_is_clear() ){
            turn_right();
            step();
        }
        else if ( right_is_blocked() && front_is_blocked() ){
            turn_left();
            if ( front_is_blocked() ){
                turn_left();
            }
            step();
        }
    } while ( no_beepers_present() );
}

void run_back(){ //vlastna funkcia
    while ( no_beepers_present() ){
        if ( front_is_clear() && left_is_blocked() ){
            step();
        }
        else if ( left_is_clear() ){
            turn_left();
            step();
        }
        else if ( left_is_blocked() && front_is_blocked() ){
            turn_right();
            if ( front_is_blocked() ){
                turn_right();
            }
            step();
        }
    }
}

void face_north(){ // vlastna funkcia
    if ( facing_east() ){
        turn_back();
    }
    else if ( facing_north() ){
        turn_left();
    }
    else if ( facing_south() ){
        turn_right();
    }
}
#include<superkarel.h>
#define SPEED 10

void turn_right();
void run_section();
void turn_back();
void run_all();
void which_beeper();
bool beeper_left();
void pick_line();

int main (){
    turn_on("task_7.kw");
    set_step_delay(SPEED);

    run_all();
    pick_line();

    turn_off();
    return 0;
}

void pick_line(){ // vlastna funkcia
    turn_back();
    while ( beepers_present() && front_is_clear() ){
        pick_beeper();
        step();
    }
    pick_beeper();
    turn_back();
    while ( front_is_clear() ){
        step();
    }
}

void turn_right(){ // Zdroj: prednaska P. Pietrikovej
    set_step_delay(0);
    turn_left();
    turn_left();
    set_step_delay(SPEED);
    turn_left();
}

void turn_back(){ // vlastna funkcia
    turn_left();
    turn_left();
}

bool beeper_left(){ // vlastna funkcia
    turn_left();
    step();
    if ( beepers_present() ){
        turn_back();
        step();
        turn_left();
        return true;
    }
    else {
        turn_back();
        step();
        turn_left();
        return false;
    }
}

void run_section(){ // vlastna funkcia
    while ( no_beepers_present() ){
        if ( front_is_blocked() && left_is_clear() && right_is_clear()){
            turn_left();
            step();
        }
        else if ( front_is_blocked() && left_is_blocked() && right_is_blocked() ){
            turn_back();
            step();
        }
        else if ( left_is_blocked() && front_is_clear() ){
            step();
        }
        else if ( left_is_blocked() && front_is_blocked() ){
            turn_right();
            step();
        }
        else if ( left_is_clear() ){
            turn_left();
            step();
        }
    }
}

void which_beeper(){
    if ( beepers_present() && front_is_clear() ){
        step();
        if ( left_is_blocked() ){
            turn_back();
            step();
            if ( left_is_clear() ){
                turn_left();
                step();
                put_beeper();
                turn_back();
                step();
                turn_left();
                step();
            }
            else {
                while ( beepers_present() && front_is_clear() ){
                    step();
                }
            }
        }
        else{
            turn_left();
            while ( beepers_present() && front_is_clear() ){
                step();
            }
            if ( front_is_blocked() && right_is_blocked() && beepers_present() ){
                turn_left();
                step();
                put_beeper();
                turn_back();
                step();
                turn_left();
            }
            turn_back();
            step();
            turn_right();
            step();
            if ( beepers_present() ){
                turn_back();
                step();
                turn_left();
                step();
            }
            else {
                put_beeper();
                turn_back();
                step();
                turn_left();
                step();
            }
        }
    }    
    else if ( front_is_blocked() && left_is_blocked() && beepers_present() ){
        if ( right_is_clear() ){
            turn_right();
            step();
            if ( beepers_present() ){
                turn_back();
                step();
            }
            else {
                put_beeper();
                turn_back();
                step();
                turn_left();
                step();
            }
        }
        else {
            turn_back();
            while ( beepers_present() ){
                step();
            }
        }
    }
    else if ( front_is_blocked() && right_is_blocked() && beepers_present() ){
        if ( beeper_left() ){
            turn_left();
            while ( beepers_present() ){
                step();
            }
            turn_back();
            step();
            turn_right();
            step();
            put_beeper();
            turn_back();
            step();
            turn_left();
            step();
        }
        else {
            turn_left();
            step();
        }
    }
    else if ( front_is_blocked() && left_is_clear() && right_is_clear() && beepers_present() ){
        if ( beeper_left() ){
            turn_left();
            while ( beepers_present() ){
                step();
            }
            turn_back();
            step();
            turn_right();
            step();
            put_beeper();
            turn_back();
            step();
            turn_left();
            step();
        }
        else {
            turn_left();
            step();
        }
    }
    else if ( front_is_blocked() && left_is_clear() && right_is_clear() && no_beepers_present() ){
        turn_right();
        while ( no_beepers_present() ){
            step();
        }
        turn_right();
        step();
        put_beeper();
        turn_back();
        step();
        turn_left();
        step();
    }
}

void run_all(){ // vlastna funkcia
    while ( no_beepers_present() ){
        put_beeper();
        if ( left_is_clear() ){
            turn_left();
            step();
        }
        else if ( front_is_blocked() ){
            break;
        }
        else if ( left_is_blocked() ) {
            while ( left_is_blocked() ){
                step();
                put_beeper();
            }
            turn_left();
            step();
        }
        run_section();
        which_beeper();
    }
}
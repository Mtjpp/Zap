#include<superkarel.h>
#define SPEED 30

void turn_right();
void turn_back();
void run_pick_beeper();
void run_mile();
void run_right_up();
void place_clothes_wall();
void place_clothes();
void move_down();
bool beepers_present_above();
void starting_position();
void run_mile_beeper();

int main(){
    turn_on("task_3.kw");
    set_step_delay(SPEED);

    run_pick_beeper();
    run_right_up();
    place_clothes_wall();
    place_clothes();
    starting_position(); 

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

void run_mile(){ // Zdroj: prednaska P. Pietrikovej
    while( front_is_clear() ){
        step();
    }
}

void run_mile_beeper(){ // vlastna funkcia
    while( front_is_clear() && no_beepers_present() ){
        step();
    }
}

void run_pick_beeper(){ // vlastna funkcia
    while ( front_is_clear() ){
        while ( front_is_clear() ){
            if ( beepers_present() ){
                pick_beeper();
            }
            step();
        }
        while ( beepers_in_bag() ){
            put_beeper();
        }
        turn_back();
        run_mile();
        if ( left_is_clear() ){
            turn_left();
            step();
            turn_left();
        }
    }
}

void run_right_up(){ // vlastna funkcia
    turn_back();
    run_mile();
    turn_left();
    while ( no_beepers_present() ){
        step();
    }
    while ( beepers_present() && front_is_clear() ){
        step();
    }
    if ( front_is_blocked() && beepers_present() ){
        turn_left();
    }
    else{
        turn_back();
        step();
        turn_right();
    }
}

void place_clothes_wall(){ // vlastna funkcia
    while( beepers_present() ){
        pick_beeper();
    }
    while ( beepers_in_bag() ){
        if ( right_is_blocked() ){
            put_beeper();
            step();
        }
        else{
            step();
        }
    }
}

bool beepers_present_above(){ // vlastna funkcia
    turn_right();
    step();
    if ( beepers_present() ){
        turn_back();
        step();
        turn_right();
        return true;
    }
    else{
        turn_back();
        step();
        turn_right();
        return false;
    }
}

void move_down(){ // vlastna funkcia
    turn_back();
    run_mile();
    turn_right();
    step();
    turn_right();
}

void place_clothes(){ // vlastna funkcia
    while ( left_is_clear() ){
        move_down();
        while ( beepers_present() ){
            pick_beeper();
        }
        while ( beepers_in_bag() ){
            if ( beepers_present_above() ){
                put_beeper();
                step();
            }
            else{
                step();
            }
        }
    }
}

void starting_position(){ // vlastna funkcia
    turn_back();
    run_mile();
    turn_left();
    while ( no_beepers_present() ){
        step();
        if ( front_is_blocked() ){
            break;
        }
    }
    if ( front_is_blocked() ){
        turn_back();
        while ( no_beepers_present() ){
            step();
            turn_right();
            run_mile_beeper();
            if ( beepers_present() ){
                run_mile();
                turn_back();
                break;
            }
            else{
                turn_back();
                run_mile();
                turn_right();
            }
        }
    }
    else{
        while ( beepers_present() && front_is_clear() ){
            step();
        }
        turn_left();
        run_mile();
        turn_back();
    }
}

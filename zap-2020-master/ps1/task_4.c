#include<superkarel.h>
#define SPEED 40

void run_mile();
void turn_right();
void turn_back();
void run_all();
void move_right();

int main(){

    turn_on("task_4.kw");
    set_step_delay(SPEED);

    turn_left();
    run_all();
    move_right();
    turn_left();

    turn_off();
    return 0;

}

void run_mile(){ // Zdroj: prednaska P. Pietrikovej
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

void run_all(){ // vlastna funkcia
    while( front_is_clear() ){
        if ( beepers_present() ){
            run_mile();
            turn_back();
            while ( front_is_clear() ){
                if ( beepers_present() ){
                    step();
                }
                else{
                    put_beeper();
                    step();
                }
            }
            if ( no_beepers_present() ){
                put_beeper();
            }
        }
        else{
            step();
            if ( front_is_blocked() ){
                turn_back();
                run_mile();
            }
        }
    }
}

void move_right(){ // vlastna funkcia
    while ( front_is_blocked() && left_is_clear() ){
        turn_left();
        step();
        turn_left();
        run_all();
    }
}
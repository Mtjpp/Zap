#include<superkarel.h>
#define SPEED 70

void run_mile();
void turn_right();
void turn_back();
void corner();
void run_beepers();
void south_east_corner();
void line_mid();
void double_step();

int main(){

    turn_on("task_5.kw");
    set_step_delay(SPEED);

    corner();
    turn_left();
    run_beepers();
    south_east_corner();
    line_mid();
    line_mid();
    turn_back();

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

void corner(){ // vlastna funkcia
    run_mile();
    turn_left();
    run_mile();
}

void south_east_corner(){ // vlastna funkcia
    if ( facing_east() ){
        run_mile();
        turn_left();
    }
    else if ( facing_south() ){
        run_mile();
        turn_left();
        run_mile();
        turn_left();
    }
    else if ( facing_west() ){
        turn_left();
        run_mile();
        turn_back();
    }
}

void run_beepers(){ // vlastna funkcia
    while( no_beepers_present() ){
        put_beeper();
        step();
        if ( front_is_blocked() ){
            turn_left();
        }
    }
}

void double_step(){ // vlastna funkcia
    step();
    step();
}

void line_mid(){ // vlastna funkcia
    double_step();
    if ( front_is_blocked() ){
        turn_back();
        step();
        turn_right();
    }
    else{
        double_step();
        if ( front_is_blocked() ){
            turn_back();
            double_step();
            turn_right();
        }
        else{
            double_step();
            if ( front_is_blocked() ){
                turn_back();
                double_step();
                step();
                turn_right();
            }
            else{
                double_step();
                if ( front_is_blocked() ){
                    turn_back();
                    double_step();
                    double_step();
                    turn_right();
                }
                else{
                    double_step(); //11
                    if( front_is_blocked() ){
                        turn_back();
                        double_step();
                        double_step();
                        step();
                        turn_right();
                    }
                    else{
                        double_step(); //13
                        if ( front_is_blocked() ){
                            turn_back();
                            double_step();
                            double_step();
                            double_step();
                            turn_right();
                        }
                        else{
                            double_step(); //15
                            if ( front_is_blocked() ){
                                turn_back();
                                double_step();
                                double_step();
                                double_step();
                                step();
                                turn_right();
                            }
                        }
                    }
                }
            }
        }
    }
}
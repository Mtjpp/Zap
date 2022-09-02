#include<superkarel.h>
#define SPEED 70

void turn_back();
void turn_right();
void no_beeper_run();
void beeper_rotation();

int main(){
    
    turn_on("task_6.kw");
    set_step_delay(SPEED);

    no_beeper_run();
    beeper_rotation();
    turn_off();
    return 0;
}

void turn_back(){ // vlastna funkcia
    turn_left();
    turn_left();
}

void turn_right(){ // Zdroj: prednaska P. Pietrikovej
    set_step_delay(0);
    turn_left();
    turn_left();
    set_step_delay(SPEED);
    turn_left();
}

void no_beeper_run(){ // vlastna funkcia
    while ( no_beepers_present() ){
        step();
    }
}

void beeper_rotation(){ // vlastna funkcia
    while ( beepers_present() ){
        pick_beeper();
        if ( no_beepers_present() ){
            if ( facing_south() ){
                turn_back();
            }
            else if ( facing_west() ){
                turn_right();
            }
            else if ( facing_east() ){
                turn_left();
            }
            no_beeper_run();
        }
        else{
            pick_beeper();
            if ( no_beepers_present() ){
                if ( facing_south() ){
                    turn_right();
                }
                else if ( facing_east() ){
                    turn_back();
                }
                else if ( facing_north() ){
                    turn_left();
                }
                no_beeper_run();
            }
            else{
                pick_beeper();
                if ( no_beepers_present() ){
                    if ( facing_north() ){
                        turn_back();
                    }
                    else if ( facing_west() ){
                        turn_left();
                    }
                    else if ( facing_east() ){
                        turn_right();
                    }
                    no_beeper_run();
                }
                else{
                    pick_beeper();
                    if ( no_beepers_present() ){
                        if ( facing_west() ){
                            turn_back();
                        }
                        else if ( facing_south() ){
                            turn_left();
                        }
                        else if ( facing_north() ){
                            turn_right();
                        }
                        no_beeper_run();
                    }
                    else{
                        pick_beeper();
                        if ( no_beepers_present() ){
                            break;
                        }
                    }
                }
            }
        }
    }
}
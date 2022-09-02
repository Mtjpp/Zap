#define _DEFAULT_SOURCE

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<curses.h>
#include<unistd.h>

void lightbeam();
void level1();
void level2();
void level3();
void instructions();

int main(){

    initscr();
    start_color();
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    init_pair(2, COLOR_YELLOW, COLOR_BLACK);
    init_pair(3, COLOR_BLUE, COLOR_BLACK);
    init_pair(4, COLOR_CYAN, COLOR_BLACK);
    init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(6, COLOR_RED, COLOR_BLACK);

    noecho();
    cbreak();
    curs_set(FALSE);
    nodelay(stdscr, TRUE);
    keypad(stdscr, TRUE);

    char menu[5][14] = { "Instructions", "Level  1", "Level  2", "Level  3", "Quit game" };
    int choice;
    int highlight = 0;

    while (1){
        for ( int i = 0; i < 5; i++ ){
            if ( i == highlight ){
                attron(A_STANDOUT);
            }
            if ( i == 0 ){
                char a[15];
                sprintf(a, "%s", menu[i]);
                mvprintw( 15 + i, 44 , a);
            }
            else if ( i == 1 || i == 2 || i == 3 ){
                char a[15];
                sprintf(a, "%s", menu[i]);
                mvprintw( 15 + i, 46 , a);                
            }
            else if ( i == 4 ){
                char a[15];
                sprintf(a, "%s", menu[i]);
                mvprintw( 15 + i, 45 , a);
            }
            attroff(A_STANDOUT);
        }

        lightbeam();

        refresh();

        choice = getch();

        switch(choice){
            case KEY_UP:
                highlight--;
                if ( highlight == -1 ){
                    highlight = 4;
                }
                break;
            case KEY_DOWN:
                highlight++;
                if ( highlight == 5 ){
                    highlight = 0;
                }
                break;
            default:
                break;
        }
        if ( choice == 10 && highlight == 0 ){
            clear();
            refresh();
            instructions();
            clear();
            refresh();
        }

        else if ( choice == 10 && highlight == 1 ){
            clear();
            refresh();
            level1();
            refresh();
        }

        else if ( choice == 10 && highlight == 2 ){
            clear();
            refresh();
            level2();
            refresh();
        }

        else if ( choice == 10 && highlight == 3 ){
            clear();
            refresh();
            level3();
            refresh();
        } 

        else if ( choice == 10 && highlight == 4 ){
            break;
        }
    }

    endwin();

    return 0;
}

void lightbeam(){

    char lightbeam[5][100] = {
        {" __    _     _   _   _                 ___ ____  "},
        {"|  |  | |___| |_| |_| |_ ___ ___ _____|_  |  | | "},
        {"|  |__| | . |   |  _| . | -_| . |     |  _|  | | "},
        {"|_____|_|_  |_|_|_| |___|___|__,|_|_|_|___|____/ "},
        {"        |___|                                    "}
    };

    for ( int i = 0; i < 5; i++ ){
        move( 5 + i, 27 );
        attron(COLOR_PAIR(1));
        printw( "%s", lightbeam[i] );
    }

    attroff(COLOR_PAIR(1));

    attron(COLOR_PAIR(2));
    mvprintw( 24, 38, " Created by: Matej Pipa " );
    attroff(COLOR_PAIR(2));

}

void level1(){

    char level1[15][100] = {
        { "  __________________________________________  " },
        { " !                                          ! " },
        { " !                                          ! " },
        { " !               _______________            ! " },
        { " !              !               !           ! " },
        { " !              !  /    /    /  !           ! " },
        { " !              !_______________!           ! " },
        { " !                                          ! " },
        { " !                                          ! " },
        { " !                                          ! " },
        { " !___________                               ! " },
        { " !  *  *  *  !                              ! " },
        { " !  *  *  *  !    O   ^               O     ! " },
        { " !  *  *  *  !                   _          ! " },
        { " !___________!________________o_!_!_________! " }
    };

    for ( int i = 0; i < 15; i++ ){
        move( 5 + i, 27 );
        printw( "%s", level1[i] );
    }


    int a = ' ';
    char y = 17;
    char x = 49;
    char step = '^';
    int switch0 = 0;
    int switch1 = 0;
    int switch2 = 0;

    mvaddch( 13, 33, 'X' );
    mvaddch( 7, 65, 'X' );


    do {

        attron( COLOR_PAIR(2) );

        if ( mvinch( 7, 33 ) == '/' ){
            switch1 = 0;
        }

        if ( mvinch( 13, 33 ) == '#' && mvinch( 7, 65 ) == '#' && switch0 == 0 ){
            mvaddch( 11, 50, ' ' );
            mvaddch( 11, 51, ' ' );
            mvaddch( 11, 52, ' ' );
            switch0++;
        }

        if ( mvinch( 13, 33 ) == '#' && mvinch( 7, 65 ) == '#' ){
            if ( mvinch( 13, 33 ) == '#' ){
                for ( int i = 0; i < 7; i++ ){
                    if ( mvinch( 12 - i, 33 ) == '/' ){
                        for ( int j = 0; j < 7; j++ ){
                            if ( mvinch ( 11 - i - j, 33 ) != '_' ){
                                mvprintw( 11 - i - j, 33 , " ");
                            }
                            else{
                                break;
                            }
                        }
                        break;
                    }
                    mvprintw( 12 - i, 33, "|" );
                }
            }

            int l = 0;

            if ( mvinch( 7, 65 ) == '#' ){
                for ( int i = 0; i < 11; i++ ){
                    l++;
                    if ( mvinch( 8 + i, 65 ) == '/' ){
                        for ( int j = 0; j < 11; j++ ){
                            if ( mvinch ( 9 + i + j, 65 ) != '_' ){
                                mvprintw( 9 + i + j, 65 , " ");
                            }
                            else{
                                break;
                            }
                        }
                        break;
                    }
                    mvprintw( 8 + i, 65, "|" );
                }                
            }

            if ( mvinch ( 7 + l, 65 ) == '/' && mvinch ( 7 + l, 57 ) == '/' ){
                for ( int i = 0; i < 7; i++ ){
                    mvaddch( 7 + l, 64 - i, '-' );
                }
                for ( int j = 0; j < 10; j++ ){
                    if ( mvinch ( 8 + l + j, 57 ) != 'o' ){
                        mvaddch ( 8 + l + j, 57, '|' );
                    }
                    else{
                        break;
                    }
                }
            }

            if ( mvinch( 7, 33 ) == '/' ){
                for ( int i = 0; i < 31; i++ ){
                    mvaddch( 7, 34 + i, '-' );
                }
            }
            else if ( ( ( mvinch( 7, 33 ) & A_CHARTEXT ) == '|' || ( mvinch( 7, 33 ) & A_CHARTEXT ) == ' ' ) && switch1 == 0 ){
                for ( int i = 0; i < 31; i++ ){
                    mvaddch( 7, 34 + i, ' ' );
                }
                switch1 = 1;
            }
        }


        attroff( COLOR_PAIR(2) );

        refresh();

        if ( mvinch ( 13, 33 ) == 'O' ){
            mvaddch( 13, 33, '#' );
        }

        if ( mvinch ( 7, 65 ) == 'O' ){
            mvaddch( 7, 65, '#' );
        }

        a = getch();

        if ( mvinch ( 19, 60 ) == 'v' ){
            clear();
            attron( COLOR_PAIR(1) );
            mvprintw( 15, 40, "Level 1 Complete" );
            mvprintw( 16, 37, "Press Enter to continue" );
            attroff( COLOR_PAIR(1) );
            a = getch();
        }
        

        if ( a == 81 || a == 113 || a == 10){
            clear();
            break;
        }

        switch(a){
            case KEY_LEFT:
                if ( ( mvinch( y, x - 1 ) & A_CHARTEXT ) == ' ' || (mvinch( y, x - 1 ) & A_CHARTEXT) == '|' || ( mvinch( y, x - 1 ) & A_CHARTEXT) == '-' ){
                    step = 60;
                    mvaddch( y, x - 1, step );
                    mvaddch( y, x, ' ' );
                    x--;
                }
                else if ( mvinch ( y, x - 1 ) == 'O' && ( ( mvinch( y, x - 2 ) & A_CHARTEXT ) == ' ' || mvinch ( y, x - 2 ) == 'X' ) ) {
                    step = 60;
                    mvaddch( y, x - 2, 'O' );
                    mvaddch( y, x - 1, step );
                    mvaddch( y, x, ' ' );
                    x--;
                }
                else if ( mvinch ( y, x - 1 ) == '/' && ( ( mvinch( y, x - 2 ) & A_CHARTEXT ) == ' ' || ( mvinch( y, x - 2 ) & A_CHARTEXT) == '|' || ( mvinch( y, x - 2 ) & A_CHARTEXT) == '-' ) ) {
                    step = 60;
                    mvaddch( y, x - 2, '/' );
                    mvaddch( y, x - 1, step );
                    mvaddch( y, x, ' ' );
                    x--;
                }
            break;

            case KEY_RIGHT:
                if ( ( mvinch( y, x + 1 ) & A_CHARTEXT ) == ' ' || (mvinch( y, x + 1 ) & A_CHARTEXT) == '|' || ( mvinch( y, x + 1 ) & A_CHARTEXT) == '-' ){
                    step = 62;
                    mvaddch( y, x + 1, step );
                    mvaddch( y, x, ' ' );
                    x++;
                }
                else if ( mvinch ( y, x + 1 ) == 'O' && ( ( mvinch( y, x + 2 ) & A_CHARTEXT ) == ' ' || mvinch ( y, x + 2 ) == 'X' ) ) {
                    step = 62;
                    mvaddch( y, x + 2, 'O' );
                    mvaddch( y, x + 1, step );
                    mvaddch( y, x, ' ' );
                    x++;
                }
                else if ( mvinch ( y, x + 1 ) == '/' && ( ( mvinch( y, x + 2 ) & A_CHARTEXT ) == ' ' || ( mvinch( y, x + 2 ) & A_CHARTEXT) == '|' || ( mvinch( y, x + 2 ) & A_CHARTEXT) == '-' ) ) {
                    step = 62;
                    mvaddch( y, x + 2, '/' );
                    mvaddch( y, x + 1, step );
                    mvaddch( y, x, ' ' );
                    x++;
                }
            break;

            case KEY_UP:
                if ( ( mvinch( y - 1, x ) & A_CHARTEXT ) == ' ' || (mvinch( y - 1, x ) & A_CHARTEXT) == '|' || ( mvinch( y - 1, x ) & A_CHARTEXT) == '-' ){
                    step = 94;
                    mvaddch( y - 1, x, step );
                    mvaddch( y, x, ' ' );
                    y--;
                }
                else if ( mvinch ( y - 1, x ) == 'O' && ( ( mvinch( y - 2, x ) & A_CHARTEXT ) == ' ' || mvinch ( y - 2, x ) == 'X' ) ) {
                    step = 94;
                    mvaddch( y - 2, x, 'O' );
                    mvaddch( y - 1, x, step );
                    mvaddch( y, x, ' ' );
                    y--;
                }
                else if ( mvinch ( y - 1, x ) == '/' && ( ( mvinch( y - 2, x ) & A_CHARTEXT ) == ' ' || ( mvinch( y - 2, x ) & A_CHARTEXT) == '|' || ( mvinch( y - 2, x ) & A_CHARTEXT) == '-' ) ) {
                    step = 94;
                    mvaddch( y - 2, x, '/' );
                    mvaddch( y - 1, x, step );
                    mvaddch( y, x, ' ' );
                    y--;
                }
            break;

            case KEY_DOWN:
                if ( ( mvinch( y + 1, x ) & A_CHARTEXT ) == ' ' || (mvinch( y + 1, x ) & A_CHARTEXT) == '|' || ( mvinch( y + 1, x ) & A_CHARTEXT) == '-' ){
                    step = 118;
                    mvaddch( y + 1, x, step );
                    mvaddch( y, x, ' ' );
                    y++;
                }
                else if ( mvinch ( y + 1, x ) == 'O' && ( ( mvinch( y + 2, x ) & A_CHARTEXT ) == ' ' || mvinch ( y + 2, x ) == 'X' ) ) {
                    step = 118;
                    mvaddch( y + 2, x, 'O' );
                    mvaddch( y + 1, x, step );
                    mvaddch( y, x, ' ' );
                    y++;
                }
                else if ( mvinch ( y + 1, x ) == '/' && ( ( mvinch( y + 2, x ) & A_CHARTEXT ) == ' ' || ( mvinch( y + 2, x ) & A_CHARTEXT) == '|' || ( mvinch( y + 2, x ) & A_CHARTEXT) == '-' ) ) {
                    step = 118;
                    mvaddch( y + 2, x, '/' );
                    mvaddch( y + 1, x, step );
                    mvaddch( y, x, ' ' );
                    y++;
                }
            break;

            default:
                continue;
            break;
        }

        if ( ( mvinch( 18, 57 ) & A_CHARTEXT ) == '|' && switch2 == 0 && ( ( mvinch( 7, 33 ) & A_CHARTEXT ) == '/' ) ){
            mvprintw( 18, 60, " " );
            mvprintw( 19, 60, " " );
            switch2 = 1;
        }

        refresh();

    }while (1);
}

void level2(){

    char level2[15][100] = {
        { "  __________________________________________  " },
        { " !       o                                  ! " },
        { " !                    !                     ! " },
        { " !    X               !                X    ! " },
        { " !          ____________________         ___! " },
        { " !o        !                    !       !  #! " },
        { " !_        !   /   Y    Y   /   !       !___! " },
        { " ! !       !                    !           ! " },
        { " !_!       !____________________!           ! " },
        { " !              O  O  O  O                  ! " },
        { " !                                          ! " },
        { " !    X   !                        !   X    ! " },
        { " !                                          ! " },
        { " !                                          ! " },
        { " !__________________________________o_______! " }
    };

    for ( int i = 0; i < 15; i++ ){
        move( 5 + i, 27 );
        printw( "%s", level2[i] );
    }

    char level2_d[3][100] = {
        { "                                              " },
        { " 'Y' fuses light into one beam pointing to    " },
        { " the closest functional object ( Y, /, H )    " }      
    };

    for ( int j = 0; j < 3; j++ ){
        attron( COLOR_PAIR(1) );
        move( 20 + j, 27 );
        printw( "%s", level2_d[j] );
        attroff( COLOR_PAIR(1) );
    }


    int a = ' ';
    char y = 17;
    char x = 49;
    char step = '^';
    int switch0 = 0;
    int switch1 = 0;
    mvaddch ( 17, 49, '^' );

    do {

        attron( COLOR_PAIR(2) );


        if ( mvinch( 8, 33 ) == '#' && mvinch( 16, 33 ) == '#' && mvinch( 8, 66 ) == '#' && mvinch( 16, 66 ) == '#' ){

            if ( ( mvinch( 10, 30 ) & A_CHARTEXT ) == '-' && switch1 == 0 ){
                mvaddch ( 12, 30, ' ' );
                mvaddch ( 12, 28, ' ' );
                switch1 = 1;
            }

            if ( switch0 == 0 ){
                mvaddch( 10, 38, ' ' );
                mvaddch( 10, 59, ' ' );
                switch0 = 1;
            }

            if ( mvinch( 16, 36 ) == '/' && mvinch( 8, 36 ) == 'Y' ){
                for ( int i = 0; i < 7; i++ ){
                    mvaddch( 15 - i, 36, '|' );
                }
                attron( COLOR_PAIR(6) );
                mvaddch( 7, 36, '|' );
                attroff( COLOR_PAIR(6) );
            }

            attron( COLOR_PAIR(2) );

            if ( mvinch( 16, 63 ) == 'Y' && mvinch( 8, 63 ) == '/' ){
                for ( int i = 0; i < 7; i++ ){
                    mvaddch( 15 - i, 63, '|' );
                }
                attron( COLOR_PAIR(6) );
                mvaddch( 17, 63, '|' );
                mvaddch( 18, 63, '|' );
                attroff( COLOR_PAIR(6) );
            }

            attron( COLOR_PAIR(2) );

            if ( ( mvinch ( 18, 63 ) & A_CHARTEXT ) == '|' && ( mvinch ( 7, 36 ) & A_CHARTEXT ) == '|' ){
                for ( int i = 0; i < 39; i++ ){
                    mvaddch ( 10, 68 - i, '-' );
                }
            }

            if ( mvinch( 8, 33 ) == '#' ){
                for ( int i = 0; i < 15; i++ ){
                    if ( mvinch( 8, 34 + i ) == 'Y' ){
                        for ( int j = 0; j < 20; j++ ){
                            if ( mvinch ( 8, 35 + i + j ) != '!' ){
                                mvprintw( 8, 35 + i + j , " ");
                            }
                            else{
                                break;
                            }
                        }
                        break;
                    }
                    mvprintw( 8, 34 + i, "-" );
                }
            }

            if ( mvinch( 16, 33 ) == '#' ){
                for ( int i = 0; i < 3; i++ ){
                    if ( mvinch( 16, 34 + i ) == '/' ){
                        break;
                    }
                    mvprintw( 16, 34 + i, "-" );
                }                
            }

            if ( mvinch( 8, 66 ) == '#' ){
                for ( int i = 0; i < 16; i++ ){
                    if ( mvinch( 8, 65 - i ) == '/' ){
                        for ( int j = 0; j < 20; j++ ){
                            if ( mvinch ( 8, 64 - i - j ) != '!' ){
                                mvprintw( 8, 64 - i - j , " ");
                            }
                            else{
                                break;
                            }
                        }
                        break;
                    }
                    mvprintw( 8, 65 - i, "-" );
                }
            }

            if ( mvinch( 16, 66 ) == '#' ){
                for ( int i = 0; i < 3; i++ ){
                    if ( mvinch( 16, 65 - i ) == 'Y' ){
                        break;
                    }
                    mvprintw( 16, 65 - i, "-" );
                }                
            }
        }

        attroff( COLOR_PAIR(2) );

        refresh();

        if ( mvinch ( 8, 33 ) == 'O' ){
            mvaddch( 8, 33, '#' );
        }

        if ( mvinch ( 8, 66 ) == 'O' ){
            mvaddch( 8, 66, '#' );
        }

        if ( mvinch ( 16, 33 ) == 'O' ){
            mvaddch( 16, 33, '#' );
        }

        if ( mvinch ( 16, 66 ) == 'O' ){
            mvaddch( 16, 66, '#' );
        }

        a = getch();

        if ( mvinch ( 12, 29 ) == '<' ){
            clear();
            attron( COLOR_PAIR(1) );
            mvprintw( 15, 40, "Level 2 Complete" );
            mvprintw( 16, 37, "Press Enter to continue" );
            attroff( COLOR_PAIR(1) );
            a = getch();
        }
        

        if ( a == 81 || a == 113 || a == 10){
            clear();
            break;
        }

        switch(a){
            case KEY_LEFT:
                if ( ( mvinch( y, x - 1 ) & A_CHARTEXT ) == ' ' || (mvinch( y, x - 1 ) & A_CHARTEXT) == '|' || ( mvinch( y, x - 1 ) & A_CHARTEXT) == '-' ){
                    step = 60;
                    mvaddch( y, x - 1, step );
                    mvaddch( y, x, ' ' );
                    x--;
                }
                else if ( mvinch ( y, x - 1 ) == 'O' && ( ( mvinch( y, x - 2 ) & A_CHARTEXT ) == ' ' || mvinch ( y, x - 2 ) == 'X' ) ) {
                    step = 60;
                    mvaddch( y, x - 2, 'O' );
                    mvaddch( y, x - 1, step );
                    mvaddch( y, x, ' ' );
                    x--;
                }
                else if ( mvinch ( y, x - 1 ) == '/' && ( ( mvinch( y, x - 2 ) & A_CHARTEXT ) == ' ' || ( mvinch( y, x - 2 ) & A_CHARTEXT) == '|' || ( mvinch( y, x - 2 ) & A_CHARTEXT) == '-' ) ) {
                    step = 60;
                    mvaddch( y, x - 2, '/' );
                    mvaddch( y, x - 1, step );
                    mvaddch( y, x, ' ' );
                    x--;
                }
                else if ( mvinch ( y, x - 1 ) == 'Y' && ( ( mvinch( y, x - 2 ) & A_CHARTEXT ) == ' ' || ( mvinch( y, x - 2 ) & A_CHARTEXT) == '|' || ( mvinch( y, x - 2 ) & A_CHARTEXT) == '-' ) ) {
                    step = 60;
                    mvaddch( y, x - 2, 'Y' );
                    mvaddch( y, x - 1, step );
                    mvaddch( y, x, ' ' );
                    x--;
                }
            break;

            case KEY_RIGHT:
                if ( ( mvinch( y, x + 1 ) & A_CHARTEXT ) == ' ' || (mvinch( y, x + 1 ) & A_CHARTEXT) == '|' || ( mvinch( y, x + 1 ) & A_CHARTEXT) == '-' ){
                    step = 62;
                    mvaddch( y, x + 1, step );
                    mvaddch( y, x, ' ' );
                    x++;
                }
                else if ( mvinch ( y, x + 1 ) == 'O' && ( ( mvinch( y, x + 2 ) & A_CHARTEXT ) == ' ' || mvinch ( y, x + 2 ) == 'X' ) ) {
                    step = 62;
                    mvaddch( y, x + 2, 'O' );
                    mvaddch( y, x + 1, step );
                    mvaddch( y, x, ' ' );
                    x++;
                }
                else if ( mvinch ( y, x + 1 ) == '/' && ( ( mvinch( y, x + 2 ) & A_CHARTEXT ) == ' ' || ( mvinch( y, x + 2 ) & A_CHARTEXT) == '|' || ( mvinch( y, x + 2 ) & A_CHARTEXT) == '-' ) ) {
                    step = 62;
                    mvaddch( y, x + 2, '/' );
                    mvaddch( y, x + 1, step );
                    mvaddch( y, x, ' ' );
                    x++;
                }
                else if ( mvinch ( y, x + 1 ) == 'Y' && ( ( mvinch( y, x + 2 ) & A_CHARTEXT ) == ' ' || ( mvinch( y, x + 2 ) & A_CHARTEXT) == '|' || ( mvinch( y, x + 2 ) & A_CHARTEXT) == '-' ) ) {
                    step = 62;
                    mvaddch( y, x + 2, 'Y' );
                    mvaddch( y, x + 1, step );
                    mvaddch( y, x, ' ' );
                    x++;
                }
            break;

            case KEY_UP:
                if ( ( mvinch( y - 1, x ) & A_CHARTEXT ) == ' ' || (mvinch( y - 1, x ) & A_CHARTEXT) == '|' || ( mvinch( y - 1, x ) & A_CHARTEXT) == '-' ){
                    step = 94;
                    mvaddch( y - 1, x, step );
                    mvaddch( y, x, ' ' );
                    y--;
                }
                else if ( mvinch ( y - 1, x ) == 'O' && ( ( mvinch( y - 2, x ) & A_CHARTEXT ) == ' ' || mvinch ( y - 2, x ) == 'X' ) ) {
                    step = 94;
                    mvaddch( y - 2, x, 'O' );
                    mvaddch( y - 1, x, step );
                    mvaddch( y, x, ' ' );
                    y--;
                }
                else if ( mvinch ( y - 1, x ) == '/' && ( ( mvinch( y - 2, x ) & A_CHARTEXT ) == ' ' || ( mvinch( y - 2, x ) & A_CHARTEXT) == '|' || ( mvinch( y - 2, x ) & A_CHARTEXT) == '-' ) ) {
                    step = 94;
                    mvaddch( y - 2, x, '/' );
                    mvaddch( y - 1, x, step );
                    mvaddch( y, x, ' ' );
                    y--;
                }
                else if ( mvinch ( y - 1, x ) == 'Y' && ( ( mvinch( y - 2, x ) & A_CHARTEXT ) == ' ' || ( mvinch( y - 2, x ) & A_CHARTEXT) == '|' || ( mvinch( y - 2, x ) & A_CHARTEXT) == '-' ) ) {
                    step = 94;
                    mvaddch( y - 2, x, 'Y' );
                    mvaddch( y - 1, x, step );
                    mvaddch( y, x, ' ' );
                    y--;
                }
            break;

            case KEY_DOWN:
                if ( ( mvinch( y + 1, x ) & A_CHARTEXT ) == ' ' || (mvinch( y + 1, x ) & A_CHARTEXT) == '|' || ( mvinch( y + 1, x ) & A_CHARTEXT) == '-' ){
                    step = 118;
                    mvaddch( y + 1, x, step );
                    mvaddch( y, x, ' ' );
                    y++;
                }
                else if ( mvinch ( y + 1, x ) == 'O' && ( ( mvinch( y + 2, x ) & A_CHARTEXT ) == ' ' || mvinch ( y + 2, x ) == 'X' ) ) {
                    step = 118;
                    mvaddch( y + 2, x, 'O' );
                    mvaddch( y + 1, x, step );
                    mvaddch( y, x, ' ' );
                    y++;
                }
                else if ( mvinch ( y + 1, x ) == '/' && ( ( mvinch( y + 2, x ) & A_CHARTEXT ) == ' ' || ( mvinch( y + 2, x ) & A_CHARTEXT) == '|' || ( mvinch( y + 2, x ) & A_CHARTEXT) == '-' ) ) {
                    step = 118;
                    mvaddch( y + 2, x, '/' );
                    mvaddch( y + 1, x, step );
                    mvaddch( y, x, ' ' );
                    y++;
                }
                else if ( mvinch ( y + 1, x ) == 'Y' && ( ( mvinch( y + 2, x ) & A_CHARTEXT ) == ' ' || ( mvinch( y + 2, x ) & A_CHARTEXT) == '|' || ( mvinch( y + 2, x ) & A_CHARTEXT) == '-' ) ) {
                    step = 118;
                    mvaddch( y + 2, x, 'Y' );
                    mvaddch( y + 1, x, step );
                    mvaddch( y, x, ' ' );
                    y++;
                }
            break;

            default:
                continue;
            break;
        }

        refresh();

    }while (1);
}

void level3(){

    char level3[15][100] = {
        { "  __________________________________________  " },
        { " !                                          ! " },
        { " !o                                        o! " },
        { " !____________________  ____________________! " },
        { " !         !        !  !                    ! " },
        { " !         !    #   !  !          X   O     ! " },
        { " !___      !________!  !                    ! " },
        { " !   !                                O     ! " },
        { " ! / !      _                               ! " },
        { " !   !     !                       !        ! " },
        { " !___!                     ________!________! " },
        { " !                        !                 ! " },
        { " !          X             !  /  /     Y  H  ! " },
        { " !    _                   !                 ! " },
        { " !___!_!_o________________!_________________! " }
    };

    for ( int i = 0; i < 15; i++ ){
        move( 5 + i, 27 );
        printw( "%s", level3[i] );
    }

    char level3_d[2][100] = {
        { "                                              " },
        { " 'H' splits light apeak into 2 lightbeams     " }        
    };

    for ( int j = 0; j < 2; j++ ){
        attron( COLOR_PAIR(1) );
        move( 20 + j, 27 );
        printw( "%s", level3_d[j] );
        attroff( COLOR_PAIR(1) );
    }

    int a = ' ';
    char y = 17;
    char x = 49;
    char step = '^';
    int switch0 = 0;
    int switch1 = 0;
    int switch2 = 0;
    mvaddch ( 17, 49, '^' );

    do {

        attron( COLOR_PAIR(2) );


        if ( mvinch( 17, 39 ) == '#' && mvinch( 10, 61 ) == '#' ){

            if ( ( mvinch( 18, 30 ) & A_CHARTEXT ) == '|' && switch1 == 0 ){
                mvaddch ( 12, 30, ' ' );
                switch1 = 1;
            }

            if ( switch0 == 0 ){
                mvaddch( 16, 53, ' ' );
                mvaddch( 17, 53, ' ' );
                mvaddch( 18, 53, ' ' );
                mvaddch( 19, 53, '_' );
                mvaddch( 12, 32, ' ' );
                mvaddch( 13, 32, ' ' );
                switch0 = 1;
            }

            if ( ( mvinch( 18, 36 ) & A_CHARTEXT ) == '|' && switch2 == 0 ){
                mvaddch( 18, 33, ' ' );
                mvaddch( 19, 33, ' ' );
                switch2 = 1; 
            }

            if ( mvinch( 14, 49 ) == 'Y' && mvinch( 7, 49 ) == 'H' ){
                for ( int i = 0; i < 6; i++ ){
                    attron( COLOR_PAIR(6) );
                    mvaddch( 13 - i, 49, '|' );
                    attroff( COLOR_PAIR(6) );
                }
                for ( int j = 0; j < 20; j++){
                    attron( COLOR_PAIR(2) );
                    mvaddch( 7, 50 + j, '-' );
                    attroff( COLOR_PAIR(2) );                    
                }
                for ( int n = 0; n < 19; n++){
                    attron( COLOR_PAIR(2) );
                    mvaddch( 7, 48 - n, '-' );
                    attroff( COLOR_PAIR(2) );                    
                }
            }

            attron( COLOR_PAIR(2) );

            if ( ( mvinch( 7, 30 ) & A_CHARTEXT ) == '-' && ( mvinch( 7, 69 ) & A_CHARTEXT ) == '-' ){
                mvaddch( 10, 38, ' ' );
            }

            if ( mvinch( 10, 36 ) == '/' ){
                for ( int i = 0; i < 8; i++  ){
                    mvaddch( 11 + i, 36, '|' );
                }
            }

            if ( mvinch( 10, 43 ) == '#'  ){
                for ( int i = 0; i < 14; i++ ){
                    if ( mvinch( 10, 42 - i ) == '!' ){
                        break;
                    }
                    else if ( mvinch( 10, 42 - i ) == '/' ){
                        for ( int j = 0; j < 20; j++ ){
                            if ( mvinch ( 10, 41 - i - j ) != '!' ){
                                mvprintw( 10, 41 - i - j, " ");
                            }
                            else{
                                break;
                            }
                        }
                        break;
                    }
                    mvprintw( 10, 42 - i, "-" );
                }
            }

            if ( mvinch( 17, 39 ) == '#' ){
                for ( int i = 0; i < 3; i++ ){
                    if ( mvinch( 16 - i, 39 ) == '/' ){
                        for ( int j = 0; j < 20; j++ ){
                            if ( mvinch ( 15 - i - j, 39 ) != '_' ){
                                mvprintw( 15 - i - j, 39, " ");
                            }
                            else{
                                break;
                            }
                        }
                        break;
                    }
                    mvprintw( 16 - i, 39, "|" );
                }
            }

            if ( mvinch( 10, 61 ) == '#' ){
                for ( int i = 0; i < 4; i++ ){
                    if ( mvinch( 11 + i, 61 ) == '/' ){
                        for ( int j = 0; j < 20; j++ ){
                            if ( mvinch ( 12 + i + j, 61 ) != '_' ){
                                mvprintw( 12 + i + j, 61 , " ");
                            }
                            else{
                                break;
                            }
                        }
                        break;
                    }
                    mvprintw( 11 + i, 61, "|" );
                }
            }

            if (  mvinch( 14, 39 ) == '/' && mvinch( 14, 61 ) == '/' ){
                for ( int i = 0; i < 21; i++ ){
                    if ( mvinch( 14, 40 + i ) == 'H' ){
                        break;
                    }
                    else if ( mvinch( 14 , 40 + i ) == 'Y' ){
                        for ( int j = 0; j < 20; j++ ){
                            if ( mvinch ( 14, 41 ) != '/' ){
                                mvprintw( 14, 41 , "-");
                            }
                            else{
                                break;
                            }
                        }
                        break;
                    }
                    mvprintw( 14, 40 + i, "-" );
                }
            }
        }


        attroff( COLOR_PAIR(2) );

        refresh();

        if ( mvinch ( 17, 39 ) == 'O' ){
            mvaddch( 17, 39, '#' );
        }

        if ( mvinch ( 10, 61 ) == 'O' ){
            mvaddch( 10, 61, '#' );
        }

        if ( mvinch ( 20, 33 ) == 'v' ){
            clear();
            attron( COLOR_PAIR(1) );
            mvprintw( 15, 40, "Level 3 Complete" );
            mvprintw( 16, 37, "Press Enter to continue" );
            attroff( COLOR_PAIR(1) );
            a = getch();
        }

        a = getch();
        

        if ( a == 81 || a == 113 || a == 10){
            clear();
            break;
        }

        switch(a){
            case KEY_LEFT:
                if ( ( mvinch( y, x - 1 ) & A_CHARTEXT ) == ' ' || (mvinch( y, x - 1 ) & A_CHARTEXT) == '|' || ( mvinch( y, x - 1 ) & A_CHARTEXT) == '-' ){
                    step = 60;
                    mvaddch( y, x - 1, step );
                    mvaddch( y, x, ' ' );
                    x--;
                }
                else if ( mvinch ( y, x - 1 ) == 'O' && ( ( mvinch( y, x - 2 ) & A_CHARTEXT ) == ' ' || mvinch ( y, x - 2 ) == 'X' ) ) {
                    step = 60;
                    mvaddch( y, x - 2, 'O' );
                    mvaddch( y, x - 1, step );
                    mvaddch( y, x, ' ' );
                    x--;
                }
                else if ( mvinch ( y, x - 1 ) == '/' && ( ( mvinch( y, x - 2 ) & A_CHARTEXT ) == ' ' || ( mvinch( y, x - 2 ) & A_CHARTEXT) == '|' || ( mvinch( y, x - 2 ) & A_CHARTEXT) == '-' ) ) {
                    step = 60;
                    mvaddch( y, x - 2, '/' );
                    mvaddch( y, x - 1, step );
                    mvaddch( y, x, ' ' );
                    x--;
                }
                else if ( mvinch ( y, x - 1 ) == 'Y' && ( ( mvinch( y, x - 2 ) & A_CHARTEXT ) == ' ' || ( mvinch( y, x - 2 ) & A_CHARTEXT) == '|' || ( mvinch( y, x - 2 ) & A_CHARTEXT) == '-' ) ) {
                    step = 60;
                    mvaddch( y, x - 2, 'Y' );
                    mvaddch( y, x - 1, step );
                    mvaddch( y, x, ' ' );
                    x--;
                }
                else if ( mvinch ( y, x - 1 ) == 'H' && ( ( mvinch( y, x - 2 ) & A_CHARTEXT ) == ' ' || ( mvinch( y, x - 2 ) & A_CHARTEXT) == '|' || ( mvinch( y, x - 2 ) & A_CHARTEXT) == '-' ) ) {
                    step = 60;
                    mvaddch( y, x - 2, 'H' );
                    mvaddch( y, x - 1, step );
                    mvaddch( y, x, ' ' );
                    x--;
                }
            break;

            case KEY_RIGHT:
                if ( ( mvinch( y, x + 1 ) & A_CHARTEXT ) == ' ' || (mvinch( y, x + 1 ) & A_CHARTEXT) == '|' || ( mvinch( y, x + 1 ) & A_CHARTEXT) == '-' ){
                    step = 62;
                    mvaddch( y, x + 1, step );
                    mvaddch( y, x, ' ' );
                    x++;
                }
                else if ( mvinch ( y, x + 1 ) == 'O' && ( ( mvinch( y, x + 2 ) & A_CHARTEXT ) == ' ' || mvinch ( y, x + 2 ) == 'X' ) ) {
                    step = 62;
                    mvaddch( y, x + 2, 'O' );
                    mvaddch( y, x + 1, step );
                    mvaddch( y, x, ' ' );
                    x++;
                }
                else if ( mvinch ( y, x + 1 ) == '/' && ( ( mvinch( y, x + 2 ) & A_CHARTEXT ) == ' ' || ( mvinch( y, x + 2 ) & A_CHARTEXT) == '|' || ( mvinch( y, x + 2 ) & A_CHARTEXT) == '-' ) ) {
                    step = 62;
                    mvaddch( y, x + 2, '/' );
                    mvaddch( y, x + 1, step );
                    mvaddch( y, x, ' ' );
                    x++;
                }
                else if ( mvinch ( y, x + 1 ) == 'Y' && ( ( mvinch( y, x + 2 ) & A_CHARTEXT ) == ' ' || ( mvinch( y, x + 2 ) & A_CHARTEXT) == '|' || ( mvinch( y, x + 2 ) & A_CHARTEXT) == '-' ) ) {
                    step = 62;
                    mvaddch( y, x + 2, 'Y' );
                    mvaddch( y, x + 1, step );
                    mvaddch( y, x, ' ' );
                    x++;
                }
                else if ( mvinch ( y, x + 1 ) == 'H' && ( ( mvinch( y, x + 2 ) & A_CHARTEXT ) == ' ' || ( mvinch( y, x + 2 ) & A_CHARTEXT) == '|' || ( mvinch( y, x + 2 ) & A_CHARTEXT) == '-' ) ) {
                    step = 62;
                    mvaddch( y, x + 2, 'H' );
                    mvaddch( y, x + 1, step );
                    mvaddch( y, x, ' ' );
                    x++;
                }
            break;

            case KEY_UP:
                if ( ( mvinch( y - 1, x ) & A_CHARTEXT ) == ' ' || (mvinch( y - 1, x ) & A_CHARTEXT) == '|' || ( mvinch( y - 1, x ) & A_CHARTEXT) == '-' ){
                    step = 94;
                    mvaddch( y - 1, x, step );
                    mvaddch( y, x, ' ' );
                    y--;
                }
                else if ( mvinch ( y - 1, x ) == 'O' && ( ( mvinch( y - 2, x ) & A_CHARTEXT ) == ' ' || mvinch ( y - 2, x ) == 'X' ) ) {
                    step = 94;
                    mvaddch( y - 2, x, 'O' );
                    mvaddch( y - 1, x, step );
                    mvaddch( y, x, ' ' );
                    y--;
                }
                else if ( mvinch ( y - 1, x ) == '/' && ( ( mvinch( y - 2, x ) & A_CHARTEXT ) == ' ' || ( mvinch( y - 2, x ) & A_CHARTEXT) == '|' || ( mvinch( y - 2, x ) & A_CHARTEXT) == '-' ) ) {
                    step = 94;
                    mvaddch( y - 2, x, '/' );
                    mvaddch( y - 1, x, step );
                    mvaddch( y, x, ' ' );
                    y--;
                }
                else if ( mvinch ( y - 1, x ) == 'Y' && ( ( mvinch( y - 2, x ) & A_CHARTEXT ) == ' ' || ( mvinch( y - 2, x ) & A_CHARTEXT) == '|' || ( mvinch( y - 2, x ) & A_CHARTEXT) == '-' ) ) {
                    step = 94;
                    mvaddch( y - 2, x, 'Y' );
                    mvaddch( y - 1, x, step );
                    mvaddch( y, x, ' ' );
                    y--;
                }
                else if ( mvinch ( y - 1, x ) == 'H' && ( ( mvinch( y - 2, x ) & A_CHARTEXT ) == ' ' || ( mvinch( y - 2, x ) & A_CHARTEXT) == '|' || ( mvinch( y - 2, x ) & A_CHARTEXT) == '-' ) ) {
                    step = 94;
                    mvaddch( y - 2, x, 'H' );
                    mvaddch( y - 1, x, step );
                    mvaddch( y, x, ' ' );
                    y--;
                }
            break;

            case KEY_DOWN:
                if ( ( mvinch( y + 1, x ) & A_CHARTEXT ) == ' ' || (mvinch( y + 1, x ) & A_CHARTEXT) == '|' || ( mvinch( y + 1, x ) & A_CHARTEXT) == '-' ){
                    step = 118;
                    mvaddch( y + 1, x, step );
                    mvaddch( y, x, ' ' );
                    y++;
                }
                else if ( mvinch ( y + 1, x ) == 'O' && ( ( mvinch( y + 2, x ) & A_CHARTEXT ) == ' ' || mvinch ( y + 2, x ) == 'X' ) ) {
                    step = 118;
                    mvaddch( y + 2, x, 'O' );
                    mvaddch( y + 1, x, step );
                    mvaddch( y, x, ' ' );
                    y++;
                }
                else if ( mvinch ( y + 1, x ) == '/' && ( ( mvinch( y + 2, x ) & A_CHARTEXT ) == ' ' || ( mvinch( y + 2, x ) & A_CHARTEXT) == '|' || ( mvinch( y + 2, x ) & A_CHARTEXT) == '-' ) ) {
                    step = 118;
                    mvaddch( y + 2, x, '/' );
                    mvaddch( y + 1, x, step );
                    mvaddch( y, x, ' ' );
                    y++;
                }
                else if ( mvinch ( y + 1, x ) == 'Y' && ( ( mvinch( y + 2, x ) & A_CHARTEXT ) == ' ' || ( mvinch( y + 2, x ) & A_CHARTEXT) == '|' || ( mvinch( y + 2, x ) & A_CHARTEXT) == '-' ) ) {
                    step = 118;
                    mvaddch( y + 2, x, 'Y' );
                    mvaddch( y + 1, x, step );
                    mvaddch( y, x, ' ' );
                    y++;
                }
                else if ( mvinch ( y + 1, x ) == 'H' && ( ( mvinch( y + 2, x ) & A_CHARTEXT ) == ' ' || ( mvinch( y + 2, x ) & A_CHARTEXT) == '|' || ( mvinch( y + 2, x ) & A_CHARTEXT) == '-' ) ) {
                    step = 118;
                    mvaddch( y + 2, x, 'H' );
                    mvaddch( y + 1, x, step );
                    mvaddch( y, x, ' ' );
                    y++;
                }
            break;

            default:
                continue;
            break;
        }

        refresh();

    }while (1);
}

void instructions(){

    int b = ' ';

    refresh();

    do{
        attron( COLOR_PAIR(6) );
        mvprintw ( 5, 30, "1. Use arrows to move on map" );
        attroff( COLOR_PAIR(6) );
        attron( COLOR_PAIR(2) );
        mvprintw ( 7, 30, "2. Dont get yourself lost in the light =) " );
        attroff( COLOR_PAIR(2) );
        attron( COLOR_PAIR(1) );
        mvprintw ( 9, 30, "3. Put lightsources (O) on the marked spot (X)" );
        attroff( COLOR_PAIR(1) );
        attron( COLOR_PAIR(4) );
        mvprintw ( 11, 30, "4. Lightsources become immovable when put on the mark" );
        attroff( COLOR_PAIR(4) );
        attron( COLOR_PAIR(3) );
        mvprintw ( 13, 30, "5. When all sources are on marks, storage with" );
        mvprintw ( 14, 30, "   special mirrors will open" );
        attroff( COLOR_PAIR(3) );
        attron( COLOR_PAIR(5) );
        mvprintw ( 16, 30, "6. Mirrors reflect light only when source and" );
        mvprintw ( 17, 30, "   and target object are in the right spot" );
        attroff( COLOR_PAIR(5) );
        attron( COLOR_PAIR(6) );
        mvprintw ( 19, 30, "7. Get light to the final spot marked (o)" );
        mvprintw ( 20, 30, "   this will open marked finish" );
        attroff( COLOR_PAIR(6) );
        attron( COLOR_PAIR(2) );
        mvprintw ( 22, 30, "8. Press Q/q to quit level u are in" );
        attroff( COLOR_PAIR(2) );
        attron( COLOR_PAIR(1) );
        mvprintw ( 24, 30, "9. Have fun" );
        attroff( COLOR_PAIR(1) );

        b = getch();

        if ( b == 81 || b == 113 ){
            refresh();
            break;
        }

    }while (1);

}
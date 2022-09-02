#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include "hangman.h"

int get_word(char secret[]){
    // check if file exists first and is readable
    FILE *fp = fopen(WORDLIST_FILENAME, "rb");
    if( fp == NULL ){
        fprintf(stderr, "No such file or directory: %s\n", WORDLIST_FILENAME);
        return 1;
    }

    // get the filesize first
    struct stat st;
    stat(WORDLIST_FILENAME, &st);
    long int size = st.st_size;

    do{
        // generate random number between 0 and filesize
        long int random = (rand() % size) + 1;
        // seek to the random position of file
        fseek(fp, random, SEEK_SET);
        // get next word in row ;)
        int result = fscanf(fp, "%*s %20s", secret);
        if( result != EOF )
            break;
    }while(1);

    fclose(fp);

    return 0;
}

int is_word_guessed( const char secret[], const char letters_guessed[] ){
    int c = 0;
    char testing_alphabet[27] = "abcdefghijklmnopqrstuvwxyz";
    size_t secret_len = strlen(secret); 
    size_t letters_len = strlen(letters_guessed);
    char duplicate[30];
    strcpy (duplicate, secret);
    for ( int m = 0; m < secret_len; m++){
        for ( int n = m + 1; n < secret_len; n++ ){
            if ( secret[m] == secret[n] ){
                duplicate[n] = '0'; //zapisne pole kde sa nahradzaju duplikaty za 0
            }
        }
    }
    int cnt = 0;
    size_t duplicate_len = strlen(duplicate);
    char array[duplicate_len+1];
    for ( int a = 0; a < 26; a++ ){
        for ( size_t b = 0; b < duplicate_len; b++ ){
            if ( testing_alphabet[a] == duplicate[b] ){
                array[cnt] = testing_alphabet[a];
                cnt++;
            }
        }
    }
    array[cnt] = '\0';
    size_t u = strlen(array);
    for ( size_t i = 0; i < letters_len; i++ ){
        for ( int j = 0; j < u; j++ ){
            if ( letters_guessed[i] == array[j] ){
                c++;
            }
        }
    }

    if ( cnt == c ){
        return 1;
    }
    else{
        return 0;
    }
}

void get_guessed_word(const char secret[], const char letters_guessed[], char guessed_word[]){
    size_t secret_len = strlen(secret); 
    size_t letters_len = strlen(letters_guessed);
    int k = 0;
    for ( int a = 0; a < secret_len; a++ ){
        guessed_word[a] = '_';

        k++;
    }
    guessed_word[k] = '\0';
    for ( size_t i = 0; i < letters_len; i++ ){
        for ( int j = 0; j < secret_len; j++ ){
            if ( letters_guessed[i] == secret[j] ){
                guessed_word[j] = secret[j];
            }
        }
    }
}

void get_spaced_guessed_word( const char guessed_word[], char spaced_guessed_word[] ){
    int iterations = 0;
    int size_guessed_word = strlen(guessed_word);
    for ( int q = 0; q < (2 * size_guessed_word); q++ ){
        if ( q == 0 ){
            spaced_guessed_word[q] = guessed_word[q];
        }
        else if ( q % 2 == 0 ){
            spaced_guessed_word[q] = guessed_word[q/2];
        }
        else{
            spaced_guessed_word[q] = ' ';
        }
        iterations++;
    }
    spaced_guessed_word[iterations - 1] = '\0';
}

void get_available_letters(const char letters_guessed[], char available_letters[]){
    char alphabet[27] = "abcdefghijklmnopqrstuvwxyz";
    size_t letters_len = strlen(letters_guessed);
    char letters[27];
    strcpy (letters, alphabet);

    for ( int i = 0; i < 26; i++ ){
        for ( size_t j = 0; j < letters_len; j++ ){
            if ( alphabet[i] == letters_guessed[j] ){
                letters[i] = ' ';
            }
        }
    }
    int a = 0;
    for ( int k = 0; k < 26; k++ ){
        if ( letters[k] == alphabet[k] ){
            available_letters[a] = alphabet[k];
            a++;
        }
    }
    available_letters[a] = '\0';

}

void hangman(const char secret[]){
    int result;
    int index = 0;
    int m = strlen(secret);
    int r = 2; // ak sa tato premenna bude rovnat 1, tak hrac vyhral
    char letters_guessed[27];
    char available_letters[27];
    char guessed_word[45];
    char spaced_guessed_word[60];
    int count = 8;
    //int q = strlen(letters_guessed);
    printf( "Welcome to the game, Hangman!\nI am thinking of a word that is %d letters long.\n", m );
    printf( "-------------\n" );

    while ( count > 0 ){
        char testing_letters[30];
        get_available_letters(letters_guessed, available_letters);
        printf( "You have %d guesses left.\n", count );
        printf( "Available letters: %s\n", available_letters);
        printf( "Please guess a letter: " );
        scanf( "%s", testing_letters );

        int w = strlen( testing_letters );
        if ( w != 1 ){
            testing_letters[w] = '\0';
            result = strcmp(testing_letters, secret);
            if ( result == 0 ){
                r = 1;
                count = 0;
            }
            else{
                r = 0;
                count = 0;
            }
            if ( r == 1 ){
                printf( "Congratulations, you won!\n" );
                break;
            }
            if ( r == 0 && count == 0 ){
                printf( "Sorry, bad guess. The word was %s.\n", secret );
                break;
            }
        }
        else{
            testing_letters[w] = '\0';
            int log = 0;
            if ( testing_letters[0] >= 65 && testing_letters[0] <= 90 ){
                testing_letters[0] = testing_letters[0] + 32;
                for ( int f = 0; f < 26; f++ ){
                    if ( testing_letters[0] == letters_guessed[f] ){
                        printf( "Oops! You've already guessed that letter: " );
                        log++;
                    }
                }
                if ( log == 0 ){
                    for ( int q = 0; q < 26; q++ ){
                        if ( testing_letters[0] == available_letters[q] ){
                            for ( int t = 0; t < m; t++ ){
                                if ( testing_letters[0] == secret[t] ){
                                    printf( "Good guess: " );
                                    letters_guessed[index] = testing_letters[0];
                                    index++;
                                    letters_guessed[index] = '\0';
                                    break;
                                }
                                if ( t == (m - 1) ){
                                    printf( "Oops! That letter is not in my word: " );
                                    letters_guessed[index] = testing_letters[0];
                                    index++;
                                    letters_guessed[index] = '\0';
                                    count--;
                                    break;
                                }
                            }
                        }
                    }
                }

                get_guessed_word(secret, letters_guessed, guessed_word);
                get_spaced_guessed_word(guessed_word, spaced_guessed_word);
                printf( "%s\n", spaced_guessed_word );

            }
            else if ( testing_letters[0] >= 97 && testing_letters[0] <= 122 ){
                int log = 0;
                for ( int f = 0; f < 26; f++ ){
                    if ( testing_letters[0] == letters_guessed[f] ){
                        printf( "Oops! You've already guessed that letter: " );
                        log++;
                    }
                }
                if ( log == 0 ){
                    for ( int q = 0; q < 26; q++ ){
                        if ( testing_letters[0] == available_letters[q] ){
                            for ( int t = 0; t < m; t++ ){
                                if ( testing_letters[0] == secret[t] ){
                                    printf( "Good guess: " );
                                    letters_guessed[index] = testing_letters[0];
                                    index++;
                                    letters_guessed[index] = '\0';
                                    break;
                                }
                                if ( t == (m - 1) ){
                                    printf( "Oops! That letter is not in my word: " );
                                    letters_guessed[index] = testing_letters[0];
                                    index++;
                                    letters_guessed[index] = '\0';
                                    count--;
                                    break;
                                }
                            }
                        }
                    }
                }

                get_guessed_word(secret, letters_guessed, guessed_word);
                get_spaced_guessed_word(guessed_word, spaced_guessed_word);
                printf( "%s\n", spaced_guessed_word );

            }
            else{
                printf( "Oops! '%s' is not a valid letter: ", testing_letters );
                get_guessed_word(secret, letters_guessed, guessed_word);
                get_spaced_guessed_word(guessed_word, spaced_guessed_word);
                printf( "%s\n", spaced_guessed_word );

            }
        }
        r = is_word_guessed(secret, letters_guessed);
        printf( "-------------\n" );
        if ( r == 1 ){
            printf( "Congratulations, you won!\n" );
            break;
        }
        if ( r == 0 && count == 0 ){
            printf( "Sorry, you ran out of guesses. The word was %s.\n", secret );
        }
    }
}
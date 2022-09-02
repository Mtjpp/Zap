#include <stdio.h>
#include <stdlib.h>


int main(int argc, char* argv[]){
  
    FILE *fp = fopen (argv[1], "r");
    FILE *fp2 = fopen (argv[2], "w");

    char string[50];
    int c = 0;
    int l = 0;
    int a = 0;
    int o = 0;

    char ch = fgetc(fp); 
    while ( ch != EOF ){
        if ( ch == 32 ){
            ch = fgetc(fp);
        }
        else{
            for (int i = 0; i < 5; i++){
                string[i] = ch;
                ch = fgetc(fp);
            }
            string[5] = '\0';

            while ( ch != 32 ){
                ch = fgetc(fp);
            }

            if ( string[0] == 83 ){
                c++;
            }
            if ( string[1] == 84 ){
                c++;
            }
            if ( string[2] == 65 ){
                c++;
            }
            if ( string[3] == 82 ){
                c++;
            }
            if ( string[4] == 84 ){
                c++;
            }
        }
        if ( c == 5 ){
            break;
        }
    }

    c = 0;
    while ( ch != EOF ){
        if ( ch == 32 ){
            ch = fgetc(fp);
            l++;
        }
        else{
            a = 0;
            for (int i = 0; i < 4; i++){
                a++;
                string[i] = ch;
                if ( string[i] == ' ' ){
                    break;
                }
                if( a < 4 ){
                    ch = fgetc(fp);
                }
            }
            string[4] = '\0';
            

            if ( string[0] == 83 && string[1] == 84 && string[2] == 79 && string[3] == 80 ){
                break;
            }
            
            if ( c != 4 && l == 2 ){
                o++;
                if ( o > 1 ){
                    fputc( 32, fp2 );
                }
                for ( int j = 0; j < 4; j++ ){
                    ch = string[j];
                    if ( ch == 32 ){
                        break; 
                    }
                    else{
                        fputc( ch, fp2 );
                    }
                    l = 0;
                }

                if ( ch != 32 ){
                    ch = fgetc(fp);
                }

                while ( ch != 32 ){
                    fputc( ch, fp2 );
                    ch = fgetc(fp);
                }
            }
            else{
                while ( ch != 32 ){
                    ch = fgetc(fp);
                }
            }    
        }
    }


    fclose(fp);
    fclose(fp2);

    return 0;
}
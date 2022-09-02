#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
  
    FILE *fp = fopen (argv[1], "r");

    unsigned long int a = 0;

    char ch = fgetc(fp);
    while ( ch != EOF ){
        if ( ch == 'a' || ch == 'A' ){
            ch = fgetc(fp);
            if ( ch == 'n' || ch == 'N' ){
                ch = fgetc(fp);
                if ( ch == 'a' || ch == 'A' ){
                    ch = fgetc(fp);
                    if ( ch == 'n' || ch == 'N' ){
                        ch = fgetc(fp);
                        if ( ch == 'a' || ch == 'A' ){
                            ch = fgetc(fp);
                            if ( ch == 's' || ch == 'S' ){
                                a++;
                            }
                        }
                        else{
                            ch = fgetc(fp);
                            continue;
                        }
                    }
                    else{
                        ch = fgetc(fp);
                        continue;
                    }
                }
                else{
                    ch = fgetc(fp);
                    continue;
                }
            }
            else{
                ch = fgetc(fp);
                continue;
            }
        }
        else{
            ch = fgetc(fp);
            continue;
        }
    }

    fclose(fp);

    FILE *fp2 = fopen (argv[1], "w");

    for ( long int i = 100000000; i != 1; i = i / 10 ){
        int fuse = 0;
        fuse = a / i;
        if ( fuse == 0 ){
            continue;
        }
        else{
            fuse = fuse + 48;
            fputc( fuse, fp2 );
            a = a % i;
        }
    }
    
    a = a + 48;
    fputc( a, fp2 );

    fclose(fp2);

    return 0;
}
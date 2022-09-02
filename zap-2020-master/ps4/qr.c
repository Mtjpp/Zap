#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<stdbool.h>

void encode_char(const char character, bool bits[8]);
char decode_byte(const bool bits[8]);
void encode_string(const char string[], bool bytes[strlen(string)+1][8]);
void decode_bytes(const int rows, bool bytes[rows][8], char string[rows]);
void bytes_to_blocks(const int cols, const int offset, bool blocks[offset*8][cols], const int rows, bool bytes[rows][8]);
void blocks_to_bytes(const int cols, const int offset, bool blocks[offset*8][cols], const int rows, bool bytes[rows][8]);

int main(){

    bool bytes3[7][8] = {
    {0,1,0,0,1,0,0,0},
    {0,1,1,0,0,1,0,1},
    {0,1,1,0,1,1,0,0},
    {0,1,1,0,1,1,0,0},
    {0,1,1,0,1,1,1,1},
    {0,0,1,0,0,0,0,1},
    {0,0,0,0,0,0,0,0}
    };
    char string[7];
    decode_bytes(7, bytes3, string);
    printf("%s\n", string);

    int length = 4+1, cols = 3, offset = 2;
    bool bytes1[4+1][8] = {
    {0,1,0,0,0,0,0,1},
    {0,1,1,0,1,0,0,0},
    {0,1,1,0,1,1,1,1},
    {0,1,1,0,1,0,1,0},
    {0,0,0,0,0,0,0,0}
    };
    bool blocks1[offset*8][cols];
    bytes_to_blocks(cols, offset, blocks1, length, bytes1);
    for(int j = 0; j < offset*8; j++){
        for(int i = 0; i < cols; i++){
            printf("%d ", (blocks1[j][i] == true) ? 1 : 0);
        }
        printf("\n");
        if(j % 8 == 7){
            printf("\n");
        }
    }

    bool blocks2[2*8][3] = {
    {0,0,0},
    {1,1,1},
    {0,1,1},
    {0,0,0},
    {0,1,1},
    {0,0,1},
    {0,0,1},
    {1,0,1},
    {0,0,0},
    {1,0,0},
    {1,0,0},
    {0,0,0},
    {1,0,0},
    {0,0,0},
    {1,0,0},
    {0,0,0}
    };
    bool bytes2[length][8];
    blocks_to_bytes(3, 2, blocks2, length, bytes2);
    for(int j = 0; j < length; j++){
        for(int i = 0; i < 8; i++){
            printf("%d", bytes2[j][i]);
        }
        printf("\n");
    }

    return 0;
}

void encode_char(const char character, bool bits[8]){
    char charac = character;
    int j = 128;
    for ( int i = 0; i < 8; i++ ){
        int check = 0;
        check = charac - j;
        if ( check < 0 ){
            bits[i] = 0;
        }
        else{
            bits[i] = 1;
            charac = charac - j;
        }
        j = j / 2;
    }
}

char decode_byte(const bool bits[8]){
    int count = 0;
    int j = 128;
    for ( int i = 0; i < 8; i++ ){
        count = ( bits[i] ) * j + count;
        j = j / 2; 
    }
    char a;
    a = count;
    return a;
}

void encode_string(const char string[], bool bytes[strlen(string)+1][8]){
    int o = strlen(string);
    char string1[o+1];
    strcpy(string1, string);
    bool bits1[8];
    for ( int a = 0; a < o + 1; a++ ){
        for ( int b = 0; b < 8; b++ ){
            encode_char( string[a], bits1);
            bytes[a][b] = bits1[b];
        }
    }
}

void decode_bytes(const int rows, bool bytes[rows][8], char string[rows]){
    for ( int i = 0; i < rows; i++ ){
        bool tempo[8];
        for ( int j = 0; j < 8; j++ ){
            tempo[j] = bytes[i][j];
        }
        char letter = decode_byte(tempo);
        string[i] = letter;
    }
    string[rows] = '\0';
}

void bytes_to_blocks(const int cols, const int offset, bool blocks[offset*8][cols], const int rows, bool bytes[rows][8]){
    int size = 0;
    size = offset * cols;
    bool tempo[8][size];
    for ( int i = 0; i < 8; i++ ){
        for ( int j = 0; j < rows; j++ ){
            tempo[i][j] = bytes[j][i];
        }
    }
    for ( int w = 0; w < 8; w++){
        for ( int e = rows; e < size; e++ ){
            tempo[w][e] = '\0';
        }
    }
    for ( int off = 0; off < offset + 0; off++ ){
        for ( int a = 0; a < cols; a++ ){
            for ( int b = 0; b < 8; b++ ){
                int YM = 0;
                int XM = 0;
                YM = b + ( 8 * off );
                XM = a + ( cols * off );
                blocks[YM][a] = tempo[b][XM];
            }
        }
    }   
}

void blocks_to_bytes(const int cols, const int offset, bool blocks[offset*8][cols], const int rows, bool bytes[rows][8]){
    int size = 0;
    size = offset * cols;
    bool tempo[8][size];
    for ( int off = 0; off < offset + 0; off++ ){
        for ( int a = 0; a < cols; a++ ){
            for ( int b = 0; b < 8; b++ ){
                int YM = 0;
                int XM = 0;
                YM = b + ( 8 * off );
                XM = a + ( cols * off );
                tempo[b][XM] = blocks[YM][a];
            }
        }
    }
    for ( int i = 0; i < 8; i++ ){
        for ( int j = 0; j < rows; j++ ){
            bytes[j][i] = tempo[i][j];
        }
    }
}
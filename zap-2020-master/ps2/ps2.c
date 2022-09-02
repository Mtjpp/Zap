#include<stdio.h>

float lift_a_car( const int, const int, const int );
float unit_price( const float, const int, const int );
int collatz( const int number );
int opposite_number( const int n, const int number );
void counter( const int input_array[], const int array_size, int result_array[2] );
unsigned long sum_squared( const int line );
int array_min( const int input_array[], const int array_size );
int array_max( const int input_array[], const int array_size );
unsigned long special_counter( const int input_array[], const int array_size );
int special_numbers( const int input_array[], const int array_size, int result_array[] );

int main(){



    return 0;
}

float lift_a_car( const int stick_length, const int human_weight, const int car_weight ){
    float m1 = car_weight;
    float m2 = human_weight;
    float r = stick_length;
    float r1;
    float r2;

    r2 = r * m1 / (m1 + m2);
    r1 = r - r2;
    int p = r1 * 100 + 0.5;
    float o = p / 100.0;

    return o;
}

float unit_price( const float pack_price, const int rolls_count, const int pieces_count ){ // jednotkova cena na 100 kusov
    float x = pack_price;
    int y = rolls_count;
    int z = pieces_count;

    float pieces_all = y * z;
    float divider = pieces_all / 100;
    float a = x / divider;
    int p = a * 100 + 0.5;
    float o = p / 100.0;

    return o;
}

int collatz( const int number ){
    int x = number;
    int i = 0;
    while ( x > 1 ){
        if ( x % 2 == 0 ){
            x = x / 2;
        }
        else{
            x = ( 3 * x ) + 1;
        }
        i = i + 1;
    }
    i = i + 1;
    return i;
}

int opposite_number( const int n, const int number ){
    int x = n;
    int a = number;
    int b = x / 2;
    int i;
    if ( a < b ){
        i = a + b;
        return i;
    }
    else if ( a == b ){
        i = 0;
        return i;
    }
    else{
        i = a - b;
        return i;
    }
}

void counter ( const int input_array[], const int array_size, int result_array[2] ){
    int x = array_size;
    int y = 0;
    int z = 0;

    for (int i = 0; i < x; i = i + 2){
        y = y + input_array [i];

    }
    
    result_array [0] = y;

    for (int j = 1; j < x; j = j + 2){
        z = z + input_array [j];

    }

    result_array [1] = z;
}

unsigned long sum_squared( const int line ){ // 1 4 6 4 1
    int x = line;

    unsigned long a = 1;
    unsigned long r = 0;

    for (int i = 1; i < x; i++){
        a = a * (x - (i - 1)) / ( i );
        //printf("%ld\n", a);
        r = r + ( a*a );
    }

    r = r + 2;
    return r;
}

int array_min( const int input_array[], const int array_size ){
    int x = array_size;

    if ( input_array == NULL ){
        return -1;
    }

    int min = input_array[0];

    for ( int i = 1; i < x; i++ ){
        if ( min > input_array[i] ){
            min = input_array[i];
        }
    }

    return min;
}

int array_max( const int input_array[], const int array_size ){
    int x = array_size;

    if ( input_array == NULL ){
        return -1;
    }

    int max = input_array[0];

    for ( int i = 1; i < x; i++ ){
        if ( max < input_array[i] ){
            max = input_array[i];
        }
    }

    return max;
}

unsigned long special_counter( const int input_array[], const int array_size ){
    int x = array_size;

    unsigned long sum1 = 0;
    unsigned long sum2 = 0;
    unsigned long sqrt = 0;

    for ( int i = 0; i < x; i = i + 2 ){
        sum1 = sum1 + input_array[i];
    }

    for ( int j = 1; j < x; j = j + 2){
        sqrt = input_array[j] * input_array[j];
        sum2 = sum2 + sqrt;
    }

    unsigned long sum = 0;
    sum = sum1 + sum2;

    return sum;
}

int special_numbers( const int input_array[], const int array_size, int result_array[] ){
    int x = array_size;
    int p = 0;

    for ( int i = 0; i < x; i++ ){
        int sum = 0;
        for ( int j = i + 1; j < x; j++ ){
            sum = sum + input_array[j];
        }
        if ( sum < input_array[i] ){
            result_array[p] = input_array[i];
            p++;
        }
    }

    return p;
}
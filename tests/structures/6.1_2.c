#include <stdio.h>
#include <math.h>

int main () {

    struct pt  {
        int x;
        int y;
    };

    double dist = 0.0, sum = 0.0, sqrt ( double );

    struct pt maxpt = { 20, 30 };
    struct pt p2 = { 10, 50 };

    printf ( "maxpt.x = %d; maxpt.y = %d;\n", maxpt.x, maxpt.y );
    sum = ( ( double ) maxpt.x * maxpt.x + ( double ) maxpt.y * maxpt.y );
    dist = sqrt ( sum );
    printf ( "sqrt = %f;\n", dist );

    struct rect {
        struct pt maxpt;
        struct pt p2;
    };    

    struct rect screen;
    
    printf ( "screen.maxpt.x = %d;\n", screen.maxpt.x );
    printf ( "screen.p2.y = %d;\n", screen.p2.y );

    return 0;

}

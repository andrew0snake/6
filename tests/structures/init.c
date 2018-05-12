#include <stdio.h>

int main () {

    typedef struct point pt;

    struct point {
        int x;
        int y;
    };
    
    pt one = { 5, 8 };

    printf ( "\nstructure one has members x = %d; and y = %d;\n\n", one.x, one.y ); 


//    typedef struct football_club {
    typedef struct {
        char name [ 20 ];
        int league;
        float balls;
    } f_club;

    f_club a = { "cska", 1, 24.5 };
    f_club b = { "zenit", 2, 34.7 };   
    f_club c; 
    c = ( f_club ) { "spartak", 3, 15.2 };

    printf ( "\nstructure a has members name = %7s; league = %d; and balls = %f;\n", a.name, a.league, a.balls ); 
    printf ( "structure b has members name = %7s; league = %d; and balls = %f;\n", b.name, b.league, b.balls ); 
    printf ( "structure c has members name = %7s; league = %d; and balls = %f;\n\n", c.name, c.league, c.balls ); 


    return 0;

}

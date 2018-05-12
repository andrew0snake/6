#include <stdio.h>
#include <stdlib.h>

#define MAX 20
#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))

struct point {
    int x;
    int y;
};

struct rect {
    struct point one;
    struct point two;
};


struct point makepoint ( int x, int y );
struct point addpoint ( struct point , struct point );
struct rect canonrect ( struct rect r );
int getline_my ( char * line );
int ptinrect ( struct point p, struct rect r );
 
int main () {

    int a = 5;    
    int b = 7;    
//    int rez = 0;
//    char line [ MAX ];
    struct point ret = makepoint ( a, b );

    printf ( "\nwith passed to functions arguments a = %d, and b = %d;\n", a, b );
    printf ( "getted structure members ret.x = %d, ret.y = %d;\n\n", ret.x, ret.y );

    struct rect screen;
    struct point middle;

    screen.one = makepoint ( 0, 0 );
    screen.two = makepoint ( 20, 30 );
    middle = makepoint ( ( screen.one.x + screen.two.x ) / 2, ( screen.one.y + screen.two.y ) / 2 );

    printf ( "screen.one = %d, %d;\n", screen.one.x, screen.one.y );
    printf ( "screen.two = %d, %d;\n", screen.two.x, screen.two.y );
    printf ( "getted point middle: x = %d; y = %d;\n", middle.x, middle.y );

    struct point sum = addpoint ( ret, middle );
    printf ( "\nafter addpoint sum = ( ret + middle ): sum.x = %d; sum.y = %d;\n", sum.x, sum.y );


    struct point * p_one;
    p_one = & ret;
    printf ( "* p_one -> x = %d;\n", p_one -> x );    

    struct {
        int len;
        char * str;
    } * p;
    
    p.len = 5;
    printf ( "++ p -> len = %d;\n", ++ p -> len );    


    return 0;        
    
}


struct rect canonrect ( struct rect r ) {

    struct rect temp;

    temp.one.x = min ( r.one.x, r.two.x );
    temp.one.y = min ( r.one.y, r.two.y );
    temp.two.x = max ( r.one.x, r.two.x );
    temp.two.y = max ( r.one.y, r.two.y );
    
    return temp;

}


int ptinrect ( struct point p, struct rect r ) {

    return ( p.x > r.one.x && p.x < r.two.x && p.y > r.one.y && p.y < r.two.y  );

}


struct point addpoint ( struct point p1 , struct point p2 ) {

    p1.x += p2.x; 
    p1.y += p2.y;
    
    return p1;

}



struct point makepoint ( int x, int y ) {

    struct point temp;

    temp.x = x;
    temp.y = y;

    return temp;
    
}

int getline_my ( char * line ) {

    char c = 0;
    int step = 0;

    while ( ( c = getchar () ) != EOF && c != '\n' ) {
        * ( line + step ) = c;
        step ++;
    }

    * ( line + step ) = '\0';

    return step;

}





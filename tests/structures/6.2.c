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
    int rez = 0;
    char line [ MAX ];
    struct point ret = makepoint ( a, b );

    printf ( "\nwith passed to functions arguments a = %d, and b = %d;\n", a, b );
    printf ( "getted structure members ret.x = %d, ret.y = %d;\n\n", ret.x, ret.y );

    struct rect screen;
    struct point middle;

    screen.one = makepoint ( 0, 0 );
    screen.two = makepoint ( 20, 30 );
    middle = makepoint ( ( screen.one.x + screen.two.x ) / 2, ( screen.one.y + screen.two.y ) / 2 );

    printf ( "getted point middle: x = %d; y = %d;\n", middle.x, middle.y );

    struct point sum = addpoint ( ret, middle );
    printf ( "\nafter addpoint sum = ( ret + middle ): sum.x = %d; sum.y = %d;\n", sum.x, sum.y );

    struct point testpoint;
    printf ( "\nNow we can test point coordinates whether they are inside rectangle.\n" );
    printf ( "Enter please coordinate x of testing point: " );
    rez = getline_my ( line ); 
    testpoint.x = atoi ( line );
    printf ( "And now please enter coordinate y of testint point: " );
    rez = getline_my ( line );
    testpoint.y = atoi ( line );
    printf ( "getted coordinates of testing point: x = %d, y = %d;\n", testpoint.x, testpoint.y );
    rez = ptinrect ( testpoint, screen );
    if ( rez == 1 ) {
        printf ( "our point is inside rectangle!\n" );    
    }
    else {
        printf ( "point is outside rectangle(\n" );
    }

    struct rect t2;    
    printf ( "\nHere we will test function canonrec, which assumes that rectangle is presented in a standart form.\n" );

    printf ( "Enter coordinates of first point:\n" );
    printf ( "x: " );
    rez = getline_my ( line );
    t2.one.x = atoi ( line );
    printf ( "\ny:" );
    rez = getline_my ( line );
    t2.one.y = atoi ( line );

    printf ( "Enter coordinates of second point:\n" );
    printf ( "x: " );
    rez = getline_my ( line );
    t2.two.x = atoi ( line );
    printf ( "\ny: " );
    rez = getline_my ( line );
    t2.two.y = atoi ( line );

    printf ( "\ngetted values: point one ( %d, %d ), point two ( %d, %d );\n", t2.one.x, t2.one.y, t2.two.x, t2.two.y );
    t2 = canonrect ( t2 );
    printf ( "\nafter canonrect values: point one ( %d, %d ), point two ( %d, %d );\n", t2.one.x, t2.one.y, t2.two.x, t2.two.y );
    struct point * pp;
    pp = & testpoint;
    printf ( "( * pp ).x  = %d; ( * pp ).y = %d;\n", ( * pp ).x , ( * pp ).y );
    printf ( "pp -> x = %d; pp -> y = %d;\n", pp -> x, pp -> y );

    struct rect * rp = & t2;
    printf ( "\nfour expressions below are equivalent;\n" );
    printf ( "t2.one.x = %d;\n", t2.one.x );
    printf ( "rp -> one.x = %d;\n", rp -> one.x );
    printf ( "( t2.one ).x = %d;\n", ( t2.one ).x );
    printf ( "( rp -> one ).x = %d;\n", ( rp -> one ).x );

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





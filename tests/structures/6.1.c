#include <stdio.h>

void getline_my ( char * line );

int main () {

//    typedef struct point point_my;

    struct point {
        int x;
        int y;
    };

    struct point a = { 5, 7 };
//    point_my b = { .y = 9, .x = 11 };    
    struct point b = { .y = 9, .x = 11 };    

    printf ( "structure point has element a = %d, %d;\n", a.x, a.y );
    printf ( "structure point has element b = %d, %d;\n", b.x, b.y );


    struct username {
        char fname [ 10 ];
        char lname [ 10 ];
    };

    struct username firstuser;

    printf ( "\nHello! Can you tell me about yourself? What is your first name? Tell me please: " );
    getline_my ( firstuser.fname );
    
    printf ( "\nGlad to see you, %s!\n", firstuser.fname );   

    printf ( "\nMay be you will tell me your last name? You may enter it here: " ); 
    getline_my ( firstuser.lname );
    
    printf ( "\nNice to meet you, mister %s %s!\n\n", firstuser.fname, firstuser.lname );    

    return 0;

}

void getline_my ( char * line ) {

    char c = 0;
    int step = 0;

    while ( ( c = getchar () ) != EOF && c != '\n' ) {
        * ( line + step ) = c;
//        printf ( "getted c = %c;\n", * ( line + step ) );        
        step ++;
    }
    
    step ++;

    * ( line + step ) = '\0';

}



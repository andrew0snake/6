#include <stdio.h>
#include <ctype.h>
#include <string.h>

struct key {
    char * word;
    int count;
} keytab [] = {
    "#",0,
    "#define",0,
    "//",0,
    "auto",0,
    "break",0,
    "case",0,
    "char",0,
    "const",0,
    "continue",0,
    "default",0,
    "double",0,
    "insigned",0,
    "int",0,
    "float",0,    
    "void",0,
    "volatile",0,
    "whole",0
}; 

#define NKEYS ( sizeof keytab / sizeof ( keytab [ 0 ] ) )
#define MAXWORD 100
#define BUFSIZE 100

static char buf [ BUFSIZE ];
static int bufp = 0;

int getch ();
void ungetch ( int );
int getword ( char *, int );
struct key *  binsearch ( char *, struct key *, int );
int is_need ( char );
void clear_string ( char * );
int find_define ( char * );    

int main () {

    char word [ MAXWORD ];
    struct key * p;
    
    while ( getword ( word, MAXWORD ) != EOF ) {
        if ( isalpha ( word [ 0 ] ) || is_need ( word [ 0 ] ) ) {
            if ( ( p = binsearch ( word, keytab, NKEYS ) ) != NULL ) {
                p->count ++;
            }
        }
    }

    printf ( "\n============\n" );

    for ( p = keytab; p < keytab + NKEYS; p ++ ) {
        if ( p -> count > 0 ) {
            printf ( "%4d of %s\n", p -> count, p -> word );
        }
    }
    printf ( "============\n" );

    return 0;

}


struct key * binsearch ( char * word, struct key tab [], int n ) {

    int cond = 0;
    int rez = 0;
    struct key * low = & tab [ 0 ];
    struct key * high = & tab [ n ];
    struct key * mid;
    
    if ( is_need ( word [ 0 ] ) ) {
        printf ( "word [ 0 ] = %c;is_need;\n", word [ 0 ] );
        switch ( word [ 0 ] ) {
        case '/' :
            if ( word [ 1 ] == '/' ) {
                clear_string ( word );
                strcpy ( word, "//");        
            }
            else {
                if ( word [ 0 ] == '*' ) {
                    clear_string ( word );
                    strcpy ( word, "/*" );
                }
            }
            break;
        case '#' :
            rez = find_define ( word );
            if ( rez == 1 ) {
                strcpy ( word, "#define" );
            }
            else {
                strcpy ( word, "#" );
            }
            break;
        default :
            ;
        }
        printf ( "word = %s;\n", word );
    }

    while ( low < high ) {
        mid = low + ( high - low ) / 2;
        if ( ( cond = strcmp ( word, mid -> word ) ) < 0 ) {
            high = mid;
        }
        else {
            if ( cond > 0 ) {
                low = mid + 1;
            }
            else {
                return mid;
            }
        }    
    }

    return NULL;

}


int getch  ( void ) {
    
    return ( ( bufp > 0 ) ? ( buf [ --bufp ] ) : getchar () );

}


void ungetch ( int c ) {

    if ( bufp >= BUFSIZE )
        printf ( "ungetch: too much symbols.\n" );
    else 
        buf [ bufp++ ] = c;

}

int getword ( char * word, int lim ) {

    int c = 0;
    char * w = word;

    while ( isspace ( c = getch () ) )
        ;

    if ( c != EOF ) {
        * w ++ = c;
    }

    if ( ! isalpha ( c ) && ! is_need ( c ) ) {
        * w = '\0';
        return c;
    }

    for ( ; -- lim > 0; w ++ ) {
        if ( ! isalnum ( * w = getch () ) && ! is_need ( * w ) ) {
            ungetch ( * w );
            break;
        }
    }
    * w = '\0';

    return word [ 0 ];

}

int is_need ( char c ) {

    if ( c == '/' || c == '#' || c == '_' ) {
        return 1;
    }
    else {
        return 0;
    }

}


int find_define ( char * word ) {

    short int i = 0;
    short int j = 0;
    short int ws = 0;
    char etalon [] = "#define";
    short int check = 1;
    short int error = 1;
    
    while ( check && error && ( * ( etalon + j ) != '\0' ) ) {
        if ( * ( word + i ) == ' ' && ws == 0 ) {
            i ++;
        }
        else {
            if ( * ( word + i ) == ' ' && ws == 1 ) {
                error = 0;
            }
            else {
                if ( * ( word + i ) == * ( etalon + j ) ) {
                    printf ( "* ( word + %d ) = %c;  * ( etalon + %d ) = %c;\n", i, * ( word + i ), j, * ( etalon + j ) );
                    if ( * ( word + i ) == 'd' ) {
                        ws = 1;
                    }
                    i ++;
                    j ++;
                }
                else {
                    check = 0;
                }
            }    
        }    

    }

    printf ( "int rez check = %d; error = %d; word = %s;\n", check, error, word );

    if ( error == 0 ) {
        return -1;
    }

    if ( check == 0 ) {
        return 0;
    }

    return 1;

}


void clear_string ( char * string ) {

    int i = 0;

    for ( i = 0; i < MAXWORD; i ++ ) {
        * ( string + i ) = '\0';
    }

}

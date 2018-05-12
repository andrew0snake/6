#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

struct tnode {
    char * word;
    int count;
    struct tnode * left;
    struct tnode * right;    
};

#define MAXWORD 100
#define BUFSIZE 100

static char buf [ BUFSIZE ];
static int bufp = 0;

int getch ();
void ungetch ( int );
int getword ( char *, int );
struct tnode * addtree ( struct tnode *, char * );
void treeprint ( struct tnode * );
int is_need ( char );
void clear_string ( char * );
struct tnode * talloc ( void );
char * strdup_my ( char * );    

int main () {

    char word [ MAXWORD ];
    struct tnode  * root;

    root = NULL;    
    while ( getword ( word, MAXWORD ) != EOF ) {
        if ( isalpha ( word [ 0 ] ) || is_need ( word [ 0 ] ) ) {
            root = addtree ( root, word );
        }
    }

    printf ( "\n============\n" );
    treeprint ( root );
    printf ( "==============\n" );

    return 0;

}


struct tnode * addtree ( struct tnode * p, char * w ) {

    int cond = 0;

    if ( p == NULL ) {
        p = talloc ();
        p->word = strdup_my ( w );
        p->count = 1;
        p->left = p->right = NULL;
    }
    else {
        if ( ( cond = strcmp ( w, p->word ) ) == 0 ) {
            p->count ++;
        }
        else {
            if ( cond < 0 ) {
                p->left = addtree ( p->left, w );
            }
            else {
                p->right = addtree ( p->right, w );
            }
        }
    }

    return p;

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



void clear_string ( char * string ) {

    int i = 0;

    for ( i = 0; i < MAXWORD; i ++ ) {
        * ( string + i ) = '\0';
    }

}


void treeprint ( struct tnode * p ) {

    if ( p != NULL ) {
        treeprint ( p->left);
        printf ( "%4d  %s;\n", p->count, p->word );
        treeprint ( p->right );
    }
}


struct tnode * talloc ( void ) {

    return ( struct tnode * ) malloc ( sizeof ( struct tnode ) );

}

 
char * strdup_my ( char * s ) {

    char * p;

    p = ( char * ) malloc ( strlen ( s ) + 1 );
    if ( p != NULL ) {
        strcpy ( p, s );
    }

    return p;

}





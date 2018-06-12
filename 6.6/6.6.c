#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXWORD 10000
#define BUFSIZE 10000
#define MAX 2000
#define HASHSIZE 101

char * strdup_my ( char * s );
int getch  ( void );
void ungetch ( int c );
int strcmp_my ( char *, char *, int );
void clear_string (char *string);
unsigned int hash (char *);
struct nlist * lookup (char *);
static char buf [ BUFSIZE ];
static int bufp = 0;
void getline_my (char *s);
struct nlist * install (char *name, char *defn);
char parse_string ( char * source, char * first_word, char * second_word);
void undef (char *defn);

struct nlist {
    struct nlist * next;
    char * name;
    char * defn; 
};

static struct nlist * hashtab [HASHSIZE];

int main ( int argc, char * argv [] ) {

//    char *s;   
    int i = 0;
    char s [MAX], name [MAX], defn [MAX]; 
    char exit = 1;    
    char rez = 0;
    struct nlist * tmp;

    while (exit) {
      printf ("\n----------------------\n");
      printf ("Enter string:\n");
      clear_string (s);
      getline_my (s);
      if (strlen (s) == 0) {
        exit = 0;       
        printf ("Length of entered string is 0, quit.\n");
      }
      else {  
        printf ("Getted string: '%s';\n", s);
        rez = parse_string (s, name, defn);
        if (rez == -1) {
          printf ("--===Wrong input, try again.===--\n");
        }
        else {
          if (rez == 1) {
            undef (name);
          }
          else {
            install (name, defn);
          }    
        }
        
      }  
    }

    for ( i = 0; i < HASHSIZE; i ++) {
      if (hashtab [i] != NULL) {
        tmp = hashtab [i];
        printf ("hashtab [%d]; tmp->name = %s; tmp->defn = %s;\n", i, tmp->name, tmp->defn );
      }
    }

    return 0;    

}
 
char * strdup_my ( char * s ) {

    char * p;
    
    p = ( char * ) malloc ( strlen ( s ) + 1 );
    if ( p != NULL ) {
        strcpy ( p, s );
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
 

int strcmp_my ( char * first, char * sec, int num ) {

    int i = 0;
    char check = 0;
    short int len = 0;

    if ( ( len = strlen ( first ) ) < num ) {
        num = len;
    }

    if ( ( len = strlen ( sec ) ) < num ) {
        num = len;
    }

    for ( i = 0; i < num && check == 0; i ++ ) {
        if ( * ( first + i ) != * ( sec + i ) ) {
            if ( * ( first + i ) > * ( sec + i ) ) {
                check = 1;
                return check;
            }
            else {
                check = -1; 
                return check;
            }                
        }        
    }

    return 0;

}


void clear_string (char *string) {

    int step = 0;
    
    while (step < MAX) {
      *(string + step) = '\0';  
      step++;  
    }

}

unsigned int hash (char *s) {

    unsigned int hashval;

    for (hashval = 0; *s != '\0'; s ++) {
      hashval = *s + 31 * hashval;  
    }

    return hashval % HASHSIZE;

}

struct nlist * lookup (char *s) {

    struct nlist * np;

    for (np = hashtab[hash (s)]; np != NULL; np = np->next) {
      if (strcmp (s, np->name) == 0) {
        return np;
      }
    }
    return NULL;
}


struct nlist * install (char *name, char *defn) {

    struct nlist *np;
    unsigned hashval;
    
    if ((np = lookup (name)) == NULL) {
      np = (struct nlist *) malloc (sizeof (*np));
      if (np == NULL || (np->name = strdup_my (name)) == NULL) {
        return NULL;
      }
      hashval = hash (name);
      np->next = hashtab [hashval];  
      hashtab [hashval] = np;    
    }
    else {
      free ((void *) np->defn);
    }
    if ((np->defn = strdup_my (defn)) == NULL) {
      return NULL;
    }
    return np;

}    


void getline_my (char *s) {

    int i = 0;
    char c = 0;

    while ((c = getch ()) != EOF && c != '\n') {
      *(s + i) = c;
      i ++;
    }

    *(s + i) = '\0';

}


char parse_string ( char * source, char * f_word, char * s_word) {

    int i = 0;
    int j = 0;
    char tmp_word [7];
    char undef = 0;

    clear_string (f_word);
    clear_string (s_word);
    for (i = 0; i < 7; i ++) {
      tmp_word [i] = 0;
    }
    i = 0;
    while ( * (source + i) == ' ') {        
      i ++;
    }    

    if (*(source + i) != '#') {
      return -1;
    }
    else {
      i ++;
    }

    while (*(source + i) == ' ') {        
      i ++;
    }    
//--find first word after #, must be define or undef
    while (*(source + i) != ' ' && *(source + i) != '\n' && *(source + i) != EOF && j < 7) {    
      *(tmp_word + j) = *(source + i);
      i ++;
      j ++;  
    }

    if (*(source + i) == '\n' || *(source + i) == EOF) {
      printf ("String is shorter than expected. Quit.\n");
      return -1;
    }
//--compire first word after # with "define" and "undef"
    if (j == 7 || (strcmp (tmp_word, "define") != 0)) {
      if (strcmp (tmp_word, "undef") == 0) {
        undef = 1;
      }
      else {
        printf ( "tmp_word != define = '%s';\n", tmp_word );
        return -1;
      }
    }

    while (*(source + i) == ' ') {        
      i ++;
    }    
//--get first define or undef word    
    j = 0;
    while (*(source + i) != ' ' && *(source + i) != '\n' && *(source + i) != EOF) {
      *(f_word + j) = *(source + i);
      i ++;
      j ++;  
    }
    if (strlen (f_word) == 0) {
      printf ("Length of first word is too short.\n");
      return -1;
    }
    else {
      if (undef) {
        return 1;
      }
    }

    while (*(source + i) == ' ') {        
      i ++;
    }    
//--get second word for define
    if (!undef) {
      j = 0;
      while (*(source + i) != ' ' && *(source + i) != '\n' && *(source + i) != EOF) {
        if (*(source + i) == '\n' || *(source + i) == EOF) {
          printf ("String is shorter than expected. Quit.\n");
          return -1;
        }
        *(s_word + j) = *(source + i);
        i ++;
        j ++;  
      }
      if (strlen (s_word) == 0) {
        printf ("Length of second word is too short.\n");
        return -1;
      }
    }

    return 0;

}

void undef (char *defn) {

    struct nlist * np;

    np = lookup (defn);
    
    if (np != NULL ) {
      printf ("string '%s' ", defn);
      printf ("found at address %p. ", np);
      printf ("undefined expression '%s'.\n", np->name);
//      free (hashtab [hash (defn)]);
      hashtab [hash (defn)] = NULL;
      np->next = NULL;  
      np->defn = "";
      np->name = "";

    }    

}




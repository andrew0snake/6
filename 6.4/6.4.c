#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXWORD 10000
#define BUFSIZE 10000
#define MAX 2000

struct tnode * talloc ( void ); 
char * strdup_my ( char * s );
int getch  ( void );
void ungetch ( int c );
int getword ( char *, int );
int is_need ( char );
void print_tree ( struct tnode * );
struct tnode * addtree ( struct tnode *, char * );
int strcmp_my ( char *, char *, int );
void clear_string (char *string);
char is_noise (char *word);
void fill_word (char *);
void sort_list (void);
void print_sorted_list (void);

static char buf [ BUFSIZE ];
static int bufp = 0;
short int compare_num = 0;
int string_num = 0;

struct tnode {
    char * arr [ MAX ];
    short int count;
    struct tnode * left;
    struct tnode * right;
    int strings [ MAX ];
};

struct sorted_list {
    char * arr [MAX];
    int count [MAX];
    int counter;
};

struct sorted_list d_list;
//struct sorted_list * sl = malloc ( sizeof ( struct sorted_list ) );
//d_list.counter = 0;

int main ( int argc, char * argv [] ) {

    int rez = 0;
    char word [ MAX ];
    struct tnode * p;
    p = NULL;    
    d_list.counter = 0;
    
    if ( argc == 2 ) {
        compare_num = atoi ( argv [ 1 ] );
    }
    else {
        compare_num = 6;
    }
    
    clear_string (word);
    while ((rez = getword (word, MAX)) != EOF ) {
        if ( isalnum ( word [ 0 ] ) ) {
          if (is_noise (word) == 0) {
            p = addtree ( p, word );
            fill_word (word);
          }  
        }
        clear_string (word); 
        if (rez == 10) {
            string_num ++;
        }
    }
    
    print_tree ( p );

    sort_list ();
    print_sorted_list ();
    return 0;    

}


struct tnode * addtree ( struct tnode * p, char * w ) {

    int cond = 0;

    if ( p == NULL ) {
        p = talloc ();
        p->arr [ p->count ] = strdup_my ( w );
        p->strings[p->count] = string_num;
        p->count ++;        
        p->left = p->right = NULL;
    }
    else {
        if ( ( cond = strcmp_my ( w, p->arr [ p->count - 1 ], compare_num ) ) == 0 ) {
            p->arr [ p->count ] = strdup_my ( w );
            p->strings[p->count] = string_num;
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


void print_tree ( struct tnode * tree ) {

    short int i = 0;

    if ( tree != NULL ) {
        print_tree ( tree->left );
        printf ( "------------------------------\n" );
        printf ( "printing tree:\n" );
        while ( i < tree->count ) {
            printf ( "tree->word [ %d ] = %s; \n", i, tree->arr [ i ] );
            i ++;
        }
        i = 0;
        printf ("this word occurs in this line numbers:");
        while (i<tree->count) {
          printf ("%d, ", tree->strings[i]);
          i ++;
        }
        printf ("\n");
        print_tree ( tree->right );
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

int getch  ( void ) {
    
    return ( ( bufp > 0 ) ? ( buf [ --bufp ] ) : getchar () );

}


void ungetch ( int c ) {

    if ( bufp >= BUFSIZE )
        printf ( "ungetch: too much symbols.\n" );
    else 
        buf [ bufp++ ] = c;

}
 

int is_need ( char c ) {

    if ( c == '/' || c == '#' || c == '_' || c == '"' ) {
        return 1;
    }
    else {
        return 0;
    }

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


int getword ( char * word, int lim ) {

    int c, d ;
    char * w = word; 
    char quit = 1, end;   
    short int step = 0;

    while (isspace (c = getch ()));
       
    if (c != EOF)
        *w = c;

    if (!isalpha(c) && !is_need (c)) {
        *w = '\0';
        return c;
    }

    for ( ; --lim > 0 && quit; step ++) {
        if (!isalnum (c)) {
            switch (c) {
              case '/':
                switch (d = getch ()) {
                  case '/':
                    printf ( "\n---skipped symbols:---\n" );
                    while ((d = getch ()) != '\n' && d != EOF) {
                        printf ("%c", d);
                    } 
                    printf ("\n--end of skipped symbols;---\n\n");
                    if (d == EOF) {
                      quit = 0;  
                    }
                    if (d == '\n') {
                      return 10;
                    }
                    break;
                  case '*':
                    end = 1;
                    while (end) {
                      d = getch ();
                      if (d == EOF) {
                        quit = 0;
                        end = 1;
                      }  
                      if (d == '*') {
                        if ((c = getch ()) == '/') {
                          end = 0;
                        }
                        else {
                          ungetch (c);
                        }
                      } 
                    }
                    break;
                  default:
                    ungetch (d);
                    break;
                }
                break;              
              case '"':
                printf ("\n---skipped in double quotes sybmols:---\n");
                end = 1;
                while (end) {
                  d = getch ();
                  printf ("%c", d);  
                  if (d == EOF) {
                    quit = 0;
                    end = 1;
                    return EOF;
                  }    
                  if (d == '"') {
                    end = 0;
                  }
                }
                printf ("\n---end of skipped in double quotes sybmols:---\n\n");
                break;  
              case '\n':
                return 10;
                break;
              case ' ':
                return 32;
                break;  
              case EOF:                
                quit = 0;
                printf ( "quit = 0;\n" );
                return EOF;
                break;    
              default:
                break;
            }
        }
        else {
            *(w+step) = c;
        }
        c = getch ();
    }
    step ++;    
    *(w+step) = '\0';
    printf ( "word = \n\n%s;\n", word );
    return word[0];
}

void clear_string (char *string) {

    int step = 0;
    
    while (step < MAX) {
      *(string + step) = '\0';  
      step++;  
    }

}

char is_noise (char *word) {

    if (strcmp( word, "the") == 0) {
      return 1;
    }

    if (strcmp( word, "and") == 0) {
      return 1;
    }

    if (strcmp( word, "a") == 0) {
      return 1;
    }

    if (strcmp( word, "an") == 0) {
      return 1;
    }

    if (strcmp( word, "this") == 0) {
      return 1;
    }

    if (strcmp( word, "or") == 0) {
      return 1;
    }

    if (strcmp( word, "that") == 0) {
      return 1;
    }

    return 0;

}

void fill_word (char * word) {

    int pos = 0;
    char quit = 1;
    char dup = 0;

    while (pos <= d_list.counter && quit) {
      if (d_list.arr[pos] != NULL) {  
        if (strcmp (word, d_list.arr[pos]) == 0) {
          d_list.count[pos]++;
          dup = 1;
          quit = 0;
        }
        else {
          pos ++;  
        }
      }  
      else {        
        d_list.arr[pos] = strdup (word);
        d_list.count[pos]++;
        quit = 0;
      }
    }
    
    if(quit && pos == d_list.counter) {
      d_list.arr [++pos] = strdup (word);
    }

    if (!dup) {
      d_list.counter ++;
    };

}

void sort_list (void) {

    int pos, i, tmp;    
    char exit = 1;
    char check = 0;
    char * c_tmp;

//  struct sorted_list {
//      char * arr [MAX];
//      int count [MAX];
//      int counter;
//  };
    pos = 0;
    while (exit) {
      for (i = pos; i <= d_list.counter; i ++) {   
        if (d_list.count[i] > d_list.count[pos]) {
          tmp = d_list.count[i];
          d_list.count[i] = d_list.count[pos];
          d_list.count [pos] = tmp;
          c_tmp = d_list.arr [i];
          d_list.arr [i] = d_list.arr [pos];
          d_list.arr [pos] = c_tmp; 
        }          
      }
      if (pos == d_list.counter) {  
        check = 0;
        for (i = 0; i < d_list.counter && check == 0; i ++) {
          if (!(d_list.count [i] >= d_list.count [i+1])) {
            check = 1;
          }
        }
        if (check == 0) {
          exit = 0;
        }
      }
      pos++;
    }


}

void print_sorted_list (void) {

    int i;

    printf ( "\n\nList of decreasing order of words:\n\n" );
    for (i = 0; i < d_list.counter; i ++) {
        printf ( "word '%s' meets %d times;\n", d_list.arr[i], d_list.count[i] );
    }

}

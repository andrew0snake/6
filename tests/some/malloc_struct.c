#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 3
#define LEN 10

int getline_my (char *);

char * arr [MAX];
struct arr {
    char * word [LEN];
};

struct arr arr1;

int main () {

    int i;
    char rez = 1;
//    char string [LEN];

    for (i = 0; i < MAX; i ++) {
//      arr[i] = malloc (sizeof (char) * MAX);
      arr[i] = malloc (sizeof (arr[i]));
      rez = getline_my (arr[i]);
//      rez = getline_my (string);
//      arr [i] = strdup (string);
//      strcpy (arr1.word[i], arr[i]);
      arr1.word[i] = strdup (arr[i]);
      printf ("step %d;\n", i);
    }

    for (i = 0; i < MAX; i ++) {
      printf ( "string %d = '%s', and its pointer = %p;\n", i, arr[i], & arr[i]);
    }

    for (i = 0; i < MAX; i ++) {
      printf ( "string of struct %d = '%s', and its pointer = %p;\n", i, arr1.word[i], & arr1.word[i]);
    }


} 

int getline_my (char *word ) {
    
    int step = 0;
    char c = 0;
    char exit = 1;

    do {
      c = getchar ();
      if (c != '\n' && c != EOF && step < LEN - 1) {
        *(word + step) = c;    
        step++;       
      }
      else {
        exit = 0;
      }
    } while (exit);

    *(word + step) = '\0';

    return step;
}




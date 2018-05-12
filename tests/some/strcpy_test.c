#include <stdio.h>
#include <string.h>


char * arr [10];


int main () {

    char word[10];
    
    strcpy (word, "test");
    printf ("getted word = '%s';\n", word);

    strcpy (&arr[0], word);
    printf ("\ngetted arr[0] = '%s';\n", &arr[0]);

    return 0;
}

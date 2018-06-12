#include <stdio.h>

int main () {

    typedef int one;
    typedef one two;

    two i = 5;
    printf ("i of type two = %d;\n", i);

}

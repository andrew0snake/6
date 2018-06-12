#include <stdio.h>

int main () {

    int i;

    for (i = 0; i < 30; i ++) {
      printf ("i = %d; ~ i = %d;\n", i, ~ i);
    }
    

    return 0;

}

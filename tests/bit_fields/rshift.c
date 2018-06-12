#include <stdio.h>

void showbits (unsigned int x) {

    int i;
    for (i = (sizeof (int) * 8) - 1; i >= 0; i --) {
      (x & (1 << i))?putchar ('1'):putchar ('0');
    }
    printf (" = %d;\n", x);    
}

int main () {

    unsigned int i, j, m, n;

    i = 55253;
    j = 2;

    printf ("\nBefore right shift i = %d; j = %d;\n\n", i, j);
    printf ("after right shift i >> j = %d;\n", i >>j);
    printf ("sizeof (int) = %lu;\n\n", sizeof (int));

    printf ("%d in binary:   \t  ", i);
    showbits (i);
    printf ("\n\n");
    
    for (m = 0;m <= 5; m ++) {
      n = i >> m;
      printf ("%d right shift %d gives:", i, m);
      showbits (n);
    }


    return 0;

}

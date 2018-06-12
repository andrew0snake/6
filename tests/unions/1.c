#include <stdio.h>

int main () {

    union one {
      int d;
      char c;   
    } u_one;  

    u_one.d = 12;
    printf ("u_one.d = %2d = '%p'; size of d = %d;\n", u_one.d, &u_one.d, sizeof (u_one.d));
    printf ("u_one.c = %2d = '%p'; size of c = %d;\n", u_one.c, &u_one.c, sizeof (u_one.c));

    u_one.c = 5;
    printf ("u_one.d = %2d = '%p'; size of d = %d;\n", u_one.d, &u_one.d, sizeof (u_one.d));
    printf ("u_one.c = %2d = '%p'; size of c = %d;\n", u_one.c, &u_one.c, sizeof (u_one.c));

    return 0;

}

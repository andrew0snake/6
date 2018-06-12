#include <stdio.h>

int main () {
    
    int x = 3, y = 1, sum, carry;
    sum = x ^ y;
    carry = x & y;
    printf ("x = %d, y = %d; sum = %d, carry = %d;\n\n", x, y, sum, carry);    

    while (carry != 0) {
        carry = carry << 1;
        printf ("carry << 1 = %d;\n", carry);
        x = sum;
        printf ("x = sum = %d;\n", x);
        y = carry;
        printf ("y = carry = %d;\n", y);
        sum = x ^ y;
        printf ("sum = x ^ y = %d;\n", sum);
        carry = x & y;
        printf ("carry = x & y = %d;\n", carry);
        printf ("---------------\n");
    }

    printf ("%u\n", sum);

    return 0;

}

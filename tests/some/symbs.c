#include <stdio.h>
#include <ctype.h>

int main () {

    char c = '_';
    printf ( "c = %c = %d;\n", c, c );
    if ( isalpha ( c ) ) {
        printf ( "isalpha ( c = %c );\n",c  );
        printf ( "isalpha ( c ) = %d;\n", isalpha ( c ) );
    }
    else {
        printf ( "! isalpha ( c = %c );\n", c );
        printf ( "isalpha ( c ) = %d;\n", isalpha ( c ) );
    }

    printf ( "isalnum ( %c ) = %d;\n", c, isalnum ( c ) );

    return 0;

}

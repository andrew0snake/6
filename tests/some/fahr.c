#include <stdio.h>
#include <stdlib.h>

int getline_my (char *word);

int main () {

    char line [100];
    int len;
    float fahr, cel;    
    
    len = getline_my (line);
    fahr = atoi (line);
    printf ("getted faht = %f;\n", fahr);
    cel = 5.0 / 9.0 * (fahr - 32.0);
    printf ("cel = %f;\n", cel);        

}

int getline_my (char *line) {

    int len;
    char c;
    
    len = 0;
    while ((c = getchar()) != EOF && c != '\n') {
      *(line + len) = c;
      len ++;  
    }
    if(c == '\n') {
      *(line + len) = '\n';  
    }
    len ++;
    *(line + len)= '\0';

    return len;
}



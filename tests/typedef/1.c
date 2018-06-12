#include <stdio.h>
#include <string.h>

typedef int len;

len f1 (char c);

typedef int PFI (char *, char *, int); 
//int strcmp_my (char * first, char * sec, int num); 
PFI strcmp_my;

typedef int * F2 (int *);
F2 f2;

int main (int argc, char * argv []) {

//    typedef int len;

    len i = 0;
    len arr [5] = {3, 7, 11, 13, 17};
    int * p = &arr [2];

    printf ("i = %d;\n\n", i);

    for (i = 0; i < 5; i ++) {
      printf ("arr [%d] = %2d = '%p';\n", i, arr [i], & arr [i]);
    }

    printf ("f2 [p = arr [2] = %d = '%p' ] = %d;\n", arr[2], & arr[2], f2 (arr [2]));

}

int * f2 (int * a) {

    int rez = 0;
    int * p;

    rez = a;
    printf ("    a   = %d = '%p';\n", a, &a);
    printf ("    rez = %d = '%p';\n", rez, & rez);
    p = rez * 2;        

    return p;    

}


int strcmp_my (char * first, char * sec, int num) {

    int i = 0;
    char check = 0;
    short int len = 0;

    if ((len = strlen (first)) < num) {
        num = len;
    }

    if ((len = strlen (sec)) < num) {
        num = len;
    }

    for (i = 0; i < num && check == 0; i ++) {
        if (* (first + i) != * (sec + i)) {
            if (* (first + i) > * (sec + i)) {
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




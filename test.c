#include <stdio.h>
#include "lin-alg.c"


void testPrint();
void testCopy();


int main(){
    printf("Testing...\n");

    testPrint();
    testCopy();

    return 0;
}

void testPrint(){
    matrix* m = newMatrix(2,2);
    printMatrix(m);
    deleteMatrix(m);
}

void testCopy(){
    matrix* m = newMatrix(2,2);
    matrix* x = copyMatrix(m);
    deleteMatrix(x);
    deleteMatrix(m);
}
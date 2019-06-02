#include <stdio.h>
#include "lin-alg.c"


void testCreate();
void testPrint();
void testCopy();
void testElem();


int main(){
    printf("Testing...\n");

    testCreate();
    testPrint();
    testCopy();
    testElem();

    return 0;
}

void testCreate(){
    double data[] = {1.2, 3.4, 5.6, 7.8};
    matrix* m = newMatrix(data, 2, 2);
    printMatrix(m);
    printf("\n");
    deleteMatrix(m);
}

void testPrint(){
    matrix* m = zeroMatrix(2,2);
    printMatrix(m);
    deleteMatrix(m);
}

void testCopy(){
    matrix* m = zeroMatrix(2,2);
    matrix* x = copyMatrix(m);
    deleteMatrix(x);
    deleteMatrix(m);
}

void testElem(){
    matrix* m = zeroMatrix(2,2);
    double x = getElement(m, 0, 0);
    printf("Before: getElement(0,0) = %9.9f\n", x);
    setElement(m, 0, 0, 4.5);
    printf("After:  getElement(0,0) = %9.9f\n", getElement(m, 0, 0));
    deleteMatrix(m);
}
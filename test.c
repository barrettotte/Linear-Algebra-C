#include <stdio.h>
#include "matrix.h"


void testCreate();
void testCopy();
void testElem();
void testRowVector();
void testColVector();


int main(){
    /* Instantiation, accessors/mutators */
    testCreate();
    testCopy();
    testElem();
    testRowVector();
    testColVector();

    return 0;
}

void testCreate(){
    printf("\nTest create matrix from array...\n");
    double data[4] = {1.2, 3.4, 5.6, 7.8};
    matrix* m = newMatrix(data, 2, 2);
    printMatrix(m);
    /* [1.2, 3.4] 
       [5.6, 4.0] */
    deleteMatrix(m);
}

void testCopy(){
    printf("\nTest matrix copying...\n");
    matrix* m = zeroMatrix(2,2);
    matrix* n = copyMatrix(m);
    printf("ORIGINAL:\n");
    printMatrix(m);
    printf("COPIED:\n");
    printMatrix(n);

    deleteMatrix(n);
    deleteMatrix(m);
}

void testElem(){
    printf("\nTest element accessor and mutator...\n");
    matrix* m = zeroMatrix(2,2);
    double x = getElement(m, 0, 0);
    printf("   Before: getElement(0,0) = %9.9f\n", x);
    setElement(m, 0, 0, 4.5);
    printf("   After:  getElement(0,0) = %9.9f\n", getElement(m, 0, 0));
    printf("   Matrix:\n");
    /* [4.5, 0.0] 
       [0.0, 0.0] */
    printMatrix(m);
    deleteMatrix(m);
}

void testRowVector(){
    printf("\nTest accessor/mutator for row vectors...\n");
    matrix* m = zeroMatrix(2, 2);
    matrix* row = getRowVector(m, 1);
    setElement(row, 0, 0, 123);
    printf("Row vector 1:\n");
    printMatrix(row); /* [123.0, 0.0] */

    double data[2] = {1, 4};
    matrix* n = newMatrix(data, 2, 1);
    setRowVector(m, 1, n);
    printf("Mutating row vector 2:\n");
    printMatrix(m); 
    /* [0.0, 0.0]
       [1.0, 4.0] */

    deleteMatrix(n);
    deleteMatrix(row);
    deleteMatrix(m);
}

void testColVector(){
    printf("\nTest accessor/mutator for column vectors...\n");
    matrix* m = zeroMatrix(2, 2);
    matrix* col = getColVector(m, 0);
    setElement(col, 0, 0, 5);
    setElement(col, 1, 0, 10);
    printf("Column vector 0:\n");
    printMatrix(col); /* [5.0, 10.0] */

    double data[2] = {10, 3};
    matrix* n = newMatrix(data, 1, 2);
    setColVector(m, 0, n);
    printf("Mutating column vector 0:\n");
    printMatrix(m);
    /* [10.0, 0.0]
       [3.0, 0.0] */

    deleteMatrix(n);
    deleteMatrix(col);
    deleteMatrix(m);
}


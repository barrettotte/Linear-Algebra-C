#include <stdio.h>
#include "matrix.h"
#include "utils.h"


void testCreate();
void testCopy();
void testElem();
void testRowVector();
void testColVector();
void testDiagonalVector();

void testIsEqual();
void testIsZeroMatrix();
void testIsIdentityMatrix();
void testIsSquareMatrix();


int main(){
    testCreate();
    testCopy();
    testElem();
    testRowVector();
    testColVector();
    testDiagonalVector();

    testIsEqual();
    testIsZeroMatrix();
    testIsIdentityMatrix();
    testIsSquareMatrix();

    return 0;
}

void testCreate(){
    printf("\nTest create matrix from array...\n");
    double data[4] = {1.2, 3.4, 5.6, 7.8};
    matrix* m = newMatrix(data, 2, 2);
    printMatrix(m, false);
    /* [1.2, 3.4] 
       [5.6, 4.0] */
    assert(
      getElement(m,0,0) == 1.2 && 
      getElement(m,1,0) == 3.4 && 
      getElement(m,0,1) == 5.6 && 
      getElement(m,1,1) == 7.8
    );
    deleteMatrix(m);
}

void testCopy(){
    printf("\nTest matrix copying...\n");
    matrix* m = zeroMatrix(2,2);
    matrix* n = copyMatrix(m);
    printf("ORIGINAL:\n");
    printMatrix(m, false);
    printf("COPIED:\n");
    printMatrix(n, false);
    assert(
      getElement(m,0,0) == getElement(n,0,0) && 
      getElement(m,0,1) == getElement(n,0,1) && 
      getElement(m,1,0) == getElement(n,1,0) && 
      getElement(m,1,1) == getElement(n,1,1)
    );

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
    printMatrix(m, false);
    assert(
      getElement(m,0,0) == 4.5 &&
      getElement(m,0,1) == 0.0 &&
      getElement(m,1,0) == 0.0 &&
      getElement(m,1,1) == 0.0
    );
    deleteMatrix(m);
}

void testRowVector(){
    printf("\nTest accessor/mutator for row vectors...\n");
    matrix* m = zeroMatrix(2, 2);
    matrix* row = getRowVector(m, 1);
    setElement(row, 0, 0, 123);
    printf("Row vector 1:\n");
    printMatrix(row, false); /* [123.0, 0.0] */
    assert(getElement(row,0,0) == 123.0 && getElement(row,0,1) == 0.0);

    double data[2] = {1, 4};
    matrix* n = newMatrix(data, 2, 1);
    setRowVector(m, 1, n);
    printf("Mutating row vector 2:\n");
    printMatrix(m, false); 
    /* [0.0, 0.0]
       [1.0, 4.0] */
    assert(
      getElement(m,0,0) == 0.0 &&
      getElement(m,1,0) == 0.0 &&
      getElement(m,0,1) == 1.0 &&
      getElement(m,1,1) == 4.0
    );

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
    printMatrix(col, false); /* [5.0, 10.0] */
    assert(
      getElement(col,0,0) == 5.0 &&
      getElement(col,1,0) == 10.0
    );

    double data[2] = {10, 3};
    matrix* n = newMatrix(data, 1, 2);
    setColVector(m, 0, n);
    printf("Mutating column vector 0:\n");
    printMatrix(m, true);
    /* [10.0, 0.0]
       [3.0, 0.0] */

    deleteMatrix(n);
    deleteMatrix(col);
    deleteMatrix(m);
}

void testDiagonalVector(){
    printf("\nTest accessor/mutator for diagonal vector...\n");
    
    matrix* m = zeroMatrix(2,2);
    setElement(m,0,0,34);
    setElement(m,1,1,56);
    matrix* d = getMainDiagonal(m);
    printMatrix(d, true);
    assert(getElement(d,0,0) == 34 && getElement(d,1,0) == 56);
    deleteMatrix(d);
    deleteMatrix(m);

    matrix* n = zeroMatrix(2,2);
    matrix* e = zeroMatrix(2,1);
    setElement(e,0,0,100);
    setElement(e,0,1,4);
    setMainDiagonal(n,e);
    printMatrix(n, false);
    assert(getElement(n,0,0) == 100 && getElement(n,1,1) == 4);
    deleteMatrix(n);
    deleteMatrix(e);
}

void testIsEqual(){
    printf("\nTest isEqual...\n");
    matrix* m = zeroMatrix(2, 2);
    matrix* n = zeroMatrix(2, 2);
    matrix* o = zeroMatrix(3, 3);
    assert(!isEqual(m,o));
    assert(isEqual(m,n));
    setElement(m, 0, 0, 1);
    assert(!isEqual(m,n));

    deleteMatrix(n);
    deleteMatrix(m);
}

void testIsZeroMatrix(){
    printf("\nTest isZeroMatrix...\n");
    matrix* m = zeroMatrix(1,3);
    matrix* n = zeroMatrix(2,2);
    setElement(n, 0, 0, 1);
    assert(isZeroMatrix(m));
    assert(!isZeroMatrix(n));

    deleteMatrix(n);
    deleteMatrix(m);
}

void testIsIdentityMatrix(){
    printf("\nTest isIdentityMatrix...\n");

    matrix* m = zeroMatrix(2,2);
    setElement(m,0,0,1);
    setElement(m,1,1,1);
    assert(isIdentityMatrix(m));
    deleteMatrix(m);

    matrix* n = zeroMatrix(1,3);
    assert(!isIdentityMatrix(n));
    deleteMatrix(n);

    matrix* o = zeroMatrix(3,3);
    setElement(o,0,0,1);
    setElement(o,1,1,1);
    setElement(o,2,2,1);
    setElement(o,1,2,-4);
    assert(!isIdentityMatrix(o));
    deleteMatrix(o);
    
    matrix* p = zeroMatrix(1,1);
    setElement(p,0,0,1);
    assert(isIdentityMatrix(p));
    deleteMatrix(p);
}

void testIsSquareMatrix(){
    printf("\nTest isSquareMatrix...\n");
    
    matrix* m = zeroMatrix(2, 2);
    assert(isSquareMatrix(m));
    deleteMatrix(m);

    matrix* n = zeroMatrix(1, 3);
    assert(!isSquareMatrix(n));
    deleteMatrix(n);
}
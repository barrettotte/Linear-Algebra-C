#include <stdio.h>
#include "assert-custom.h"
#include "matrix.h"


void testCreate();
void testCopy();
void testElem();
void testRowVector();
void testColVector();
void testMainDiagonal();
void testAntiDiagonal();

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
    testMainDiagonal();
    testAntiDiagonal();

    testIsEqual();
    testIsZeroMatrix();
    testIsIdentityMatrix();
    testIsSquareMatrix();

    return 0;
}

void testCreate(){
    printf("\nTest create matrix from array...\n");
    double data[4] = {1, 2, 3, 4};
    matrix* m = newMatrix(data, 2, 2);
    printMatrix(m, true);
    /* [1, 2] 
       [3, 4] */
    assert(
      getElement(m,0,0) == 1 && 
      getElement(m,0,1) == 2 && 
      getElement(m,1,0) == 3 && 
      getElement(m,1,1) == 4
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
    double x = getElement(m,0,0);
    printf("   Before: getElement(0,0) = %9.9f\n", x);
    setElement(m,0,0,4);
    printf("   After:  getElement(0,0) = %9.9f\n", getElement(m,0,0));
    printf("   Matrix:\n");
    /* [4, 0] 
       [0, 0] */
    printMatrix(m,false);
    assert(
      getElement(m,0,0) == 4 &&
      getElement(m,0,1) == 0 &&
      getElement(m,1,0) == 0 &&
      getElement(m,1,1) == 0
    );
    deleteMatrix(m);
}

void testRowVector(){
    printf("\nTest accessor/mutator for row vectors...\n");
    matrix* m = zeroMatrix(2,2);
    matrix* row = getRowVector(m,1);
    setElement(row, 0, 0, 123);
    printf("Row vector 1:\n");
    printMatrix(row, false); /* [123, 0] */
    assert(getElement(row,0,0) == 123 && getElement(row,0,1) == 0);

    double data[2] = {1, 4};
    matrix* n = newMatrix(data, 1, 2);
    setRowVector(m, 1, n);
    printf("Mutating row vector 2:\n");
    printMatrix(m, false); 
    /* [0, 0]
       [1, 4] */
    assert(
      getElement(m,0,0) == 0 &&
      getElement(m,0,1) == 0 &&
      getElement(m,1,0) == 1 &&
      getElement(m,1,1) == 4
    );

    deleteMatrix(n);
    deleteMatrix(row);
    deleteMatrix(m);
}

void testColVector(){
    printf("\nTest accessor/mutator for column vectors...\n");
    matrix* m = zeroMatrix(2, 2);
    matrix* col = getColVector(m, 0);
    setElement(col,0,0,5);
    setElement(col,0,1,10);
    printf("Column vector 0:\n");
    printMatrix(col, false); /* [5, 10] */
    assert(
      getElement(col,0,0) == 5 &&
      getElement(col,0,1) == 10
    );

    double data[2] = {10, 3};
    matrix* n = newMatrix(data, 1, 2);
    setColVector(m, 0, n);
    printf("Mutating column vector 0:\n");
    printMatrix(m, false);
    /* [10, 0]
       [3, 0] */

    deleteMatrix(n);
    deleteMatrix(col);
    deleteMatrix(m);
}

void testMainDiagonal(){
    printf("\nTest accessor/mutator for main diagonal...\n");
    
    matrix* m = zeroMatrix(2,2);
    setElement(m,0,0,34);
    setElement(m,1,1,56);
    matrix* d = getMainDiagonal(m);
    printf("Main diagonal:\n");
    printMatrix(d, false);
    assert(getElement(d,0,0) == 34 && getElement(d,0,1) == 56);
    deleteMatrix(d);
    deleteMatrix(m);

    printf("\nMutating main diagonal:\n");
    matrix* n = zeroMatrix(2,2);
    matrix* e = zeroMatrix(1,2);
    setElement(e,0,0,100);
    setElement(e,0,1,4);
    setMainDiagonal(n,e);
    printMatrix(n, false);
    assert(getElement(n,0,0) == 100 && getElement(n,1,1) == 4);
    deleteMatrix(n);
    deleteMatrix(e);
}

void testAntiDiagonal(){
    printf("\nTest accessor/mutator for anti diagonal...\n");
    
    matrix* m = zeroMatrix(2,2);
    setElement(m,0,1,100);
    setElement(m,1,0,250);
    matrix* d = getAntiDiagonal(m);
    printf("Anti diagonal:\n");
    printMatrix(d, false);
    assert(getElement(d,0,0) == 250 && getElement(d,0,1) == 100);
    deleteMatrix(d);
    deleteMatrix(m);

    printf("\nMutating anti diagonal:\n");
    matrix* n = zeroMatrix(2,2);
    matrix* e = zeroMatrix(1,2);
    setElement(e,0,0,9);
    setElement(e,0,1,8);
    setAntiDiagonal(n,e);
    printMatrix(n, false);
    assert(getElement(n,1,0) == 9 && getElement(n,0,1) == 8);
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

    deleteMatrix(o);
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
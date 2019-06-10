#include <math.h>
#include <stdio.h>
#include "linear-algebra.h"

void testCreate();
void testCopy();
void testFlatten();
void testElem();
void testRowVector();
void testColVector();
void testMainDiagonal();
void testAntiDiagonal();

void testIsEqual();
void testIsZeroMatrix();
void testIsIdentityMatrix();
void testIsSquareMatrix();
void testIsDiagonal();
void testIsTriangular();
void testIsSymmetric();

void testTranspose();
void testTrace();
void testAddMatrices();
void testMultiplyMatrices();
void testScaleMatrix();
void testSubMatrix();

void testLuDecomposition();
void testDeterminant();

void testVectorOperations();


int main(){
    testCreate();
    testCopy();
    testFlatten();
    testElem();
    testRowVector();
    testColVector();
    testMainDiagonal();
    testAntiDiagonal();

    testIsEqual();
    testIsZeroMatrix();
    testIsIdentityMatrix();
    testIsSquareMatrix();
    testIsDiagonal();
    testIsTriangular();
    testIsSymmetric();

    testTranspose();
    testTrace();
    testAddMatrices();
    testMultiplyMatrices();
    testScaleMatrix();
    testSubMatrix();

    //testLuDecomposition();
    testDeterminant();

    testVectorOperations();

    return 0;
}

void testCreate(){
    printf("\nTest create matrix and vector from array...\n");
    double data[4] = {1, 2, 3, 4};
    matrix* m = newMatrix(data, 2, 2);
    assert(
      getMatrixElement(m,0,0) == 1 && getMatrixElement(m,0,1) == 2 && 
      getMatrixElement(m,1,0) == 3 && getMatrixElement(m,1,1) == 4 &&
      matrixSize(m) == 4 && matrixSizeBytes(m) == 32
    );
    deleteMatrix(m);

    double data2[8] = { 1, 2, 3, 4, 5, 6, 7, 8 };
    vector* v = newVector(data2, 8);
    assert(vectorSizeBytes(v) == 64);
    deleteVector(v);
}

void testCopy(){
    printf("\nTest matrix and vector copying...\n");
    matrix* m = zeroMatrix(2,2);
    setMatrixElement(m,0,1,5);
    matrix* n = copyMatrix(m);
    assert(
      getMatrixElement(m,0,0) == getMatrixElement(n,0,0) && 
      getMatrixElement(m,0,1) == getMatrixElement(n,0,1) &&
      getMatrixElement(m,1,0) == getMatrixElement(n,1,0) && 
      getMatrixElement(m,1,1) == getMatrixElement(n,1,1)
    );
    deleteMatrix(n);
    deleteMatrix(m);

    vector* v = zeroVector(4);
    setVectorElement(v, 2, 2);
    vector* v2 = copyVector(v);
    assert(getVectorElement(v2, 2) == 2);
    deleteVector(v2);
    deleteVector(v);
}

void testFlatten(){
    printf("\nTest flatten...\n");
    double data[6] = { 1, 2, 3, 4, 5, 6 };
    matrix* m = newMatrix(data, 2, 3);
    vector* flat = flattenMatrix(m);
    assert(getVectorElement(flat,0) == 1 && getVectorElement(flat,5) == 6);
    deleteVector(flat);
    deleteMatrix(m);
}

void testElem(){
    printf("\nTest element accessor and mutator...\n");
    matrix* m = zeroMatrix(2,2);
    setMatrixElement(m,0,0,4);
    assert(
      getMatrixElement(m,0,0) == 4 && getMatrixElement(m,0,1) == 0 &&
      getMatrixElement(m,1,0) == 0 && getMatrixElement(m,1,1) == 0
    );
    deleteMatrix(m);

    vector* v = zeroVector(2);
    setVectorElement(v,1,10);
    assert(getVectorElement(v,1) == 10);
    deleteVector(v);
}

void testRowVector(){
    printf("\nTest accessor/mutator for row vectors...\n");
    matrix* m = zeroMatrix(3,2);
    vector* row = getRowVector(m,1);
    setVectorElement(row,0,123);
    assert(getVectorElement(row,0) == 123 && getVectorElement(row,1) == 0);
    double data[2] = {1, 4};
    vector* v = newVector(data,2);
    setRowVector(m, 1, v);
    assert(
      getMatrixElement(m,0,0) == 0 &&
      getMatrixElement(m,0,1) == 0 &&
      getMatrixElement(m,1,0) == 1 &&
      getMatrixElement(m,1,1) == 4
    );

    deleteVector(v);
    deleteVector(row);
    deleteMatrix(m);
}

void testColVector(){
    printf("\nTest accessor/mutator for column vectors...\n");
    matrix* m = zeroMatrix(3, 2);
    vector* col = getColVector(m, 0);
    setVectorElement(col,0,5);
    setVectorElement(col,1,10);
    setVectorElement(col,2,15);
    assert(getVectorElement(col,0) == 5 && getVectorElement(col,1) == 10);
    double data[2] = {10, 3};
    vector* v = newVector(data,2);
    setColVector(m, 0, v);

    deleteVector(v);
    deleteVector(col);
    deleteMatrix(m);
}

void testMainDiagonal(){
    printf("\nTest accessor/mutator for main diagonal...\n");
    matrix* m = zeroMatrix(2,2);
    setMatrixElement(m,0,0,34);
    setMatrixElement(m,1,1,56);
    vector* v = getMainDiagonal(m);
    assert(getVectorElement(v,0) == 34 && getVectorElement(v,1) == 56);
    deleteVector(v);
    deleteMatrix(m);

    matrix* n = zeroMatrix(2,2);
    vector* w = zeroVector(2);
    setVectorElement(w,0,100);
    setVectorElement(w,1,4);
    setMainDiagonal(n,w);
    assert(getMatrixElement(n,0,0) == 100 && getMatrixElement(n,1,1) == 4);
    deleteMatrix(n);
    deleteVector(w);
}

void testAntiDiagonal(){
    printf("\nTest accessor/mutator for anti diagonal...\n");
    matrix* m = zeroMatrix(2,2);
    setMatrixElement(m,0,1,100);
    setMatrixElement(m,1,0,250);
    vector* d = getAntiDiagonal(m);
    assert(getVectorElement(d,0) == 250 && getVectorElement(d,1) == 100);
    deleteVector(d);
    deleteMatrix(m);

    matrix* n = zeroMatrix(2,2);
    vector* e = zeroVector(2);
    setVectorElement(e,0,9);
    setVectorElement(e,1,8);
    setAntiDiagonal(n,e);
    assert(getMatrixElement(n,1,0) == 9 && getMatrixElement(n,0,1) == 8);
    deleteMatrix(n);
    deleteVector(e);
}

void testIsEqual(){
    printf("\nTest vector and matrix equal...\n");
    matrix* m = zeroMatrix(2, 2);
    matrix* n = zeroMatrix(2, 2);
    matrix* o = zeroMatrix(3, 3);
    assert(!isMatrixEqual(m,o));
    assert(isMatrixEqual(m,n));
    setMatrixElement(m,0,0,1);
    assert(!isMatrixEqual(m,n));
    deleteMatrix(o);
    deleteMatrix(n);
    deleteMatrix(m);

    vector* v = zeroVector(3);
    vector* w = zeroVector(3);
    assert(isVectorEqual(v, w));
    deleteVector(w);
    deleteVector(v);
}

void testIsZeroMatrix(){
    printf("\nTest isZeroMatrix...\n");
    matrix* m = zeroMatrix(1,3);
    matrix* n = zeroMatrix(2,2);
    setMatrixElement(n,0,0,1);
    assert(isZeroMatrix(m));
    assert(!isZeroMatrix(n));
    deleteMatrix(n);
    deleteMatrix(m);
}

void testIsIdentityMatrix(){
    printf("\nTest isIdentityMatrix...\n");

    matrix* m = zeroMatrix(2,2);
    setMatrixElement(m,0,0,1);
    setMatrixElement(m,1,1,1);
    assert(isIdentityMatrix(m));
    deleteMatrix(m);

    matrix* n = zeroMatrix(1,3);
    assert(!isIdentityMatrix(n));
    deleteMatrix(n);

    matrix* o = zeroMatrix(3,3);
    setMatrixElement(o,0,0,1);
    setMatrixElement(o,1,1,1);
    setMatrixElement(o,2,2,1);
    setMatrixElement(o,1,2,-4);
    assert(!isIdentityMatrix(o));
    deleteMatrix(o);
    
    matrix* p = identityMatrix(2);
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

void testIsDiagonal(){
    printf("\nTest isDiagonal...\n");
    double data1[9] = { 1, 2, 3,  0, 5, 6,  0, 0, 9 };
    matrix* m1 = newMatrix(data1, 3, 3);
    assert(!isDiagonalMatrix(m1));
    deleteMatrix(m1);

    double data2[9] = { 1, 0, 0, 0, 2, 0, 0, 0, 3 };
    matrix* m2 = newMatrix(data2, 3, 3);
    assert(isDiagonalMatrix(m2));
    deleteMatrix(m2);
}

void testIsTriangular(){
    printf("\nTest isTriangular, isLoTriMatrix, isUpTriMatrix...\n");
    
    double data1[9] = { 1, 2, 3,  0, 5, 6,  0, 0, 9 };
    matrix* m1 = newMatrix(data1, 3, 3);
    assert(isUpTriMatrix(m1));
    deleteMatrix(m1);

    double data2[9] = { 1, 0, 0,  4, 5, 0,  7, 8, 9 };
    matrix* m2 = newMatrix(data2, 3, 3);
    assert(isLoTriMatrix(m2));
    deleteMatrix(m2);

    double data3[9] = { 1, 0, 0,  4, 5, 0,  7, 8, 9 };
    matrix* m3 = newMatrix(data3, 3, 3);
    assert(isTriangularMatrix(m3));
    deleteMatrix(m3);
}

void testIsSymmetric(){
    printf("\nTest isSymmetric...\n");
    double data[6] = { 1, 2, 3, 4, 5, 6 };
    matrix* m = newMatrix(data, 2, 3);
    assert(!isMatrixSymmetric(m));
    deleteMatrix(m);
    matrix* n = zeroMatrix(2,2);
    assert(isMatrixSymmetric(n));
    deleteMatrix(n);
}

void testTranspose(){
    printf("\nTest transposeMatrix...\n");
    double data[6] = { 1, 2, 3, 4, 5, 6 };
    matrix* m = newMatrix(data, 2, 3);
    matrix* t = transposeMatrix(m);
    assert( 
      getMatrixElement(t,0,0) == 1 && getMatrixElement(t,1,0) == 2 && getMatrixElement(t,2,0) == 3 &&
      getMatrixElement(t,0,1) == 4 && getMatrixElement(t,1,1) == 5 && getMatrixElement(t,2,1) == 6
    );
    deleteMatrix(t);
    deleteMatrix(m);
}

void testTrace(){
    printf("\nTest trace...\n");
    double data[9] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    matrix* m = newMatrix(data, 3, 3);
    assert(traceMatrix(m) == 15);
    deleteMatrix(m);
}

void testAddMatrices(){
    printf("\nTest adding matrices...\n");
    double data1[4] = { 4, 6, 3, 8 };
    double data2[4] = { 6, 4, 7, 2 };
    matrix* m1 = newMatrix(data1, 2, 2);
    matrix* m2 = newMatrix(data2, 2, 2);
    matrix* sum = addMatrices(m1, m2);
    assert(
      getMatrixElement(sum,0,0) == 10 && getMatrixElement(sum,0,1) == 10 &&
      getMatrixElement(sum,1,0) == 10 && getMatrixElement(sum,1,1) == 10
    );
    deleteMatrix(sum);
    deleteMatrix(m2);
    deleteMatrix(m1);
}

void testMultiplyMatrices(){
    printf("\nTest multiplying matrices...\n");
    double data1[4] = { 1, 2, 3, 4 };
    double data2[4] = { 1, 1, 1, 1 };
    matrix* m1 = newMatrix(data1, 2, 2);
    matrix* m2 = newMatrix(data2, 2, 2);
    matrix* prod = multiplyMatrices(m1, m2);
    assert(
      getMatrixElement(prod,0,0) == 3 && getMatrixElement(prod,0,1) == 3 &&
      getMatrixElement(prod,1,0) == 7 && getMatrixElement(prod,1,1) == 7
    );
    deleteMatrix(prod);
    deleteMatrix(m2);
    deleteMatrix(m1);
}

void testScaleMatrix(){
    printf("\nTest scaling matrices...\n");
    double data[6] = { 1, 2, 3, 4, 5, 6 };
    matrix* m = newMatrix(data, 3, 2);
    matrix* scaled = scaleMatrix(m, 10);
    assert(
      getMatrixElement(scaled,0,0) == 10 && getMatrixElement(scaled,0,1) == 20 &&
      getMatrixElement(scaled,1,0) == 30 && getMatrixElement(scaled,1,1) == 40 &&
      getMatrixElement(scaled,2,0) == 50 && getMatrixElement(scaled,2,1) == 60
    );
    deleteMatrix(scaled);
    deleteMatrix(m);
}

void testSubMatrix(){
    printf("\nTest sub matrix...\n");
    double data[9] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    matrix* m = newMatrix(data, 3, 3);
    matrix* sub = subMatrix(m, 2, 2);
    assert(
      getMatrixElement(sub,0,0) == 1 && getMatrixElement(sub,0,1) == 2 &&
      getMatrixElement(sub,1,0) == 4 && getMatrixElement(sub,1,1) == 5
    );
    deleteMatrix(sub);
    deleteMatrix(m);
}

void testLuDecomposition(){
    printf("\nTest lu decomposition...\n");
    double data[16] = { 11, 9, 24, 2, 1, 5, 2, 6, 3, 17, 18, 1, 2, 5, 7, 1 };
    matrix* m = newMatrix(data, 4, 4);
    matrix* l = NULL;
    matrix* u = NULL;
    matrix* p = NULL;
    int sw = 0;
    luDecomposition(m,&l,&u,&p,&sw);
    printMatrix(l, false);
    printf("\n");
    printMatrix(u, false);
    printf("\n");
    printMatrix(p, false);

    deleteMatrix(p);
    deleteMatrix(u);
    deleteMatrix(l);
    deleteMatrix(m);
}

void testDeterminant(){
    printf("\nTest determinant...\n");
    
    double data1[1] = { 10 };
    matrix* m1 = newMatrix(data1, 1, 1);
    assert(determinant(m1) == 10);
    deleteMatrix(m1);

    double data2[4] = { 4, 6, 3, 8 };
    matrix* m2 = newMatrix(data2, 2, 2);
    assert(determinant(m2) == 14);
    deleteMatrix(m2);

    double data3[9] = { 6, 1, 1, 4, -2, 5, 2, 8, 7 };
    matrix* m3 = newMatrix(data3, 3, 3);
    assert(determinant(m3) == -306);
    deleteMatrix(m3);

    
    double data4[16] = { 11, 9, 24, 2, 1, 5, 2, 6, 3, 17, 18, 1, 2, 5, 7, 1 };
    matrix* m4 = newMatrix(data4, 4, 4);
    determinant(m4);

    deleteMatrix(m4);
}

void testVectorOperations(){
    printf("\nTest vector operations...\n");
    double data1[3] = { 2, 4, 3 };
    double data2[3] = { 5, 10, 15};
    double data3[3] = { 1, 0, 0};
    double data4[3] = { 0, 1, 0};
    vector* v  = newVector(data1, 3);
    vector* w  = newVector(data2, 3);
    vector* u1 = newVector(data3, 3);
    vector* u2 = newVector(data4, 3);
    
    assert(roundn(vectorMagnitude(v),3) == 5.385);
    assert(!isUnitVector(v) && isUnitVector(u1));
    assert(dotProduct(v,w) == 95);
    assert(isVectorOrthogonal(u1,u2));
    assert(roundn(vectorDistance(v,w),3) == 13.748);

    vector* cross = crossProduct(v, w);
    assert(
      getVectorElement(cross,0) == 30 && 
      getVectorElement(cross,1) == 15 && 
      getVectorElement(cross,2) == 0
    );
    deleteVector(cross);
    deleteVector(u2);
    deleteVector(u1);
    deleteVector(w);
    deleteVector(v);
}

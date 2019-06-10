#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"


typedef struct{
    int rows; 
    int cols;
    double* data;
} matrix;

typedef struct{
    int cols;
    double* data;
} vector;


// Helper function for asserting matrix and matrix data
bool assertMatrix(matrix* m);


// Helper function for asserting vector and vector data
bool assertVector(vector* v);


// Return new matrix from double array d with size rows x cols
matrix* newMatrix(double* d, int rows, int cols);


// Return new vector from double array d with size cols
vector* newVector(double* d, int cols);


// Return new matrix with null data
matrix* nullMatrix(int rows, int cols);


// Return new vector with null data
vector* nullVector(int cols);


// Return new matrix as a zero matrix of size rows x cols
matrix* zeroMatrix(int rows, int cols);


// Return new vector as a zero vector of size cols
vector* zeroVector(int cols);


// Replace all elements in matrix m with n
void fillMatrix(matrix** m, double n);


// Replace all elements in vector v with n
void fillVector(vector** v, double n);


// Return new matrix as identifiy matrix of size n
matrix* identityMatrix(int n);


// Release matrix m from memory
void deleteMatrix(matrix* m);


// Release vector v from memory
void deleteVector(vector* v);


// Return new matrix as a copy of matrix m
matrix* copyMatrix(matrix* m);


// Return new vector as a copy of vector v
vector* copyVector(vector* v);


// Return matrix m as flattened vector
vector* flattenMatrix(matrix* m);


// Return number of elements of matrix m
int matrixSize(matrix* m);


// Return number of elements of vector v
int vectorSize(vector* v);


// Return size of matrix in bytes
int matrixSizeBytes(matrix* m);


// Return size of vector in bytes
int vectorSizeBytes(vector* v);


// Set element of matrix m[i,j] to scalar s
void setMatrixElement(matrix* m, int i, int j, double s);


// Return scalar as element m[i,j]
double getMatrixElement(matrix* m, int i, int j);


// Set element of vector v[i] to scalar s
void setVectorElement(vector* v, int i, double s);


// Return scalar as element v[i]
double getVectorElement(vector* v, int i);


// Set row vector i of matrix m to vector v
void setRowVector(matrix* m, int i, vector* v);


// Return new matrix as row vector i of vector v
vector* getRowVector(matrix* m, int i);


// Set col vector j of matrix m to vector v
void setColVector(matrix* m, int j, vector* v);


// Return new matrix as col vector j of vector v
vector* getColVector(matrix* m, int j);


// Return new vector as main diagonal of matrix m (square matrices only)
vector* getMainDiagonal(matrix* m);


// Set main diagonal of matrix m to vector v
void setMainDiagonal(matrix* m, vector* v);


// Return new vector as anti diagonal of matrix m (square matrices only)
vector* getAntiDiagonal(matrix* m);


// Set anti diagonal of matrix m to vector v
void setAntiDiagonal(matrix* m, vector* v);


// Return scalar as product of elements of main diagonal of matrix m
double diagonalProduct(matrix* m);


// "Pretty" print matrix m
void printMatrix(matrix* m, bool includeIndices);


// "Pretty" print vector v
void printVector(vector* v, bool includeIndices);


// Matrices m and n are equal if same dimension and identical elements
bool isMatrixEqual(matrix* m, matrix* n);


// Vectors v and w are equal if they contain identical elements
bool isVectorEqual(vector* v, vector* w);


// Matrices m and n have same dimensions if their columns and rows are equal
bool hasSameDimensions(matrix* m, matrix* n);


// Matrix m is a zero matrix if all elements are 0
bool isZeroMatrix(matrix* m);


// Matrix m is an identity matrix if it is a square matrix with only 1's along main diagonal
bool isIdentityMatrix(matrix* m);


// Matrix m is a square matrix if number of cols = number of rows
bool isSquareMatrix(matrix* m);


// Matrix m is invertible if it is a square matrix and det(m) != 0
bool isInvertible(matrix* m);


// Matrix m is a diagonal matrix if m is a square matrix and all elements not along diagonal are zero
bool isDiagonalMatrix(matrix* m);


// Matrix m is a triangular matrix if m is an upper triangular or lower triangular matrix
bool isTriangularMatrix(matrix* m);


// Matrix m is an upper triangular matrix if m is a square matrix and all elements below diagonal are zero
bool isUpTriMatrix(matrix* m);


// Matrix m is a lower triangular matrix if m is a square matrix and all elements above diagonal are zero
bool isLoTriMatrix(matrix* m);


// Matrix m is a symmetric matrix if m = transpose(m)
bool isMatrixSymmetric(matrix* m);


// Matrix m has a zero row if any row is made entirely of zeroes
bool hasZeroRow(matrix *m);


// Matrix m has a zero col if any col is made entirely of zeroes
bool hasZeroCol(matrix *m);


// Return new matrix as transpose of matrix m - flip matrix along diagonal
matrix* transposeMatrix(matrix* m);


// Return scalar as trace of matrix m - sum of all diagonals
double traceMatrix(matrix* m);


// Return new matrix as sum of matrices m1 and m2
matrix* addMatrices(matrix* m1, matrix* m2);


// Return new vector as sum of vectors v1 and v2
vector* addVectors(vector* v1, vector* v2);


// Return new matrix as matrix m ^ k
matrix* powMatrix(matrix* m, double k);


// Return new vector as vector v ^ k
vector* powVector(vector* v, double k);


// Return new matrix as product of matrices m1 and m2
matrix* multiplyMatrices(matrix* m1, matrix* m2);


// Return new matrix as matrix m scaled by scalar s
matrix* scaleMatrix(matrix* m, double s);


// Return scalar as dot product of vectors v1 and v2 (Euclidean inner product)
double dotProduct(vector* v, vector* w);


// Return new vector as cross product of vectors v1 and v2 (3 dimensions)
vector* crossProduct(vector* v, vector* w);


// Return scalar as vector magnitude of vector v (length or magnitude)
double vectorMagnitude(vector* v);


// Return scalar as euclidean distance between vectors v1 and v2
double vectorDistance(vector* v, vector* w);


// Return new vector as vector v scaled by s
vector* scaleVector(vector* v, double s);


// Vector v is a unit vector if the vectorMagnitude(v) = 1
bool isUnitVector(vector* v);


// Vector v1 is orthogonal (perpendicular) to vector v2 if dotProduct(v1, v2) == 0
bool isVectorOrthogonal(vector* v1, vector* v2);


// Matrix m1 is orthogonal to matrix m2 if inv(m) == transpose(m)
bool isMatrixOrthogonal(matrix* m1, matrix* m2);


// Return scalar of scalar triple product of vectors v1, v2, and v3
double scalarTripleProduct(vector* v1, vector* v2, vector* v3);


// Return new 2D matrix as reflection about x or y axis [x:0,y:1]
matrix* reflectAxis2D(matrix* m, int axis);


// Return new 3D matrix as reflection about xy,xz,yz plane [xy:0,xz:1,yz:2]
matrix* reflectAxis3D(matrix* m, int axis);


// Return new 2D matrix as orthogonal projection on x or y axis [x:0,y:1]
matrix* orthProj2D(matrix* m, int axis);


// Return new 3D matrix as orthogonal projection on xy,xz,yz plane [xy:0,xz:1,yz:2]
matrix* orthProj3D(matrix* m, int axis);


// Return new 2D matrix as rotation through angle theta
matrix* rotate2D(matrix *m, double theta);


// Return new nxn matrix as contraction or dilation of factor k on n-space
matrix* scaleNSpace(matrix *m, double k);


// Return new 2D matrix as shear of 2-space in x or y with factor k
matrix* shear2D(matrix *m, double k, int axis);


// Return scalar as determinant of matrix m
double determinant(matrix* m);


// Decompose matrix m into matrices l (lower triangular), u (upper triangular), p (permutation)
void luDecomposition(matrix* m, matrix** l, matrix** u, matrix** p, int* swaps);


// Return new matrix as submatrix of matrix m[0:i,0:j]
matrix* subMatrix(matrix* m, double i, double j);


// Return new matrix as pivot matrix of matrix m
matrix* pivotMatrix(matrix* m, int* swaps);
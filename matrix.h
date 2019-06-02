#ifndef MYBOOL_H
  #define MYBOOL_H
  #define false 0
  #define true 1
  typedef int bool;
#endif

typedef struct{
    int width;
    int height;
    double* data;
} matrix;

// Return new matrix as a zero matrix of size ixj
matrix* newMatrix(const int i, const int j);  


// Release matrix m from memory
void deleteMatrix(matrix* m);


// Return new matrix as a copy of matrix m
matrix* copyMatrix(matrix* m);


// Set element of matrix m[i,j] to scalar s
void setElement(matrix* m, int i, int j, double s);


// Return scalar as element m[i,j]
double* getElement(matrix* m, int i, int j);


// Set row j of matrix m to vector v
void setRow(matrix* m, int j, matrix* v);


// Return new matrix as row j of matrix m as row vector
matrix* getRow(matrix* m, int j);


// Set col i of matrix m to vector v
void setCol(matrix* m, int i, matrix* v);


// Return new matrix as row i of matrix m as column vector
matrix* getCol(matrix* m, int i);


// Get height of matrix m
int rowCount(const matrix* m);


// Get width of matrix m
int colCount(const matrix* m);


// "Pretty" print matrix m
void printMatrix(const matrix* m);


// Matrices m1 and m2 are equal if same dimension and identical elements
bool isEqual(matrix* m1, matrix* m2);


// Matrix m is a zero matrix if all elements are 0
bool isZeroMatrix(matrix* m);


// Matrix m is an identity matrix if it is a square matrix with only 1's along main diagonal
bool isIdentityMatrix(matrix* m);


// Matrix m is a square matrix if number of cols = number of rows
bool isSquareMatrix(matrix* m);


// Matrix m is invertible if it is a square matrix and det(m) != 0
bool isInvertible(matrix* m);


// Matrix m is a diagonal matrix if m is a square matrix and all elements along diagonal are zero
bool isDiagonalMatrix(matrix* m);


// Matrix m is an upper triangular matrix if m is a square matrix and all elements below diagonal are zero
bool isUpTriMatrix(matrix* m);


// Matrix m is a lower triangular matrix if m is a square matrix and all elements above diagonal are zero
bool isLoTriMatrix(matrix* m);


// Matrix m is a symmetric matrix if m = transpose(m)
bool isSymmetric(matrix* m);


// Matrix m has a zero row if any row is made entirely of zeroes
bool hasZeroRow(matrix *m);


// Matrix m has a zero col if any col is made entirely of zeroes
bool hasZeroCol(matrix *m);


// Matrix m is a scalar multiple of matrix m2 if m1 % m2 == 0
bool isScalarMultiple(matrix *m1 , matrix* m2);


// Return scalar as determinant of matrix m
double determinant(matrix* m);


// Return scalar as minor of element m[i,j]
double minor(matrix* m, int i, int j);


// Return scalar as cofactor of element m[i,j]
double cofactor(matrix* m, int i, int j);


// Return new matrix as adjoint of matrix m
matrix* adjointMatrix(matrix* m);


// Return new matrix as identifiy matrix of size n
matrix* identityMatrix(int n);


// Return new matrix as transpose of matrix m - flip matrix along diagonal
matrix* transpose(matrix* m);


// Return new matrix as inverse of matrix m - square matrices only
matrix* inverse(matrix* m);


// Return scalar as trace of matrix m - sum of all diagonals
double traceMatrix(matrix* m);


// Return new matrix as sum of matrices m1 and m2
matrix* sum(matrix* m1, matrix* m2);


// Return new matrix as product of matrices m1 and m2
matrix* product(matrix* m1, matrix* m2);


// Return new matrix as matrix m scaled by scalar value s (scalar product)
matrix* scale(matrix* m, double s);


// Return scalar as dot product of vectors v1 and v2 (Euclidean inner product)
double dotProduct(matrix* v1, matrix* v2);


// Return scalar as the dot product of matrix m's diagonals
double dotDiagonal(matrix* m);


// Return new matrix as cross product of vectors v1 and v2
matrix* crossProduct(matrix* v1, matrix* v2);


// Return scalar as norm of vector v (length or magnitude)
double norm(matrix* v);


// Return scalar as distance between vectors v1 and v2
double distance(matrix* v1, matrix* v2);


// Matrix m is considered a vector if it colCount(m) == 0 or rowCount(m) == 0
bool isVector(matrix* m);


// Vector v is a unit vector if the norm(v) = 1
bool isUnitVector(matrix* v);


// Vector m1 is orthogonal (perpendicular) to vector m2 if dotProduct(v1, v2) == 0
// Matrix m1 is orthogonal to matrix m2 if inv(m) == transpose(m)
bool isOrthogonal(matrix* m1, matrix* m2);


// Return scalar as the area of a parallelogram defined by vectors v1 and v2 [Page 166]
double parallelogramArea(matrix* v1, matrix* v2);


// Return scalar as the volume of a parallelopiped defined by vectors v1, v2, and v3. [Page 166]
double parallelopipedVolume(matrix* v1, matrix* v2, matrix* v3);


// Return scalar of scalar triple product of vectors v1, v2, and v3 -> dotProduct(v1, crossProduct(v2, v3))
double scalarTripleProduct(matrix* v1, matrix* v2, matrix* v3);


// Return new 2D matrix as reflection about y-axis - Page 252 [-1,0],[0,1]
matrix* reflect2Y(matrix* m);


// Return new 2D matrix as reflection about x-axis [1,0],[-1,0]
matrix* reflect2X(matrix* m);


// Return new 3D matrix as reflection about xy plane [1,0,0],[0,1,0],[0,0,-1]
matrix* reflect3XY(matrix* m);


// Return new 3D matrix as reflection about xz plane [1,0,0],[0,-1,0],[0,0,1]
matrix* reflect3XZ(matrix* m);


// Return new 3D matrix as reflection about yz plane [-1,0,0],[0,1,0],[0,0,1]
matrix* reflect3YZ(matrix* m);


// Return new 2D matrix as orthogonal projection on x-axis [1,0],[0,0]
matrix* orthProj2X(matrix* m);


// Return new 2D matrix as orthogonal projection on y-axis [0,0],[0,1]
matrix* orthProj2Y(matrix* m);


// Return new 3D matrix as orthogonal projection on xy plane [1,0,0],[0,1,0],[0,0,0]
matrix* orthProj3XY(matrix* m);


// Return new 3D matrix as orthogonal projection on xz plane [1,0,0],[0,0,0],[0,0,1]
matrix* orthProj3XZ(matrix* m);


// Return new 3D matrix as orthogonal projection on yz plane [0,0,0],[0,1,0],[0,0,1]
matrix* orthProj3YZ(matrix* m);


// Return new 2D matrix as rotation through angle theta [1,0,0],[0,cos(theta),-sin(theta)],[0,sin(theta),cos(theta)]
matrix* rotate2D(matrix *m, double theta);


// Return new 3D matrix as counterclockwise rotation about positive x-axis through angle theta
//   [1,0,0],[0,cos(theta),-sin(theta)],[0,sin(theta),cos(theta)]
matrix* rotate3DX(matrix *m, double theta);


// Return new 3D matrix as counterclockwise rotation about positive y-axis through angle theta
//   [cos(theta),0,sin(theta)],[0,1,0],[-sin(theta),0,cos(theta)]
matrix* rotate3DY(matrix *m, double theta);


// Return new 3D matrix as counterclockwise rotation about positive z-axis through angle theta
//   [cos(theta), -sin(theta), 0],[sin(theta),cos(theta),0],[0,0,1]
matrix* rotate3DZ(matrix *m, double theta);


// Return new 2D matrix as contraction of factor k on 2-space  [k,0],[0,k]
matrix* contract(matrix *m, double k);


// Return new 2D matrix as dilation of factor k on n-space  ex: 2-space [k,0],[0,k]
matrix* dilate(matrix *m, double k, double n);


// Return new 2D matrix as compression of 2-space in x-direction with factor k  [k,0],[0,1]
matrix* compress2X(matrix *m, double k);


// Return new 2D matrix as expansion of 2-space in x-direction with factor k  [k,0],[0,1]
matrix* expand2X(matrix *m, double k);


// Return new 2D matrix as compression of 2-space in y-direction with factor k [1,0],[0,k]
matrix* compress2Y(matrix *m, double k);


// Return new 2D matrix as expansion of 2-space in y-direction with factor k [1,0],[0,k]
matrix* expand2Y(matrix *m, double k);


// Return new 2D matrix as shear of 2-space in x-direction with factor k [1, k], [0, 1]
matrix* shear2X(matrix *m, double k);


// Return new 2D matrix as shear of 2-space in y-direction with factor k [1,0],[k,1]
matrix* shear2Y(matrix *m, double k);


// Return new matrix as eigenvector of matrix m given eigenvalue ev
matrix* eigenvector(matrix* m, double ev); 


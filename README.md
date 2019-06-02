# Linear-Algebra-C

A linear algebra library for performing basic and advanced matrix operations. 
This was made as a refresher for linear algebra.


I did a basic refresher with Elementary Linear Algebra 10th Ed, the book I used in a previous course.


## Note
Every function is based around my struct **matrix** which contains width, height, and data. I did not make 
a separate **vector** struct since a vector is just a one dimensional matrix.

Every element of a matrix is a double, this makes it the most flexible for doing math with.


## Accessors, Mutators, Instantiation
* ```matrix* newMatrix(int i, int j)``` - Instantiate new matrix as zero matrix size ixj
* ```void deleteMatrix(matrix* m)``` - Delete/free memory of matrix m
* ```matrix* copyMatrix(matrix* m)``` - Copy matrix m to a new matrix
* ```void setElement(matrix* m, int i, int j, double s)``` - Set m[i,j] with scalar s
* ```double* getElement(matrix* m, int i, int j)``` - Get scalar element of m[i,j]
* ```void setRow(matrix* m, int j, matrix* v)``` - Set row j of matrix m with vector v
* ```matrix* getRow(matrix* m, int j)``` - Get row vector j of matrix m
* ```void setCol(matrix* m, int i, matrix* v)``` - Set column i of matrix m with vector v
* ```matrix* getCol(matrix* m, int i)``` - Get column vector i of matrix m
* ```int rowCount(matrix* m)``` - Get number of rows for matrix m
* ```int colCount(matrix* m)``` - Get number of columns for matrix m


## Basic Vector/Matrix Operations
* xxx


## Advanced Matrix Operations
* xxx


## Misc Functions
* ```void printMatrix(matrix* m)``` - "Pretty" print matrix m


## Resources
* https://www.amazon.com/Elementary-Linear-Algebra-Howard-Anton/dp/0470458216
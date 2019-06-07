# Linear-Algebra-C

A linear algebra library for performing basic and advanced matrix operations. 
Targeted for **C99**.

This was made as a refresher for linear algebra.


I did a basic refresher with Elementary Linear Algebra 10th Ed, the book I used in a previous course.


## Matrix
To index a matrix, I use row-major indexing with zero indexing
```
[1, 2, 3]     [(0,0) (0,1) (0,2)]
[4, 5, 6] --> [(1,0) (1,1) (1,2)]
[7, 8, 9]     [(2,0) (2,1) (2,2)]
```


## Notes
Every function is based around my struct **matrix** which contains width, height, and data. I did not make 
a separate **vector** struct since a vector is just a one dimensional matrix.

Every element of a matrix is a double, this makes it the most flexible for doing math with.


## Accessors, Mutators, Instantiation
* xxx

## Basic Vector/Matrix Operations
* xxx


## Advanced Matrix Operations
* xxx


## Misc Functions
* ```void printMatrix(matrix* m)``` - "Pretty" print matrix m


## Resources
* https://www.amazon.com/Elementary-Linear-Algebra-Howard-Anton/dp/0470458216
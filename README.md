# Linear-Algebra-C

A linear algebra library for performing basic and advanced matrix/vector operations. 
Targeted for **C99**.

This was made as a refresher for linear algebra and is by no means complete.


I did a basic refresher with Elementary Linear Algebra 10th Ed, the book I used in a previous course.


### Matrix
A struct containing a data field, number of columns, and number of rows.

To index a matrix, I use row-major indexing with zero indexing
```
[1, 2, 3]     [(0,0) (0,1) (0,2)]
[4, 5, 6] --> [(1,0) (1,1) (1,2)]
[7, 8, 9]     [(2,0) (2,1) (2,2)]
```

Matrix data is stored in memory as a one dimensional array. To access the data properly in 
a two dimensional manner, it is sliced on rows and cols like this ```m->data[i * m->cols + j] = 0```


### Vector
A simple struct containing a data field and size field. I started this little library using a 1xn matrix
for a vector representation. But, I found that there were enough vector only functions to make a separate 
distinct type; even though they are practically identical, it adds a bit of readability.


## Functions
* To do


## Debugging
As far as valgrind is concerned, I have taken care of all detected possible memory leaks so far.
```shell
gcc -o dbg_matrix -std=c99 -rdynamic -Wall -g matrix.c test.c utils.c vector.c -lm 
valgrind --leak-check=full \
         --show-leak-kinds=all \
         --track-origins=yes \
         --verbose \
         --log-file=valgrind-out.txt \
         ./dbg_matrix
```

gdb debugging
* compile normally (with -g)
* ```gdb```
* ```file test_matrix```
* ```run```


## Resources
* [Elementary Linear Algebra textbook](https://www.amazon.com/Elementary-Linear-Algebra-Howard-Anton/dp/0470458216)
* Laplace expansion https://en.wikipedia.org/wiki/Laplace_expansion
* Matrix decomposition https://en.wikipedia.org/wiki/Matrix_decomposition
  * Doolittle algorithm https://www.geeksforgeeks.org/doolittle-algorithm-lu-decomposition/
  * LU decomposition 
    * https://en.wikipedia.org/wiki/LU_decomposition
    * https://www.youtube.com/watch?v=yYxwlnilEJs
* Matrix/Vector calculator https://www.symbolab.com/solver/matrix-vector-calculator
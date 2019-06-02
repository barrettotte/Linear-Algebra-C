#include "matrix.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Return new matrix as a zero matrix of size ixj
matrix* newMatrix(const int i, const int j){
    assert(i > 0 && j > 0);
    matrix* m = (matrix *) malloc(sizeof(matrix));
    m->width = i;
    m->height = j;
    m->data = (double *) malloc(i*j*sizeof(double));
    for(int i = 0; i < i*j; i++){
        m->data[i] = 0.0;
    }
    return m;
}

void deleteMatrix(matrix* m){
    assert(m && m->data);
    free(m->data);
    free(m);
}

matrix* copyMatrix(matrix* m){
    assert(m);
    matrix* c = newMatrix(m->width, m->height);
    memcpy(c->data, m-> data, m->width * m->height * sizeof(double));
    return c;
}

int colCount(const matrix* m){
    return m->width;
}

int rowCount(const matrix* m){
    return m->height;
}

void printMatrix(const matrix* m){
    assert(m != NULL);
    double* ptr = m->data;
    for(int i = 0; i <= m->width; i++){
        for(int j = 0; j <= m->height; j++){
            printf("% 9.9f ", *(ptr++));
        }
        printf("\n");
    }
}


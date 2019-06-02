#include "matrix.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


matrix* newMatrix(const double* d, const int i, const int j){
    assert(d && i > 0 & i > 0);
    matrix* m = zeroMatrix(i, j);
    for(int x = 0; x < i * j; x++){
        m->data[x] = d[x];
    }
    return m;
}

matrix* zeroMatrix(const int i, const int j){
    assert(i > 0 && j > 0);
    matrix* m = (matrix *) malloc(sizeof(matrix));
    m->width = i;
    m->height = j;
    m->data = (double *) malloc(i*j*sizeof(double));
    for(int x = 0; x < i*j; x++){
        m->data[x] = 0.0;
    }
    return m;
}

void deleteMatrix(matrix* m){
    assert(m && m->data);
    free(m->data);
    free(m);
}

matrix* copyMatrix(const matrix* m){
    assert(m);
    matrix* c = zeroMatrix(m->width, m->height);
    memcpy(c->data, m-> data, m->width * m->height * sizeof(double));
    return c;
}

void setElement(const matrix* m, const int i, const int j, const double e){
    assert(m && m->data && i >= 0 && j >= 0 && i < m->width && j < m->height);
    m->data[i * m->height + j] = e;
}

double getElement(const matrix* m, const int i, const int j){
    assert(m && m->data && i >= 0 && j >= 0 && i < m->width && j < m->height);
    return m->data[i * m->height + j];
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


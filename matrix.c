#include "matrix.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


matrix* newMatrix(const double* d, const int w, const int h){
    assert(d && w > 0 & w > 0);
    matrix* m = zeroMatrix(w, h);
    for(int x = 0; x < w * h; x++){
        m->data[x] = d[x];
    }
    return m;
}

matrix* zeroMatrix(const int w, const int h){
    assert(w > 0 && h > 0);
    matrix* m = (matrix*) malloc(sizeof(matrix));
    m->width = w;
    m->height = h;
    m->data = (double*) malloc(w * h * sizeof(double));
    for(int x = 0; x < w * h; x++){
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

void setRowVector(const matrix* m, const int j, const matrix* v){
    assert(m && m->data && j >= 0 && j < m->height && v && v->data);
    for(int x = 0; x < v->width; x++){
        m->data[j * m->height + x] = v->data[x];
    }
}

matrix* getRowVector(const matrix* m, const int j){
    assert(m && m->data && j >= 0 && j < m->height);
    double* row = (double*) malloc(sizeof(double) * m->width);
    for(int x = j * m->width; x < (j+1) * m->width; x++){
        row[x] = m->data[x * m->height + j];
    }
    matrix* n = newMatrix(row, 1, m->width);
    free(row);
    return n;
}

void setColVector(const matrix* m, const int i, const matrix* v){
    assert(m && m->data && i >= 0 && i < m->height && v && v->data);
    for(int x = 0; x < v->height; x++){
        m->data[x * m->height + i] = v->data[x];
    }
}

matrix* getColVector(const matrix* m, const int i){
    assert(m && m-> data && i >= 0 && i < m->width);
    double* col = (double*) malloc(sizeof(double) * m->height);
    for(int x = i * m->height; x < (i+1) * m->height; x++){
        col[x] = m->data[i * m->width + x];
    }
    matrix* n = newMatrix(col, m->height, 1);
    free(col);
    return n;
}

void printMatrix(const matrix* m){
    assert(m && m->data);
    for(int i = 0; i < m->width; i++){
        for(int j = 0; j < m->height; j++){
            printf("%16.8f ", m->data[i * m->height + j]);
        }
        if(i < m->width){
            printf("\n");
        }
    }
}


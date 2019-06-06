#include "matrix.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void assertMatrix(const matrix* m){
    assert(m != NULL && m->data != NULL);
}

matrix* newMatrix(const double* d, const int w, const int h){
    assert(d != NULL && w > 0 && h > 0);
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
    assertMatrix(m);
    free(m->data);
    m->data = NULL;
    free(m);
    m = NULL;
}

matrix* copyMatrix(const matrix* m){
    assertMatrix(m);
    matrix* c = zeroMatrix(m->width, m->height);
    memcpy(c->data, m-> data, m->width * m->height * sizeof(double));
    return c;
}

void setElement(const matrix* m, const int i, const int j, const double e){
    assertMatrix(m);
    assert(i >= 0 && j >= 0 && i < m->width && j < m->height);
    m->data[j * m->height + i] = e;
}

double getElement(const matrix* m, const int i, const int j){
    assertMatrix(m);
    assert(i >= 0 && j >= 0 && i < m->width && j < m->height);
    return m->data[j * m->height + i];
}

void setRowVector(const matrix* m, const int j, const matrix* v){
    assertMatrix(m);
    assertMatrix(v);
    assert(j >= 0 && j < m->height);
    for(int x = 0; x < v->width; x++){
        m->data[j * m->height + x] = v->data[x];
    }
}

matrix* getRowVector(const matrix* m, const int j){
    assertMatrix(m);
    assert(j >= 0 && j < m->height);
    double* row = (double*) malloc(sizeof(double) * m->width);
    for(int x = j; x < (j+1); x++){
        row[x] = m->data[x * m->height + j];
    }
    matrix* n = newMatrix(row, 1, m->width);
    free(row);
    return n;
}

void setColVector(const matrix* m, const int i, const matrix* v){
    assertMatrix(m);
    assertMatrix(v);
    assert(i >= 0 && i < m->height);
    for(int x = 0; x < v->height; x++){
        m->data[x * m->height + i] = v->data[x];
    }
}

matrix* getColVector(const matrix* m, const int i){
    assertMatrix(m);
    assert(i >= 0 && i < m->width);
    double* col = (double*) malloc(sizeof(double) * m->height);
    for(int x = i * m->height; x < (i+1) * m->height; x++){
        col[x] = m->data[i * m->width + x];
    }
    matrix* n = newMatrix(col, m->height, 1);
    free(col);
    return n;
}

matrix* getMainDiagonal(const matrix* m){
    assertMatrix(m);
    assert(m->width == m->height);
    double* diag = (double*) malloc(sizeof(double) * m->height);
    for(int i = 0; i < m->width; i++){
        for(int j = 0; j < m->height; j++){
            if(i == j){
                diag[i] = m->data[i * m->width + i];
            }
        }
    }
    matrix* n = newMatrix(diag, 1, m->width);
    free(diag);
    return n;
}

void setMainDiagonal(const matrix* m, const matrix* v){
    assertMatrix(m);
    assertMatrix(v);
    assert(m->width == m->height && m->width == v->width);
    for(int i = 0; i < m->width; i++){
        for(int j = 0; j < m->height; j++){
            if(i == j){
                m->data[i * m->height + i] = v->data[i];
            }
        }
    }
}

bool isEqual(const matrix* m, const matrix* n){
    assertMatrix(m);
    assertMatrix(n);
    if(m->height != n->height || m->width != n->width){
        return false;
    }
    for(int i = 0; i < m->width; i++){
        for(int j = 0; j < m->height; j++){
            if(m->data[i * m->height + j] != n->data[i * n->height + j]){
                return false;
            }
        }
    }
    return true;
}

bool isZeroMatrix(const matrix* m){
    assertMatrix(m);
    for(int i = 0; i < m->width; i++){
        for(int j = 0; j < m->height; j++){
            if(m->data[i * m->height + j] != 0.0){
                return false;
            }
        }
    }
    return true;
}

bool isIdentityMatrix(const matrix* m){
    assertMatrix(m);
    if(m->height != m->width){
        return false;
    }
    for(int i = 0; i < m->width; i++){
        for(int j = 0; j < m->height; j++){
            if(i == j && m->data[i * m->height + j] != 1.0){
                return false;
            } else if(i != j && m->data[i * m-> height + j] != 0.0) {
                return false;
            }
        }
    }
    return true;
}

bool isSquareMatrix(const matrix* m){
    assertMatrix(m);
    return (m->height == m->width);
}

void printMatrix(const matrix* m, const bool includeIndices){
    assertMatrix(m);
    for(int i = 0; i < m->width; i++){
        for(int j = 0; j < m->height; j++){
            if(includeIndices){
                printf("[%d,%d] -> ", i, j);
            }
            printf("%16.8f ", m->data[i * m->height + j]);
        }
        if(i < m->width){
            printf("\n");
        }
    }
}


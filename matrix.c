#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "assert-custom.h"
#include "matrix.h"



void assertMatrix(const matrix* m){
    assert(m != NULL && m->data != NULL);
}

matrix* newMatrix(const double* d, const int rows, const int cols){
    assert(d != NULL && rows > 0 && cols > 0);
    matrix* m = zeroMatrix(rows, cols);
    for(int x = 0; x < rows * cols; x++){
        m->data[x] = d[x];
    }
    return m;
}

matrix* zeroMatrix(const int rows, const int cols){
    assert(rows > 0 && cols > 0);
    matrix* m = (matrix*) malloc(sizeof(matrix));
    m->rows = rows;
    m->cols = cols;
    m->data = (double*) malloc(rows * cols * sizeof(double));
    for(int x = 0; x < rows * cols; x++){
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
    matrix* c = zeroMatrix(m->rows, m->cols);
    memcpy(c->data, m-> data, m->rows * m->cols * sizeof(double));
    return c;
}

void setElement(const matrix* m, const int i, const int j, const double e){
    assertMatrix(m);
    assert(i >= 0 && j >= 0 && i < m->rows && j < m->cols);
    m->data[i * m->rows + j] = e;
}

double getElement(const matrix* m, const int i, const int j){
    assertMatrix(m);
    assert(i >= 0 && j >= 0 && i < m->rows && j < m->cols);
    return m->data[i * m->rows + j];
}

void setRowVector(const matrix* m, const int i, const matrix* v){
    assertMatrix(m);
    assertMatrix(v);
    assert(i >= 0 && i < m->rows);
    for(int j = 0; j < v->cols; j++){
        m->data[i * m->rows + j] = v->data[j];
    }
}

matrix* getRowVector(const matrix* m, const int i){
    assertMatrix(m);
    assert(i >= 0 && i < m->rows);
    double* row = (double*) malloc(sizeof(double) * m->cols);
    for(int j = i; j < (i+1); j++){
        row[j] = m->data[i * m->rows + j];
    }
    matrix* n = newMatrix(row, 1, m->cols);
    free(row);
    return n;
}

void setColVector(const matrix* m, const int j, const matrix* v){
    assertMatrix(m);
    assertMatrix(v);
    assert(j >= 0 && j < m->cols);
    for(int i = 0; i < v->cols; i++){
        m->data[i * m->rows + j] = v->data[i];
    }
}

matrix* getColVector(const matrix* m, const int j){
    assertMatrix(m);
    assert(j >= 0 && j < m->cols);
    double* col = (double*) malloc(sizeof(double) * m->rows);
    for(int i = 0; i < m->rows; i++){
        col[i] = m->data[i * m->rows + j];
    }
    matrix* n = newMatrix(col, 1, m->rows);
    free(col);
    return n;
}

matrix* getMainDiagonal(const matrix* m){
    assertMatrix(m);
    assert(m->rows == m->cols);
    double* diag = (double*) malloc(sizeof(double) * m->rows);
    for(int x = 0; x < m->rows; x++){
        diag[x] = m->data[x * m->rows + x];
    }
    matrix* n = newMatrix(diag, 1, m->rows);
    free(diag);
    return n;
}

void setMainDiagonal(const matrix* m, const matrix* v){
    assertMatrix(m);
    assertMatrix(v);
    assert(m->rows == m->cols && m->cols == v->cols);
    for(int x = 0; x < v->cols; x++){
        m->data[x * m->rows + x] = v->data[x];
    }
}

matrix* getAntiDiagonal(const matrix* m){
    assertMatrix(m);
    assert(m->rows == m->cols);
    int x = 0;
    double* diag = (double*) malloc(sizeof(double) * m->rows);
    for(int i = m->rows-1; i >= 0; i--){
        for(int j = m->cols-1; j >= 0; j--){
            if(i + j == m->rows-1){
                diag[x++] = m->data[i * m->rows + j];
                if(x == m->rows){
                    break;
                }
            }
        }
    }
    matrix* n = newMatrix(diag, 1, m->rows);
    free(diag);
    return n;
}

void setAntiDiagonal(const matrix*m, const matrix* v){
    assertMatrix(m);
    assertMatrix(v);
    assert(m->rows == m->cols && m->cols == v->cols);
    int x =0;
    for(int i = m->rows-1; i >= 0; i--){
        for(int j = m->cols-1; j >= 0; j--){
            if(i + j == m->rows-1){
                m->data[i * m->rows + j] = v->data[x++];
                if(x == m->rows){
                    break;
                }
            }
        }
    }
}

bool isEqual(const matrix* m, const matrix* n){
    assertMatrix(m);
    assertMatrix(n);
    if(m->rows != n->rows || m->cols != n->cols){
        return false;
    }
    for(int i = 0; i < m->rows; i++){
        for(int j = 0; j < m->cols; j++){
            if(m->data[i * m->rows + j] != n->data[i * n->rows + j]){
                return false;
            }
        }
    }
    return true;
}

bool isZeroMatrix(const matrix* m){
    assertMatrix(m);
    for(int i = 0; i < m->rows; i++){
        for(int j = 0; j < m->cols; j++){
            if(m->data[i * m->rows + j] != 0.0){
                return false;
            }
        }
    }
    return true;
}

bool isIdentityMatrix(const matrix* m){
    assertMatrix(m);
    if(m->rows != m->cols){
        return false;
    }
    for(int i = 0; i < m->rows; i++){
        for(int j = 0; j < m->cols; j++){
            if(i == j && m->data[i * m->rows + j] != 1.0){
                return false;
            } else if(i != j && m->data[i * m-> rows + j] != 0.0) {
                return false;
            }
        }
    }
    return true;
}

bool isSquareMatrix(const matrix* m){
    assertMatrix(m);
    return (m->rows == m->cols);
}

void printMatrix(const matrix* m, const bool includeIndices){
    assertMatrix(m);
    for(int i = 0; i < m->rows; i++){
        for(int j = 0; j < m->cols; j++){
            if(includeIndices){
                printf("[%d,%d] -> ", i, j);
            }
            printf("%16.8f ", m->data[i * m->rows + j]);
        }
        if(i < m->rows){
            printf("\n");
        }
    }
}


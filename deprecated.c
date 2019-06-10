#include "linear-algebra.h"


// Failed attempts at various functions
void luDecomposition2(matrix* m, matrix** l, matrix** u){
    assert(isSquareMatrix(m));
    *l = nullMatrix(m->cols, m->cols);
    *u = nullMatrix(m->cols, m->cols);
    for(int i = 0; i < m->cols; i++){
        for(int j = 0; j < m->cols; j++){
            (*u)->data[i * m->cols + j] = m->data[i * m->cols + j];
            for(int k = 0; k < i-1; k++){
                (*u)->data[i * m->cols + j] = (*u)->data[i * m->cols + j] - (*l)->data[k * m->cols + j];
            }
        }
        for(int j = i+1; j < m->cols; j++){
            (*l)->data[j * m->cols + i] = m->data[j * m->cols + i];
            for(int k = 0; k < i-1; k++){
                (*l)->data[j * m->cols + i] = (*l)->data[j * m->cols + i] - (*u)->data[k * m->cols + i];
            }
            (*l)->data[j * m->cols + i] = (*l)->data[j * m->cols + i] / (*u)->data[i * m->cols + i];
        }
    }
}



// Failed attempt
void luDecomposition1(matrix* m, matrix** l, matrix** u){
    assert(isSquareMatrix(m));
    *l = nullMatrix(m->cols, m->cols);
    *u = nullMatrix(m->cols, m->cols);
    for(int i = 0; i < m->cols; i++){
        for(int k = i; k < m->cols; k++){
            double sum = 0;
            for(int j = 0; j < i; j++){
                sum += ((*l)->data[i * m->cols + j]) * ((*u)->data[j * m->cols + k]);
            }
            (*u)->data[i * m->cols + k] = m->data[i * m->cols + k] - sum;
        }
        for(int k = i; k < m->cols; k++){
            if(i == k){
                (*l)->data[i * m->cols + i] = 1;
            } else{
                double sum = 0;
                for(int j = 0; j < i; j++){
                    sum += (((*l)->data[k * m->cols + j]) * ((*u)->data[j * m->cols + i]));
                }
                (*l)->data[k * m->cols + i] = (m->data[k * m->cols + i] - sum) / (*u)->data[i * m->cols + i];
            }
        }
    }
}


void LUP(){
    assert(isSquareMatrix(m) && *l == NULL && *u == NULL && *p == NULL);
    int n = m->cols;
    *l = zeroMatrix(n, n);
    *u = zeroMatrix(n, n);
    *p = pivotMatrix(m);
    matrix* m2 = multiplyMatrices(*p,m);
    for(int j = 0; j < n; j++){
        (*l)->data[j * n + j] = 1;
        for(int i = 0; i < j+1; i++){
            double sumU = 0;
            for(int k = 0; k < i; k++){
                sumU += ((*u)->data[k * n + j] * (*l)->data[i * n + k]);
            }
            (*u)->data[i * n + j] = m2->data[i * n + j] - sumU;
        }
        for(int i = j; i < n; i++){
            double sumL = 0;
            for(int k = 0; k < j; k++){
                sumL += ((*u)->data[k * n + j] * (*l)->data[i * n + k]);
            }
            (*l)->data[i * n + j] = (m2->data[i * n + j] - sumL) / (*u)->data[j * n + j];
        }
    }
    deleteMatrix(m2);
}
#include "linear-algebra.h"


bool assertMatrix(matrix* m){
    assert(m != NULL && m->data != NULL);
    return true;
}

matrix* newMatrix(double* d, int rows, int cols){
    assert(d != NULL && rows > 0 && cols > 0);
    matrix* m = nullMatrix(rows, cols);
    int idx = 0;
    for(int i = 0; i < m->rows; i++){
        for(int j = 0; j < m->cols; j++){
            m->data[i * m->cols + j] = d[idx++];
        }
    }
    return m;
}

matrix* nullMatrix(int rows, int cols){
    assert(rows > 0 && cols > 0);
    matrix* m = (matrix*) malloc(sizeof(matrix));
    m->rows = rows;
    m->cols = cols;
    m->data = (double*) malloc(rows * cols * sizeof(double));
    return m;
}

matrix* zeroMatrix(int rows, int cols){
    matrix* m = nullMatrix(rows, cols);
    fillMatrix(&m, 0);
    return m;
}

void fillMatrix(matrix** m, double n){
    assertMatrix(*m);
    for(int i = 0; i < (*m)->rows; i++){
        for(int j = 0; j < (*m)->cols; j++){
            (*m)->data[i * (*m)->cols + j] = n;
        }
    }
}

matrix* identityMatrix(int n){
    matrix* m = zeroMatrix(n, n);
    for(int i = 0; i < m->rows; i++){
        for(int j = 0; j < m->rows; j++){
            if(i == j){
                m->data[i * m->cols + j] = 1;
            }
        }
    }
    return m;
}

void deleteMatrix(matrix* m){
    free(m->data);
    m->data = NULL;
    free(m);
    m = NULL;
}

matrix* copyMatrix(matrix* m){
    assertMatrix(m);
    matrix* c = zeroMatrix(m->rows, m->cols);
    for(int i = 0; i < m->rows; i++){
        for(int j = 0; j < m->cols; j++){
            c->data[i * m->cols + j] = m->data[i * m->cols + j];
        }
    }
    return c;
}

vector* flattenMatrix(matrix* m){
    assertMatrix(m);
    vector* flat = nullVector(m->rows * m->cols);
    int idx = 0;
    for(int i = 0; i < m->rows; i++){
        for(int j = 0; j < m->cols; j++){
            flat->data[idx++] = m->data[i * m->cols + j];
        }
    }
    return flat;
}

int matrixSize(matrix* m){
    assertMatrix(m);
    return m->rows * m->cols;
}

int matrixSizeBytes(matrix* m){
    return sizeof(double) * matrixSize(m);
}

void setMatrixElement(matrix* m, int i, int j, double s){
    assert(assertMatrix(m) && i >= 0 && j >= 0 && i < m->rows && j < m->cols);
    m->data[i * m->cols + j] = s;
}

double getMatrixElement(matrix* m, int i, int j){
    assert(assertMatrix(m) && i >= 0 && j >= 0 && i < m->rows && j < m->cols);
    return m->data[i * m->cols + j];
}

void setRowVector(matrix* m, int i, vector* v){
    assert(assertMatrix(m) && assertVector(v) && i >= 0 && i < m->rows);
    for(int j = 0; j < v->cols; j++){
        m->data[i * m->cols + j] = v->data[j];
    }
}

vector* getRowVector(matrix* m, int i){
    assert(assertMatrix(m) && i >= 0 && i < m->rows);
    double* row = (double*) malloc(sizeof(double) * m->cols);
    for(int j = 0; j < m->cols; j++){
        row[j] = m->data[i * m->cols + j];
    }
    vector* v = newVector(row, m->cols);
    free(row);
    return v;
}

void setColVector(matrix* m, int j, vector* v){
    assert(assertMatrix(m) && assertVector(v) && j >= 0 && j < m->cols);
    for(int i = 0; i < v->cols; i++){
        m->data[i * m->cols + j] = v->data[i];
    }
}

vector* getColVector(matrix* m, int j){
    assert(assertMatrix(m) && j >= 0 && j < m->cols);
    double* col = (double*) malloc(sizeof(double) * m->rows);
    for(int i = 0; i < m->rows; i++){
        col[i] = m->data[i * m->cols + j];
    }
    vector* v = newVector(col, m->rows);
    free(col);
    return v;
}

vector* getMainDiagonal(matrix* m){
    assert(isSquareMatrix(m));
    double* diag = (double*) malloc(sizeof(double) * m->rows);
    for(int x = 0; x < m->rows; x++){
        diag[x] = m->data[x * m->cols + x];
    }
    vector* v = newVector(diag, m->rows);
    free(diag);
    return v;
}

void setMainDiagonal(matrix* m, vector* v){
    assert(isSquareMatrix(m) && assertVector(v) && m->rows == m->cols && m->cols == v->cols);
    for(int x = 0; x < v->cols; x++){
        m->data[x * m->cols + x] = v->data[x];
    }
}

vector* getAntiDiagonal(matrix* m){
    assert(isSquareMatrix(m));
    int x = 0;
    double* diag = (double*) malloc(sizeof(double) * m->rows);
    for(int i = m->rows-1; i >= 0; i--){
        for(int j = m->cols-1; j >= 0; j--){
            if(i + j == m->rows-1){
                diag[x++] = m->data[i * m->cols + j];
                if(x == m->rows){
                    break;
                }
            }
        }
    }
    vector* v = newVector(diag, m->rows);
    free(diag);
    return v;
}

void setAntiDiagonal(matrix*m, vector* v){
    assert(isSquareMatrix(m) && assertVector(v) && m->rows == m->cols && m->cols == v->cols);
    int idx = 0;
    for(int i = m->rows-1; i >= 0; i--){
        for(int j = m->cols-1; j >= 0; j--){
            if(i + j == m->rows-1){
                m->data[i * m->cols + j] = v->data[idx++];
                if(idx == m->rows){
                    break;
                }
            }
        }
    }
}

double diagonalProduct(matrix*m){
    vector* diagonal = getMainDiagonal(m);
    double product = 1.0;
    for(int i = 0; i < diagonal->cols; i++){
        product *= diagonal->data[i];
    }
    deleteVector(diagonal);
    return product;
}

bool isMatrixEqual(matrix* m, matrix* n){
    assert(assertMatrix(m) && assertMatrix(n));
    if(m->rows != n->rows || m->cols != n->cols){
        return false;
    }
    for(int i = 0; i < m->rows; i++){
        for(int j = 0; j < m->cols; j++){
            if(m->data[i * m->cols + j] != n->data[i * n->cols + j]){
                return false;
            }
        }
    }
    return true;
}

bool hasSameDimensions(matrix* m, matrix* n){
    assert(assertMatrix(m) && assertMatrix(n));
    return (m->rows == n->rows) && (m->cols == n->cols);
}

bool isZeroMatrix(matrix* m){
    assertMatrix(m);
    for(int i = 0; i < m->rows; i++){
        for(int j = 0; j < m->cols; j++){
            if(m->data[i * m->cols + j] != 0){
                return false;
            }
        }
    }
    return true;
}

bool isIdentityMatrix(matrix* m){
    if(!isSquareMatrix(m)){
        return false;
    }
    for(int i = 0; i < m->rows; i++){
        for(int j = 0; j < m->cols; j++){
            if(i == j && m->data[i * m->cols + j] != 1.0){
                return false;
            } else if(i != j && m->data[i * m->cols + j] != 0.0) {
                return false;
            }
        }
    }
    return true;
}

bool isSquareMatrix(matrix* m){
    assertMatrix(m);
    return (m->rows == m->cols);
}

bool isInvertible(matrix* m){
    return isSquareMatrix(m) && determinant(m) != 0;
}

bool isDiagonalMatrix(matrix* m){
    assert(isSquareMatrix(m));
    for(int i = 0; i < m->rows; i++){
        for(int j = 0; j < m->cols; j++){
            if(i != j && m->data[i * m->cols + j] != 0){
                return false;
            }
        }
    }
    return true;
}

bool isTriangularMatrix(matrix* m){
    assert(isSquareMatrix(m));
    return exclusiveOr(isUpTriMatrix(m), isLoTriMatrix(m));
}

bool isUpTriMatrix(matrix* m){
    assert(isSquareMatrix(m));
    for(int i = 0; i < m->rows; i++){
        for(int j = 0; j < i; j++){
            if(m->data[i * m->cols + j] != 0){
                return false;
            }
        }
    }
    return true;
}

bool isLoTriMatrix(matrix* m){
    assert(isSquareMatrix(m));
    for(int i = 0; i < m->rows; i++){
        for(int j = i+1; j < m->cols; j++){
            if(m->data[i * m->cols + j] != 0){
                return false;
            }
        }
    }
    return true;
}

bool isMatrixSymmetric(matrix* m){
    matrix* t = transposeMatrix(m);
    bool equal = isMatrixEqual(m, t);
    deleteMatrix(t);
    return equal;
}

bool hasZeroRow(matrix* m){
    assertMatrix(m);
    bool allZeroes = true;
    for(int i = 0; i < m->rows; i++){
        for(int j = 0; j < m->cols; j++){
            if(m->data[i * m->cols + j] != 0){
                allZeroes = false;
            }
        }
        if(allZeroes){
            return true;
        }
        allZeroes = true;
    }
    return false;
}

bool hasZeroCol(matrix* m){
    assertMatrix(m);
    bool allZeroes = true;
    for(int j = 0; j < m->rows; j++){
        for(int i = 0; i < m->cols; i++){
            if(m->data[i * m->cols + j] != 0){
                allZeroes = false;
            }
        }
        if(allZeroes){
            return true;
        }
        allZeroes = true;
    }
    return false;
}

double determinant(matrix* m){
    assert(isSquareMatrix(m));
    // use leibniz and laplace for smaller matrices
    switch(m->rows){ 
        case 1: return m->data[0];
        case 2: return (m->data[0] * m->data[3]) - (m->data[1] * m->data[2]);
        case 3: return (m->data[0]*((m->data[4]*m->data[8])-(m->data[5]*m->data[7]))) -
                       (m->data[1]*((m->data[3]*m->data[8])-(m->data[5]*m->data[6]))) +
                       (m->data[2]*((m->data[3]*m->data[7])-(m->data[4]*m->data[6]))) ;
    }
    if(isTriangularMatrix(m)){
        return diagonalProduct(m);
    }
    matrix* l = NULL;
    matrix* u = NULL;
    matrix* p = NULL;
    int sw;
    luDecomposition(m,&l,&u,&p,&sw);

    printf("\n");
    printMatrix(p, false);
    printf("\n%d\n", sw);
    
    double det = pow(-1,(double) sw) * determinant(l) * determinant(u);
    printf("\n%f\n", det);
    deleteMatrix(p);
    deleteMatrix(u);
    deleteMatrix(l);
    return 0.0;
}

matrix* transposeMatrix(matrix* m){
    assertMatrix(m);
    matrix* t = zeroMatrix(m->cols, m->rows);
    for(int i = 0; i < m->rows; i++){
        for(int j = 0; j < m->cols; j++){
            t->data[j * t->cols + i] = m->data[i * m->cols + j];
        }
    }
    return t;
}

double traceMatrix(matrix* m){
    assert(isSquareMatrix(m));
    double trace = 0;
    for(int i = 0; i < m->rows; i++){
        trace += m->data[i * m->cols + i];
    }
    return trace;
}

matrix* addMatrices(matrix* m, matrix* n){
    assert(hasSameDimensions(m, n));
    matrix* sum = nullMatrix(m->rows, m->cols);
    int idx = 0;
    for(int i = 0; i < m->rows; i++){
        for(int j = 0; j < m->cols; j++){
            sum->data[idx] = m->data[idx] + n->data[idx];
            idx++;
        }
    }
    return sum;
}

matrix* powMatrix(matrix* m, double k){
    assertMatrix(m);
    matrix* p = nullMatrix(m->rows, m->cols);
    for(int i = 0; i < m->rows; i++){
        for(int j = 0; j < m->cols; j++){
            p->data[i * m->cols + j] = pow(m->data[i * m->cols + j], k);
        }
    }
    return p;
}

matrix* multiplyMatrices(matrix* m, matrix* n){
    assert(assertMatrix(m) && assertMatrix(n) && m->cols == n->cols && m->rows == n->rows);
    matrix* prod = zeroMatrix(m->cols, m->cols);
    for(int j = 0; j < m->cols; j++){
        for(int i = 0; i < m->cols; i++){
            double val = 0.0;
            for(int k = 0; k < m->cols; k++){
                val += ((m->data[i * m->cols + k] * n->data[k * m->cols + j]));
            }
            prod->data[i * m->cols + j] = val;
        }
    }
    return prod;
}

matrix* scaleMatrix(matrix* m, double s){
    assertMatrix(m);
    matrix* scaled = nullMatrix(m->rows, m->cols);
    for(int i = 0; i < m->rows; i++){
        for(int j = 0; j < m->cols; j++){
            scaled->data[i * m->cols + j] = m->data[i * m->cols + j] * s;
        }
    }
    return scaled;
}

matrix* subMatrix(matrix* m, double i, double j){
    assert(assertMatrix(m) && i >= 0 && i < m->rows && j >= 0 && j < m->cols);
    matrix* sm = nullMatrix(i,j);
    for(int row = 0; row < sm->rows; row++){
        for(int col = 0; col < sm->cols; col++){
            sm->data[row * sm->cols + col] = m->data[row * m->cols + col];
        }
    }
    return sm;
}

void luDecomposition(matrix* m, matrix** l, matrix** u, matrix** p, int* swaps){
    assert(isSquareMatrix(m) && *l == NULL && *u == NULL && *p == NULL);
    int n = m->cols;
    *l = zeroMatrix(n, n);
    *u = zeroMatrix(n, n);
    *p = pivotMatrix(m, swaps);
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
    /*
    for(int i = 0; i < m->cols; i++){
        for(int k = i; k < m->cols; k++){
            double sumU = 0;
            for(int j = 0; j < i; j++){
                sumU += ((*l)->data[i * m->cols + j]) * ((*u)->data[j * m->cols + k]);
            }
            (*u)->data[i * m->cols + k] = m->data[i * m->cols + k] - sumU;
        }
        for(int k = i; k < m->cols; k++){
            if(i == k){
                (*l)->data[i * m->cols + i] = 1;
            } else{
                double sumL = 0;
                for(int j = 0; j < i; j++){
                    sumL += (((*l)->data[k * m->cols + j]) * ((*u)->data[j * m->cols + i]));
                }
                (*l)->data[k * m->cols + i] = (m->data[k * m->cols + i] - sumL) / (*u)->data[i * m->cols + i];
            }
        }
    }
    */
}

matrix* inverseMatrix(matrix* m){
    assert(isInvertible(m));
    matrix* inv = nullMatrix(m->rows, m->cols);
    return inv;
}

matrix* pivotMatrix(matrix* m, int* swaps){
    assert(isSquareMatrix(m));
    int n = m->cols;
    matrix* pivot = identityMatrix(n);
    for(int i = 0; i < n; i++){
        double max = m->data[i * n + i];
        int row = i;
        for(int j = i; j < n; j++){
            if(m->data[j * n + i] > max){
                max = m->data[j * n + i];
                row = j;
            }
        }
        if(i != row){
            vector* v = getRowVector(pivot, i);
            vector* w = getRowVector(pivot, row);
            setRowVector(pivot, i, w);
            setRowVector(pivot, row, v);
            deleteVector(w);
            deleteVector(v);
            swaps++;
        }
    }
    return pivot;
}

void printMatrix(matrix* m, bool includeIndices){
    assertMatrix(m);
    for(int i = 0; i < m->rows; i++){
        for(int j = 0; j < m->cols; j++){
            if(includeIndices){
                printf("[%d,%d] -> ", i, j);
            }
            printf("%8.2f ", m->data[i * m->cols + j]);
        }
        if(i < m->rows){
            printf("\n");
        }
    }
}

matrix* scaleNSpace(matrix* m, double k){
    assert(isSquareMatrix(m));
    matrix* n = zeroMatrix(m->cols,m->cols);
    vector* v = zeroVector(m->cols);
    fillVector(&v, k);
    setMainDiagonal(n, v);
    matrix* ref = multiplyMatrices(m, n);
    deleteVector(v);
    deleteMatrix(n);
    return ref;
}

matrix* reflectAxis2D(matrix* m, int axis){
    assert(isSquareMatrix(m) && m->cols == 2);
    matrix* n = zeroMatrix(2,2);
    setMatrixElement(n,0,0,(axis) ? 1 : -1);
    setMatrixElement(n,1,1,(axis) ? -1 : 1);
    matrix* ref = multiplyMatrices(m, n);
    deleteMatrix(n);
    return ref;
}

matrix* reflectAxis3D(matrix* m, int axis){
    assert(isSquareMatrix(m) && m->cols == 3 && axis >= 0 && axis <= 2);
    matrix* n = nullMatrix(3,3);
    if(axis == 0){
        double data[9] = {1,0,0,0,1,0,0,0,-1}; // XY
        setMainDiagonal(m, newVector(data, 3)); 
    } else if(axis == 1){
        double data[9] = {1,0,0,0,-1,0,0,0,1}; // XZ
        setMainDiagonal(m, newVector(data, 3)); 
    } else{
        double data[9] = {-1,0,0,0,1,0,0,0,1}; // YZ
        setMainDiagonal(m, newVector(data, 3)); 
    }
    matrix* ref = multiplyMatrices(m, n);
    deleteMatrix(n);
    return ref;
}

matrix* orthProj2D(matrix* m, int axis){
    assert(isSquareMatrix(m) && m->cols == 2);
    matrix* n = zeroMatrix(2,2);
    setMatrixElement(n,axis,axis,1);
    matrix* ref = multiplyMatrices(m,n);
    deleteMatrix(n);
    return ref;
}

matrix* orthProj3D(matrix* m, int axis){
    assert(isSquareMatrix(m) && m->cols == 3);
    matrix* n = zeroMatrix(3,3);
    switch(axis){
        case 0: // XY plane
            setMatrixElement(n,0,0,1);
            setMatrixElement(n,1,1,1); 
            break;
        case 1: // XZ plane
            setMatrixElement(n,0,0,1); 
            setMatrixElement(n,2,2,1);
            break;
        case 2: // YZ plane
            setMatrixElement(n,1,1,1);
            setMatrixElement(n,2,2,1);
            break;
    }
    matrix* ref = multiplyMatrices(m, n);
    deleteMatrix(n);
    return ref;
}

matrix* shear2D(matrix* m, double k, int axis){
    assert(isSquareMatrix(m) && m->cols == 2);
    matrix* n = zeroMatrix(2,2);
    setMatrixElement(n,0,0,1);
    setMatrixElement(n,0,1,(axis) ? k : 0);
    setMatrixElement(n,1,0,(axis) ? 0 : k);
    setMatrixElement(n,1,1,1);
    matrix* sheared = multiplyMatrices(m,n);
    deleteMatrix(n);
    return sheared;
}

matrix* rotate3D(matrix* m, double theta, int axis){
    assert(isSquareMatrix(m) && m->cols == 3);
    matrix* n = zeroMatrix(3,3);
    switch(axis){
        case 0: // X
            setMatrixElement(n,0,0,1);
            setMatrixElement(n,1,0,cos(theta));
            setMatrixElement(n,1,1,-sin(theta));
            setMatrixElement(n,2,1,sin(theta));
            setMatrixElement(n,2,2,cos(theta));
            break;
        case 1: // Y
            setMatrixElement(n,0,0,cos(theta));
            setMatrixElement(n,1,2,sin(theta));
            setMatrixElement(n,1,1,1);
            setMatrixElement(n,2,0,-sin(theta));
            setMatrixElement(n,2,2,cos(theta));
            break;
        case 2: // Z
            setMatrixElement(n,0,0,cos(theta));
            setMatrixElement(n,0,1,-sin(theta));
            setMatrixElement(n,2,0,sin(theta));
            setMatrixElement(n,2,1,cos(theta));
            setMatrixElement(n,2,2,1);
            break;
    }
    matrix* ref = multiplyMatrices(m, n);
    deleteMatrix(n);
    return ref;
}
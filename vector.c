#include "linear-algebra.h"


bool assertVector(vector* v){
    assert(v != NULL && v->data != NULL);
    return true;
}

vector* newVector(double* d, int cols){
    assert(d != NULL && cols > 0);
    vector* v = nullVector(cols);
    int idx = 0;
    for(int i = 0; i < v->cols; i++){
        v->data[i] = d[idx++];
    }
    return v;
}

vector* nullVector(int cols){
    assert(cols > 0);
    vector* v = (vector*) malloc(sizeof(vector));
    v->cols = cols;
    v->data = (double*) malloc(cols * sizeof(double));
    return v;
}

vector* zeroVector(int cols){
    vector* v = nullVector(cols);
    fillVector(&v, 0);
    return v;
}

void fillVector(vector** v, double n){
    assertVector(*v);
    for(int i = 0; i < (*v)->cols; i++){
        (*v)->data[i] = n;
    }
}

void deleteVector(vector* v){
    free(v->data);
    v->data = NULL;
    free(v);
    v = NULL;
}

vector* copyVector(vector* v){
    assertVector(v);
    vector* c = zeroVector(v->cols);
    for(int i = 0; i < v->cols; i++){
        c->data[i] = v->data[i];
    }
    return c;
}

int vectorSize(vector* v){
    assertVector(v);
    return v->cols;
}

int vectorSizeBytes(vector* v){
    return sizeof(double) * vectorSize(v);
}

bool isVectorEqual(vector* v, vector* w){
    assert(assertVector(v) && assertVector(w));
    if(v->cols != w->cols){
        return false;
    }
    for(int i = 0; i < v->cols; i++){
        if(v->data[i] != w->data[i]){
            return false;
        }
    }
    return true;
}

void setVectorElement(vector* v, int i, double s){
    assert(assertVector(v) && i >= 0 && i < v->cols);
    v->data[i] = s;
}

double getVectorElement(vector* v, int i){
    assert(assertVector(v) && i >= 0 && i < v->cols);
    return v->data[i];
}

void printVector(vector* v, bool includeIndices){
    assertVector(v);
    for(int i = 0; i < v->cols; i++){
        if(includeIndices){
            printf("[%d] -> ", i);
        }
        printf("%16.8f ", v->data[i]);
    }
}

double vectorMagnitude(vector* v){
    assertVector(v);
    double sum = 0;
    for(int i = 0; i < v->cols; i++){
        sum += (v->data[i] * v->data[i]);
    }
    return sqrt(sum);
}

bool isUnitVector(vector* v){
    return vectorMagnitude(v) == 1;
}

bool isVectorOrthogonal(vector* v1, vector* v2){
    assert(assertVector(v1) && assertVector(v2));
    return dotProduct(v1,v2) == 0;
}

double dotProduct(vector* v, vector* w){
    assert(assertVector(v) && assertVector(w) && v->cols == w->cols);
    double dp = 0;
    for(int i = 0; i < v->cols; i++){
        dp += (v->data[i] * w->data[i]);
    }
    return dp;
}

vector* crossProduct(vector* v, vector* w){
    assert(assertVector(v) && assertVector(w) && v->cols == 3 && v->cols == 3);
    vector* c = nullVector(3);
    c->data[0] = (v->data[1] * w->data[2]) - (v->data[2] * w->data[1]);
    c->data[1] = (v->data[0] * w->data[2]) - (v->data[2] * w->data[0]);
    c->data[2] = (v->data[0] * w->data[1]) - (v->data[1] * w->data[0]);
    return c;
}

double vectorDistance(vector* v, vector* w){
    assert(assertVector(v) && assertVector(w) && v->cols == w->cols);
    double d = 0;
    for(int i = 0; i < v->cols; i++){
        d += (w->data[i] - v->data[i]) * (w->data[i] - v->data[i]);
    }
    return sqrt(d);
}

vector* addVectors(vector* v, vector* w){
    assert(assertVector(v) && assertVector(w) && v->cols == w->cols);
    vector* sum = nullVector(v->cols);
    for(int i = 0; i < v->cols; i++){
        sum->data[i] = v->data[i] + w->data[i];
    }
    return sum;
}

vector* scaleVector(vector* v, double s){
    assert(assertVector(v));
    vector* scaled = nullVector(v->cols);
    for(int i = 0; i < v->cols; i++){
        scaled->data[i] = v->data[i] * s;
    }
    return scaled;
}

double scalarTripleProduct(vector* v1, vector* v2, vector* v3){
    assert(v1->cols == 3 && v2->cols == 3 && v3->cols == 3);
    return dotProduct(v1, crossProduct(v2, v3));
}

vector* powVector(vector* v, double k){
    assertVector(v);
    vector* p = nullVector(v->cols);
    for(int i = 0; i < v->cols; i++){
        p->data[i] = pow(v->data[i], k);
    }
    return p;
}
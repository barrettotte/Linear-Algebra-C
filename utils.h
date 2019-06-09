#include <execinfo.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>


// Basic XOR operator
bool exclusiveOr(bool a, bool b);


// Round double to n digits
double roundn(double val, unsigned int n);


// Basic custom assert
void assert(const int condition);


// Print the call stack up until assertion fail
void printCallStack();

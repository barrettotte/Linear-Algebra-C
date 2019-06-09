#include "utils.h"


bool exclusiveOr(bool a, bool b){
    return (a || b) && (!(a && b));
}

double roundn(double val, unsigned int n){
    assert(n > 0);
    double x = pow(10, n);
    return round(val * x) / x;
}

void assert(const int condition){
    if(!condition){
        printf("Assertion failed.\n");
        printCallStack();
        exit(1);
    }
}

void printCallStack(){
    void* buffer[50];
    int levels = backtrace(buffer, 50);
    char** symbols = backtrace_symbols(buffer, levels);
    printf("----------------------------- STACK TRACE ------------------------------\n");
    for(int i = 1; i < levels; i++){
        printf(" %3d  %s\n", i-1, symbols[i]);
    }
    printf("------------------------------------------------------------------------\n");
}
/* NOTE: I was supposed to look into using addr2line and getting an
    awesome stacktrace printed to the console with line numbers, but honestly 
    if I just have function calls printed, that's good enough for my purposes.
*/

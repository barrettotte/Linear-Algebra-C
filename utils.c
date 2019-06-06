#include "utils.h"
#include <execinfo.h>
#include <signal.h>
#include <stdio.h>

void assert(const int condition){
    if(!condition){
        printf("ASSERTION FAILED!!!!");
        printCallStack();
        exit(1);
    }
}

void printCallStack(){
    //TODO:
}
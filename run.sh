#!/bin/bash
clear
gcc -o test_matrix -std=c99 -Wall -g -rdynamic -Werror test.c matrix.c assert-custom.c
./test_matrix
rm -rf test_matrix
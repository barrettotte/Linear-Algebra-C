#!/bin/bash
gcc -o test_matrix -std=c99 -Wall -g test.c matrix.c utils.c
./test_matrix
rm -rf test_matrix
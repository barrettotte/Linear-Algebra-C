#!/bin/bash
gcc -o dbg_matrix -std=c99 -rdynamic -Wall -g test.c matrix.c assert-custom.c
# apt-get install valgrind
valgrind --leak-check=full \
         --show-leak-kinds=all \
         --track-origins=yes \
         --verbose \
         --log-file=valgrind-out.txt \
         ./dbg_matrix

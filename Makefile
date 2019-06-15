default: build

build:
	clear
	gcc -o test_matrix -std=c99 -Wall -g -rdynamic -Werror matrix.c test.c utils.c vector.c -lm
	./test_matrix
debug:
	clear
	gcc -o test_matrix -std=c99 -Wall -g -rdynamic -Werror matrix.c test.c utils.c vector.c -lm
	./test_matrix
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=valgrind-out.txt ./test_matrix
clean:
	rm -rf test_matrix valgrind-out.txt
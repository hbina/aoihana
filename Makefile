test_fold:
	mkdir -p ./build
	gcc ./tests/fold.c -g -Wall -o ./build/test_fold
	valgrind --leak-check=full --show-leak-kinds=all ./build/test_fold

test_vec:
	mkdir -p ./build
	gcc ./tests/vec.c -g -Wall -o ./build/test_vec
	valgrind --leak-check=full --show-leak-kinds=all ./build/test_vec

test: test_fold test_vec
test_fold:
	mkdir -p ./build
	gcc ./tests/fold.c -g -o ./build/test_fold
	./build/test_fold

test_vec:
	mkdir -p ./build
	gcc ./tests/vec.c -g -o ./build/test_vec
	./build/test_vec

test: test_fold test_vec
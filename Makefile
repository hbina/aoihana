test_fold:
	mkdir -p ./build
	gcc ./tests/fold.c -g -Wall -Iinclude/ -o ./build/test_fold
	valgrind --leak-check=full --show-leak-kinds=all ./build/test_fold

test_vec:
	mkdir -p ./build
	gcc ./tests/vec.c -g -Wall -Iinclude/ -o ./build/test_vec
	valgrind --leak-check=full --show-leak-kinds=all ./build/test_vec

test_view:
	mkdir -p ./build
	gcc ./tests/view.c -g -Wall -Iinclude/ -o ./build/test_view
	valgrind --leak-check=full --show-leak-kinds=all ./build/test_view

test: test_fold test_vec test_view
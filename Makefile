test_fold:
	mkdir -p ./build
	gcc ./tests/fold.c -g -Wall -Iinclude -o ./build/test_fold
	valgrind --leak-check=full --show-leak-kinds=all ./build/test_fold

test_vec:
	mkdir -p ./build
	gcc ./tests/vec.c -g -Wall -Iinclude -o ./build/test_vec
	valgrind --leak-check=full --show-leak-kinds=all ./build/test_vec

test_view:
	mkdir -p ./build
	gcc ./tests/view.c -g -Wall -Iinclude -o ./build/test_view
	valgrind --leak-check=full --show-leak-kinds=all ./build/test_view

test_vec_name:
	mkdir -p ./build
	gcc ./tests/vec_name.c -g -Wall -Iinclude -o ./build/test_vec_name
	valgrind --leak-check=full --show-leak-kinds=all ./build/test_vec_name

test_smallvec:
	mkdir -p ./build
	gcc ./tests/smallvec.c -gdwarf-2 -g3 -Wall -Iinclude -o ./build/test_smallvec
	valgrind --leak-check=full --show-leak-kinds=all ./build/test_smallvec

test: test_fold test_vec test_view test_vec_name test_smallvec

clean:
	rm -rf ./build/
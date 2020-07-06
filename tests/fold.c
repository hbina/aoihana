#include <assert.h>

#include "../include/aoihana.h"

const int TEST_VEC_SIZE = 30;

int main(int argc, char **argv)
{
    Vec_int vec = vec_int_with_capacity(TEST_VEC_SIZE);
    for (int c = 0; c != TEST_VEC_SIZE; c++)
    {
        vec_int_push_back(&vec, 1);
    }
    const int result = fold_int(vec.ptr, vec.len, 0, plus_int);
    assert(result == TEST_VEC_SIZE);
    vec_int_destroy(&vec);
}

#include <assert.h>

#include "../include/aoihana.h"

const int TEST_VEC_SIZE = 30;

int main(int argc, char **argv)
{
    Vec_int vec = vec_int_with_capacity(TEST_VEC_SIZE);

    /// Check for basic creation and insertion.
    for (int c = 0; c != TEST_VEC_SIZE; c++)
    {
        vec_int_push_back(&vec, c);
    }
    for (int c = 0; c != TEST_VEC_SIZE; c++)
    {
        Vec_Result_int result = vec_int_at(&vec, c);
        if (result.success)
        {
            assert(result.value == c);
        }
        else
        {
            assert(false);
        }
    }

    /// Check that access out of index will yield a negative result.
    Vec_Result_int result = vec_int_at(&vec, TEST_VEC_SIZE);
    if (result.success)
    {
        assert(false);
    }
    else
    {
        assert(true);
    }

    vec_int_destroy(&vec);
}

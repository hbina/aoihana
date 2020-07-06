#include <assert.h>

#include "../include/aoihana.h"

const int TEST_VEC_SIZE = 30;

int main(int argc, char **argv)
{
    Vec_int vec = vec_int_with_capacity(TEST_VEC_SIZE);

    /// Check insertion.
    for (int c = 0; c != TEST_VEC_SIZE; c++)
    {
        vec_int_push_back(&vec, c);
    }

    /// Check access.
    for (int c = 0; c != TEST_VEC_SIZE; c++)
    {
        const Vec_Result_int result = vec_int_at(&vec, c);
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
    {
        Vec_Result_int result = vec_int_at(&vec, TEST_VEC_SIZE);
        if (result.success)
        {
            assert(false);
        }
        else
        {
            assert(true);
        }
    }

    /// Test folding over Vec calculating the sum.
    {
        const int free_fold_result = fold_int(vec.ptr, vec.len, 0, plus_int);
        const int vec_fold_result = vec_int_fold(&vec, 0, plus_int);
        assert(free_fold_result == vec_fold_result);
    }

    /// Cleanup!
    vec_int_destroy(&vec);
}

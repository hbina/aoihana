#include <assert.h>

#include "../include/aoihana.h"

const int TEST_VEC_SIZE = 30;

#define TEST_ACCESS_AND_VALUE(vec, index, value) assert(vec_int_at(&vec, index).success == true && *vec_int_at(&vec, index).ptr == value);

void test_removing_element_based_on_index()
{
    Vec_int vec = vec_int_with_iota(5, 0, successor_int);

    for (int index = 0; index != 5; index++)
    {
        TEST_ACCESS_AND_VALUE(vec, 0, 0);
        TEST_ACCESS_AND_VALUE(vec, 1, 1);
        TEST_ACCESS_AND_VALUE(vec, 2, 2);
        TEST_ACCESS_AND_VALUE(vec, 3, 3);
        TEST_ACCESS_AND_VALUE(vec, 4, 4);
    }

    const int initial_capacity = vec.capacity;

    assert(vec_int_remove(&vec, 3) == true);

    {
        TEST_ACCESS_AND_VALUE(vec, 0, 0);
        TEST_ACCESS_AND_VALUE(vec, 1, 1);
        TEST_ACCESS_AND_VALUE(vec, 2, 2);
        TEST_ACCESS_AND_VALUE(vec, 3, 4);
    }

    assert(vec_int_remove(&vec, 0) == true);

    {
        TEST_ACCESS_AND_VALUE(vec, 0, 1);
        TEST_ACCESS_AND_VALUE(vec, 1, 2);
        TEST_ACCESS_AND_VALUE(vec, 2, 4);
    }

    assert(vec_int_remove(&vec, 1) == true);

    {
        TEST_ACCESS_AND_VALUE(vec, 0, 1);
        TEST_ACCESS_AND_VALUE(vec, 1, 4);
    }

    assert(vec_int_remove(&vec, 0) == true);
    assert(vec_int_remove(&vec, 0) == true);

    assert(vec.len == 0);
    assert(vec.capacity == initial_capacity);

    vec_int_destroy(&vec);
}

void test_apply_if_exist()
{
    Vec_int vec = vec_int_with_iota(5, 0, successor_int);
    vec_int_apply_if_exist(&vec, 0, successor_int);
    TEST_ACCESS_AND_VALUE(vec, 0, 1);
    TEST_ACCESS_AND_VALUE(vec, 1, 1);
    TEST_ACCESS_AND_VALUE(vec, 2, 2);
    TEST_ACCESS_AND_VALUE(vec, 3, 3);
    TEST_ACCESS_AND_VALUE(vec, 4, 4);
    vec_int_destroy(&vec);
}

// TODO: Refactor these tests out into their own functions...
int main(int argc, char **argv)
{
    /// Create with capacity.
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
        assert(result.success && *result.ptr == c);
    }

    /// Check that access out of index will yield a negative result.
    {
        Vec_Result_int result = vec_int_at(&vec, TEST_VEC_SIZE);
        assert(result.success == false);
    }

    /// Create with iota.
    Vec_int vec_iota = vec_int_with_iota(30, 0, successor_int);

    /// Check Vec created through iota and normal insertion matches.
    for (int c = 0; c != TEST_VEC_SIZE; c++)
    {
        Vec_Result_int result_iota = vec_int_at(&vec_iota, c);
        Vec_Result_int result_vec = vec_int_at(&vec, c);
        assert(result_iota.success && result_vec.success && *result_iota.ptr == *result_vec.ptr);
    }

    /// Test folding over Vec calculating the sum.
    {
        const int free_fold_result = fold_int(vec.ptr, vec.len, 0, plus_int);
        const int vec_fold_result = vec_int_fold(&vec, 0, plus_int);
        assert(free_fold_result == vec_fold_result);
    }

    test_removing_element_based_on_index();
    test_apply_if_exist();

    /// Cleanup!
    vec_int_destroy(&vec);
    vec_int_destroy(&vec_iota);
}

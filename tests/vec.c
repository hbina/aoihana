#include <assert.h>

#include "../include/aoihana.h"

#define TEST_ACCESS_AND_VALUE(vec, index, value)                               \
  assert(vec_int_at(&vec, index).success == true &&                            \
         *vec_int_at(&vec, index).ptr == value);

#define TEST_ACCESS_FAILURE(vec, index)                                        \
  assert(vec_int_at(&vec, index).success == false);

void
test_removing_element_based_on_index()
{
  Vec_int vec = vec_int_with_iota(5, 0, successor_int);

  for (int index = 0; index != 5; index++) {
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

void
test_apply_if_exist()
{
  Vec_int vec = vec_int_with_iota(5, 0, successor_int);
  TEST_ACCESS_AND_VALUE(vec, 0, 0);
  TEST_ACCESS_AND_VALUE(vec, 1, 1);
  TEST_ACCESS_AND_VALUE(vec, 2, 2);
  TEST_ACCESS_AND_VALUE(vec, 3, 3);
  TEST_ACCESS_AND_VALUE(vec, 4, 4);
  vec_int_apply_if_exist(&vec, 0, successor_int);
  TEST_ACCESS_AND_VALUE(vec, 0, 1);
  TEST_ACCESS_AND_VALUE(vec, 1, 1);
  TEST_ACCESS_AND_VALUE(vec, 2, 2);
  TEST_ACCESS_AND_VALUE(vec, 3, 3);
  TEST_ACCESS_AND_VALUE(vec, 4, 4);
  vec_int_destroy(&vec);
}

void
test_basic_insertion()
{
  const int TEST_VEC_SIZE = 30;
  Vec_int vec = vec_int_with_capacity(TEST_VEC_SIZE);

  for (int c = 0; c != TEST_VEC_SIZE; c++) {
    vec_int_push_back(&vec, c);
  }

  for (int c = 0; c != TEST_VEC_SIZE; c++) {
    TEST_ACCESS_AND_VALUE(vec, c, c);
  }

  vec_int_destroy(&vec);
}

void
test_invalid_access_yield_negative_result()
{
  const int TEST_VEC_SIZE = 5;
  Vec_int vec = vec_int_with_iota(TEST_VEC_SIZE, 0, successor_int);

  for (int c = 0; c != TEST_VEC_SIZE; c++) {
    TEST_ACCESS_AND_VALUE(vec, c, c);
  }

  TEST_ACCESS_FAILURE(vec, 5);
  TEST_ACCESS_FAILURE(vec, -1);
  TEST_ACCESS_FAILURE(vec, 3123);
  TEST_ACCESS_FAILURE(vec, 2352432);
  vec_int_destroy(&vec);
}

void
test_folding_helper_function_is_correct()
{
  const int TEST_VEC_SIZE = 5;
  Vec_int vec = vec_int_with_iota(TEST_VEC_SIZE, 0, successor_int);
  const int free_fold_result = fold_int(vec.ptr, vec.len, 0, plus_int);
  const int vec_fold_result = vec_int_fold(&vec, 0, plus_int);
  assert(free_fold_result == vec_fold_result);
  vec_int_destroy(&vec);
}

void
test_sorting()
{
  Vec_int vec = vec_int_with_iota(5, 5, predecessor_int);

  TEST_ACCESS_AND_VALUE(vec, 0, 5);
  TEST_ACCESS_AND_VALUE(vec, 1, 4);
  TEST_ACCESS_AND_VALUE(vec, 2, 3);
  TEST_ACCESS_AND_VALUE(vec, 3, 2);
  TEST_ACCESS_AND_VALUE(vec, 4, 1);

  vec_int_sort(&vec, le_int);

  TEST_ACCESS_AND_VALUE(vec, 0, 1);
  TEST_ACCESS_AND_VALUE(vec, 1, 2);
  TEST_ACCESS_AND_VALUE(vec, 2, 3);
  TEST_ACCESS_AND_VALUE(vec, 3, 4);
  TEST_ACCESS_AND_VALUE(vec, 4, 5);

  vec_int_sort(&vec, ge_int);

  TEST_ACCESS_AND_VALUE(vec, 0, 5);
  TEST_ACCESS_AND_VALUE(vec, 1, 4);
  TEST_ACCESS_AND_VALUE(vec, 2, 3);
  TEST_ACCESS_AND_VALUE(vec, 3, 2);
  TEST_ACCESS_AND_VALUE(vec, 4, 1);

  vec_int_destroy(&vec);
}

int
main(void)
{
  test_basic_insertion();
  test_invalid_access_yield_negative_result();
  test_removing_element_based_on_index();
  test_apply_if_exist();
  test_folding_helper_function_is_correct();
  test_sorting();
}

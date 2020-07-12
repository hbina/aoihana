#include <assert.h>

#include "aoihana/fold.h"
#include "aoihana/functional.h"
#include "aoihana/vector.h"

DECLARE_VEC_NAME(int, veci);
DECLARE_FOLD(int);
DECLARE_ARITHMETIC_OPERATIONS(int);

#define TEST_ACCESS_AND_VALUE(vec, index, value)                               \
  assert(veci_at(vec, index).success == true &&                                \
         *veci_at(vec, index).ptr == value);

#define TEST_ACCESS_FAILURE(vec, index)                                        \
  assert(veci_at(vec, index).success == false);

void
test_removing_element_based_on_index()
{
  veci vec = veci_with_iota(5, 0, successor_int);

  for (int index = 0; index != 5; index++) {
    TEST_ACCESS_AND_VALUE(vec, 0, 0);
    TEST_ACCESS_AND_VALUE(vec, 1, 1);
    TEST_ACCESS_AND_VALUE(vec, 2, 2);
    TEST_ACCESS_AND_VALUE(vec, 3, 3);
    TEST_ACCESS_AND_VALUE(vec, 4, 4);
  }

  const int initial_capacity = vec.capacity;

  assert(veci_remove(&vec, 3) == true);

  {
    TEST_ACCESS_AND_VALUE(vec, 0, 0);
    TEST_ACCESS_AND_VALUE(vec, 1, 1);
    TEST_ACCESS_AND_VALUE(vec, 2, 2);
    TEST_ACCESS_AND_VALUE(vec, 3, 4);
  }

  assert(veci_remove(&vec, 0) == true);

  {
    TEST_ACCESS_AND_VALUE(vec, 0, 1);
    TEST_ACCESS_AND_VALUE(vec, 1, 2);
    TEST_ACCESS_AND_VALUE(vec, 2, 4);
  }

  assert(veci_remove(&vec, 1) == true);

  {
    TEST_ACCESS_AND_VALUE(vec, 0, 1);
    TEST_ACCESS_AND_VALUE(vec, 1, 4);
  }

  assert(veci_remove(&vec, 0) == true);
  assert(veci_remove(&vec, 0) == true);

  assert(vec.len == 0);
  assert(vec.capacity == initial_capacity);

  veci_destroy(&vec);
}

void
test_apply_if_exist()
{
  veci vec = veci_with_iota(5, 0, successor_int);
  TEST_ACCESS_AND_VALUE(vec, 0, 0);
  TEST_ACCESS_AND_VALUE(vec, 1, 1);
  TEST_ACCESS_AND_VALUE(vec, 2, 2);
  TEST_ACCESS_AND_VALUE(vec, 3, 3);
  TEST_ACCESS_AND_VALUE(vec, 4, 4);
  veci_apply_if_exist(vec, 0, successor_int);
  TEST_ACCESS_AND_VALUE(vec, 0, 1);
  TEST_ACCESS_AND_VALUE(vec, 1, 1);
  TEST_ACCESS_AND_VALUE(vec, 2, 2);
  TEST_ACCESS_AND_VALUE(vec, 3, 3);
  TEST_ACCESS_AND_VALUE(vec, 4, 4);
  veci_destroy(&vec);
}

void
test_basic_insertion()
{
  const int TEST_VEC_SIZE = 30;
  veci vec = veci_with_capacity(TEST_VEC_SIZE);

  for (int c = 0; c != TEST_VEC_SIZE; c++) {
    veci_push_back(&vec, c);
  }

  for (int c = 0; c != TEST_VEC_SIZE; c++) {
    TEST_ACCESS_AND_VALUE(vec, c, c);
  }

  veci_destroy(&vec);
}

void
test_invalid_access_yield_negative_result()
{
  const int TEST_VEC_SIZE = 5;
  veci vec = veci_with_iota(TEST_VEC_SIZE, 0, successor_int);

  for (int c = 0; c != TEST_VEC_SIZE; c++) {
    TEST_ACCESS_AND_VALUE(vec, c, c);
  }

  TEST_ACCESS_FAILURE(vec, 5);
  TEST_ACCESS_FAILURE(vec, -1);
  TEST_ACCESS_FAILURE(vec, 3123);
  TEST_ACCESS_FAILURE(vec, 2352432);
  veci_destroy(&vec);
}

void
test_folding_helper_function_is_correct()
{
  const int TEST_VEC_SIZE = 5;
  veci vec = veci_with_iota(TEST_VEC_SIZE, 0, successor_int);
  const int free_fold_result = fold_int(vec.ptr, vec.len, 0, plus_int);
  const int vec_fold_result = veci_fold(vec, 0, plus_int);
  assert(free_fold_result == vec_fold_result);
  veci_destroy(&vec);
}

void
test_sorting()
{
  veci vec = veci_with_iota(5, 5, predecessor_int);

  TEST_ACCESS_AND_VALUE(vec, 0, 5);
  TEST_ACCESS_AND_VALUE(vec, 1, 4);
  TEST_ACCESS_AND_VALUE(vec, 2, 3);
  TEST_ACCESS_AND_VALUE(vec, 3, 2);
  TEST_ACCESS_AND_VALUE(vec, 4, 1);

  veci_sort(vec, le_int);

  TEST_ACCESS_AND_VALUE(vec, 0, 1);
  TEST_ACCESS_AND_VALUE(vec, 1, 2);
  TEST_ACCESS_AND_VALUE(vec, 2, 3);
  TEST_ACCESS_AND_VALUE(vec, 3, 4);
  TEST_ACCESS_AND_VALUE(vec, 4, 5);

  veci_sort(vec, ge_int);

  TEST_ACCESS_AND_VALUE(vec, 0, 5);
  TEST_ACCESS_AND_VALUE(vec, 1, 4);
  TEST_ACCESS_AND_VALUE(vec, 2, 3);
  TEST_ACCESS_AND_VALUE(vec, 3, 2);
  TEST_ACCESS_AND_VALUE(vec, 4, 1);

  veci_destroy(&vec);
}

void
test_modify_reference()
{
  veci vec = veci_with_iota(5, 0, successor_int);
  const ResultRef_int ref = veci_at(vec, 1);
  *ref.ptr = 0;
  TEST_ACCESS_AND_VALUE(vec, 0, 0);
  TEST_ACCESS_AND_VALUE(vec, 1, 0);
  TEST_ACCESS_AND_VALUE(vec, 2, 2);
  TEST_ACCESS_AND_VALUE(vec, 3, 3);
  TEST_ACCESS_AND_VALUE(vec, 4, 4);
  veci_destroy(&vec);
}

bool
is_23(const int x)
{
  return x == 23;
}

void
test_find_element()
{
  veci vec = veci_with_iota(30, 0, successor_int);
  ResultRef_int ref = veci_find(&vec, is_23);
  assert(ref.success && *ref.ptr == 23);
  veci_destroy(&vec);
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
  test_modify_reference();
  test_find_element();
}

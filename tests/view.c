#include "aoihana/view.h"

#include <assert.h>

DECLARE_VIEW(int);

#define TEST_ACCESS_AND_VALUE(view, index, value)                              \
  assert(view_int_at(view, index).success == true &&                           \
         *view_int_at(view, index).ptr == value);

#define TEST_ACCESS_FAILURE(view, index)                                       \
  assert(view_int_at(view, index).success == false);

const int TEST_VEC_SIZE = 30;
const int INIT_VALUE = 10;

int
main(void)
{
  int* ptr = (int*)malloc(sizeof(int) * TEST_VEC_SIZE);

  for (int i = 0; i < TEST_VEC_SIZE; i++) {
    *(ptr + i) = i;
  }

  View_int view = view_int_from(ptr, TEST_VEC_SIZE);

  for (int i = 0; i < TEST_VEC_SIZE; i++) {
    TEST_ACCESS_AND_VALUE(view, i, i);
  }

  TEST_ACCESS_FAILURE(view, TEST_VEC_SIZE);

  free(ptr);
}

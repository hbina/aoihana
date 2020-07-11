#include <assert.h>
#include <stdlib.h>

#include "aoihana/fold.h"
#include "aoihana/functional.h"

DECLARE_FOLD(int);
DECLARE_ARITHMETIC_OPERATIONS(int);

const int TEST_VEC_SIZE = 30;
const int INIT_VALUE = 10;

int
main(void)
{
  int* ptr = (int*)malloc(sizeof(int) * TEST_VEC_SIZE);

  int sum = INIT_VALUE;
  for (int i = 0; i < TEST_VEC_SIZE; i++) {
    *(ptr + i) = i;
    sum += i;
  }

  const int result_fold = fold_int(ptr, TEST_VEC_SIZE, INIT_VALUE, plus_int);
  assert(result_fold == sum);

  free(ptr);
}

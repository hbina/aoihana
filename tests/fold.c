#include <assert.h>

#include "../include/aoihana.h"

const int TEST_VEC_SIZE = 30;

int
main(int argc, char** argv)
{
  Vec_int vec = vec_int_with_default(TEST_VEC_SIZE, 1);
  const int result_fold = fold_int(vec.ptr, vec.len, 0, plus_int);
  const int result_vec_fold = vec_int_fold(&vec, 0, plus_int);
  assert(result_fold == result_vec_fold);
  vec_int_destroy(&vec);
}

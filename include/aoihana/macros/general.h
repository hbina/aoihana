#pragma once

#include "functional.h"
#include "vector.h"

// Generally desirable configuration
#define IMPLEMENT_FOR_TYPE(type)                                               \
  DECLARE_INTEGER_OPERATIONS(type);                                            \
  DECLARE_ARITHMETIC_OPERATIONS(type);                                         \
  DECLARE_FOLD(type);                                                          \
  DECLARE_VEC(type);                                                           \
  DECLARE_VEC_HELPER_FOLD_FUNCTION(type);                                      \
  DECLARE_ENUMERATE(type);

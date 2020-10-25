#pragma once

#define DECLARE_FOLD_FUNCTION_SIGNATURE(type)                                  \
  typedef type (*type##_fold_function_sig)(const type, const type);

#define DECLARE_FOLD(type)                                                     \
  DECLARE_FOLD_FUNCTION_SIGNATURE(type)                                        \
  type fold_##type(const type* arr,                                            \
                   const int size,                                             \
                   const type init,                                            \
                   const type##_fold_function_sig f)                           \
  {                                                                            \
    type acc = init;                                                           \
    for (int index = 0; index != size; index++) {                              \
      acc = f(acc, *(arr + index));                                            \
    }                                                                          \
    return acc;                                                                \
  }

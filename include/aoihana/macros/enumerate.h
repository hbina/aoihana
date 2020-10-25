#pragma once

#define DECLARE_ENUMERATE_FUNCTION_SIGNATURE(type)                             \
  typedef void (*type##_enumerate_function_sig)(const int, const type);

#define DECLARE_ENUMERATE(type)                                                \
  DECLARE_ENUMERATE_FUNCTION_SIGNATURE(type)                                   \
  void enumerate_##type(                                                       \
    const type* arr, const int size, const type##_enumerate_function_sig f)    \
  {                                                                            \
    for (int index = 0; index != size; index++) {                              \
      f(index, *(arr + index));                                                \
    }                                                                          \
  }

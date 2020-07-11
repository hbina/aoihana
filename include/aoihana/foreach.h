#pragma once

#define DECLARE_FOREACH_FUNCTION_SIGNATURE(type)                               \
  typedef void (*type##_foreach_function_sig)(const type);

#define DECLARE_FOREACH(type)                                                  \
  DECLARE_FOREACH_FUNCTION_SIGNATURE(type)                                     \
  void foreach_##type(                                                         \
    const type* arr, const int size, const type##_foreach_function_sig f)      \
  {                                                                            \
    for (int index = 0; index != size; index++) {                              \
      f(*(arr + index));                                                       \
    }                                                                          \
  }


#ifndef AOIHANA_H
#define AOIHANA_H

#include <stdio.h>
#include <stdlib.h>

#define FOLD_BINARY_OPERATIONS(type) \
  typedef type (*type##_fold_function_sig)(const type, const type);

#define FOLD(type)                                                 \
  FOLD_BINARY_OPERATIONS(type)                                     \
  int fold_##type(const type *arr, const int size, const int init, \
                  const type##_fold_function_sig f)                \
  {                                                                \
    int acc = init;                                                \
    int index = 0;                                                 \
    while (index != size)                                          \
    {                                                              \
      acc = f(acc, *(arr + index));                                \
      index = index + 1;                                           \
    }                                                              \
    return acc;                                                    \
  }

#define FOREACH_BINARY_OPERATIONS(type) \
  typedef void (*type##_foreach_function_sig)(const type);

#define FOREACH(type)                                              \
  FOREACH_BINARY_OPERATIONS(type)                                  \
  int fold_##type(const type *arr, const int size, const int init, \
                  const type##_foreach_function_sig f)             \
  {                                                                \
    int acc = init;                                                \
    int index = 0;                                                 \
    while (index != size)                                          \
    {                                                              \
      acc = f(acc, *(arr + index));                                \
      index = index + 1;                                           \
    }                                                              \
    return acc;                                                    \
  }

#define VEC_FOLD_BINARY_OPERATIONS(type) \
  typedef type (*vec_##type##_fold_function_sig)(type, type);

#define VEC(type)                                                          \
  typedef struct Vec_##type##_                                             \
  {                                                                        \
    type *ptr;                                                             \
    int len;                                                               \
    int capacity;                                                          \
  } Vec_##type;                                                            \
  Vec_##type vec_##type##_new()                                            \
  {                                                                        \
    Vec_##type vec;                                                        \
    vec.ptr = (type *)malloc(1 * sizeof(type));                            \
    vec.len = 0;                                                           \
    vec.capacity = 1;                                                      \
    return vec;                                                            \
  }                                                                        \
  Vec_##type vec_##type##_with_capacity(const int capacity)                \
  {                                                                        \
    Vec_##type vec;                                                        \
    vec.ptr = (type *)malloc(capacity * sizeof(type));                     \
    vec.len = 0;                                                           \
    vec.capacity = capacity;                                               \
    return vec;                                                            \
  }                                                                        \
  void vec_##type##_push_back(Vec_##type *vec, const type x)               \
  {                                                                        \
    if (vec->len == vec->capacity)                                         \
    {                                                                      \
      int new_cap = vec->capacity * 2 + 1;                                 \
      type *new_array = (type *)realloc(vec->ptr, new_cap * sizeof(type)); \
      vec->ptr = new_array;                                                \
      vec->capacity = new_cap;                                             \
    }                                                                      \
    vec->ptr[vec->len] = x;                                                \
    vec->len = vec->len + 1;                                               \
  }                                                                        \
  void vec_##type##_destroy(Vec_##type *vec)                               \
  {                                                                        \
    free(vec->ptr);                                                        \
    vec->ptr = NULL;                                                       \
    vec->len = 0;                                                          \
  }                                                                        \
  VEC_FOLD_BINARY_OPERATIONS(type);                                        \
  type vec_##type##_fold(Vec_##type *vec, const type init,                 \
                         vec_##type##_fold_function_sig f)                 \
  {                                                                        \
    type acc = init;                                                       \
    for (int index = 0; index != vec->len; index++)                        \
    {                                                                      \
      acc = f(acc, *(vec->ptr + index));                                   \
    }                                                                      \
    return acc;                                                            \
  }                                                                        \
  type vec_##type##_at(Vec_##type *vec, const int index)                   \
  {                                                                        \
    return *(vec->ptr + index);                                            \
  }

#define ARITHMETIC_OPERATIONS(type)                    \
  type plus_##type(const type lhs, const type rhs)     \
  {                                                    \
    return lhs + rhs;                                  \
  }                                                    \
  type minus_##type(const type lhs, const type rhs)    \
  {                                                    \
    return lhs - rhs;                                  \
  }                                                    \
  type multiply_##type(const type lhs, const type rhs) \
  {                                                    \
    return lhs * rhs;                                  \
  }                                                    \
  type divide_##type(const type lhs, const type rhs)   \
  {                                                    \
    return lhs / rhs;                                  \
  }

#define IMPLEMENT_FOR_TYPE(type) \
  ARITHMETIC_OPERATIONS(type);   \
  FOLD(type);                    \
  VEC(type);

IMPLEMENT_FOR_TYPE(char);
IMPLEMENT_FOR_TYPE(int);
IMPLEMENT_FOR_TYPE(float);
IMPLEMENT_FOR_TYPE(double);

#endif

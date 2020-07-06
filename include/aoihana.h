#ifndef AOIHANA_H
#define AOIHANA_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define DEFINE_FOLD_FUNCTION_SIGNATURE(type) \
  typedef type (*type##_fold_function_sig)(const type, const type);

#define DEFINE_FOLD(type)                                          \
  DEFINE_FOLD_FUNCTION_SIGNATURE(type)                             \
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

#define DEFINE_FOREACH_FUNCTION_SIGNATURE(type) \
  typedef void (*type##_foreach_function_sig)(const type);

#define DEFINE_FOREACH(type)                                       \
  DEFINE_FOREACH_FUNCTION_SIGNATURE(type)                          \
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

#define DEFINE_VEC_FOLD_FUNCTION_SIGNATURE(type) \
  typedef type (*vec_##type##_fold_function_sig)(type, type);

#define DEFINE_VEC_RESULT_TYPE(type)                                \
  typedef struct Vec_Result_##type##_                               \
  {                                                                 \
    bool success;                                                   \
    type value;                                                     \
  } Vec_Result_##type;                                              \
  Vec_Result_##type vec_##type##_result_create_ok(const type value) \
  {                                                                 \
    Vec_Result_##type result;                                       \
    result.success = true;                                          \
    result.value = value;                                           \
    return result;                                                  \
  }                                                                 \
  Vec_Result_##type vec_##type##_result_create_error()              \
  {                                                                 \
    Vec_Result_##type result;                                       \
    result.success = false;                                          \
    /*result.value = value; // what should be here? */              \
    return result;                                                  \
  }

#define DEFINE_VEC(type)                                                   \
  DEFINE_VEC_RESULT_TYPE(type)                                             \
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
  DEFINE_VEC_FOLD_FUNCTION_SIGNATURE(type);                                \
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
  Vec_Result_##type vec_##type##_at(Vec_##type *vec, const int index)      \
  {                                                                        \
    if (index < vec->len)                                                  \
    {                                                                      \
      return vec_##type##_result_create_ok(*(vec->ptr + index));           \
    }                                                                      \
    else                                                                   \
    {                                                                      \
      return vec_##type##_result_create_error();                           \
    }                                                                      \
  }

#define DEFINE_ARITHMETIC_OPERATIONS(type)             \
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

#define IMPLEMENT_FOR_TYPE(type)      \
  DEFINE_ARITHMETIC_OPERATIONS(type); \
  DEFINE_FOLD(type);                  \
  DEFINE_VEC(type);

IMPLEMENT_FOR_TYPE(char);
IMPLEMENT_FOR_TYPE(int);
IMPLEMENT_FOR_TYPE(float);
IMPLEMENT_FOR_TYPE(double);

#endif

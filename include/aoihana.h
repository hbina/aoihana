#ifndef AOIHANA_H
#define AOIHANA_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define DECLARE_FOLD_FUNCTION_SIGNATURE(type) \
  typedef type (*type##_fold_function_sig)(const type, const type);

#define DECLARE_FOLD(type)                                         \
  DECLARE_FOLD_FUNCTION_SIGNATURE(type)                            \
  int fold_##type(const type *arr, const int size, const int init, \
                  const type##_fold_function_sig f)                \
  {                                                                \
    int acc = init;                                                \
    for (int index = 0; index != size; index++)                    \
    {                                                              \
      acc = f(acc, *(arr + index));                                \
    }                                                              \
    return acc;                                                    \
  }

#define DECLARE_FOREACH_FUNCTION_SIGNATURE(type) \
  typedef void (*type##_foreach_function_sig)(const type);

#define DECLARE_FOREACH(type)                          \
  DECLARE_FOREACH_FUNCTION_SIGNATURE(type)             \
  int fold_##type(const type *arr, const int size,     \
                  const type##_foreach_function_sig f) \
  {                                                    \
    for (int index = 0; index != size; index++)        \
    {                                                  \
      f(acc, *(arr + index));                          \
    }                                                  \
    return acc;                                        \
  }

#define DECLARE_VEC_FOLD_FUNCTION_SIGNATURE(type) \
  typedef type (*vec_##type##_fold_function_sig)(type, type);

#define DECLARE_VEC_IOTA_FUNCTION_SIGNATURE(type) \
  typedef type (*vec_##type##_iota_function_sig)(type);

#define DECLARE_VEC_RESULT_TYPE(type)                        \
  typedef struct Vec_Result_##type##_                        \
  {                                                          \
    bool success;                                            \
    type *ptr;                                               \
  } Vec_Result_##type;                                       \
  Vec_Result_##type vec_##type##_result_create_ok(type *ptr) \
  {                                                          \
    Vec_Result_##type result;                                \
    result.success = true;                                   \
    result.ptr = ptr;                                        \
    return result;                                           \
  }                                                          \
  Vec_Result_##type vec_##type##_result_create_error()       \
  {                                                          \
    Vec_Result_##type result;                                \
    result.success = false;                                  \
    result.ptr = NULL;                                       \
    return result;                                           \
  }

#define DECLARE_VEC(type)                                                   \
  DECLARE_VEC_RESULT_TYPE(type)                                             \
  typedef struct Vec_##type##_                                              \
  {                                                                         \
    type *ptr;                                                              \
    int len;                                                                \
    int capacity;                                                           \
  } Vec_##type;                                                             \
  void vec_##type##_push_back(Vec_##type *vec, const type x);               \
  /** Everything below this is actually the definition.*/                   \
  Vec_##type vec_##type##_new()                                             \
  {                                                                         \
    Vec_##type vec;                                                         \
    vec.ptr = (type *)malloc(1 * sizeof(type));                             \
    vec.len = 0;                                                            \
    vec.capacity = 1;                                                       \
    return vec;                                                             \
  }                                                                         \
  Vec_##type vec_##type##_with_capacity(const int capacity)                 \
  {                                                                         \
    Vec_##type vec;                                                         \
    vec.ptr = (type *)malloc(capacity * sizeof(type));                      \
    vec.len = 0;                                                            \
    vec.capacity = capacity;                                                \
    return vec;                                                             \
  }                                                                         \
  DECLARE_VEC_IOTA_FUNCTION_SIGNATURE(type);                                \
  Vec_##type vec_##type##_with_iota(const int capacity, const type init,    \
                                    const vec_##type##_iota_function_sig f) \
  {                                                                         \
    Vec_##type vec;                                                         \
    vec.ptr = (type *)malloc(capacity * sizeof(type));                      \
    vec.len = 0;                                                            \
    vec.capacity = capacity;                                                \
    type iota = init;                                                       \
    for (int index = 0; index != capacity; index++)                         \
    {                                                                       \
      vec_##type##_push_back(&vec, iota);                                   \
      iota = f(iota);                                                       \
    }                                                                       \
    return vec;                                                             \
  }                                                                         \
  void vec_##type##_push_back(Vec_##type *vec, const type x)                \
  {                                                                         \
    if (vec->len == vec->capacity)                                          \
    {                                                                       \
      int new_cap = vec->capacity * 2 + 1;                                  \
      type *new_array = (type *)realloc(vec->ptr, new_cap * sizeof(type));  \
      vec->ptr = new_array;                                                 \
      vec->capacity = new_cap;                                              \
    }                                                                       \
    vec->ptr[vec->len] = x;                                                 \
    vec->len = vec->len + 1;                                                \
  }                                                                         \
  void vec_##type##_destroy(Vec_##type *vec)                                \
  {                                                                         \
    free(vec->ptr);                                                         \
    vec->ptr = NULL;                                                        \
    vec->len = 0;                                                           \
  }                                                                         \
  DECLARE_VEC_FOLD_FUNCTION_SIGNATURE(type);                                \
  type vec_##type##_fold(Vec_##type *vec, const type init,                  \
                         vec_##type##_fold_function_sig f)                  \
  {                                                                         \
    return fold_##type(vec->ptr, vec->len, init, f);                        \
  }                                                                         \
  const Vec_Result_##type vec_##type##_at(Vec_##type *vec, const int index) \
  {                                                                         \
    if (index >= 0 && index < vec->len)                                     \
    {                                                                       \
      return vec_##type##_result_create_ok((vec->ptr + index));             \
    }                                                                       \
    else                                                                    \
    {                                                                       \
      return vec_##type##_result_create_error();                            \
    }                                                                       \
  }

/// Overflow check?
#define DECLARE_INTEGER_OPERATIONS(type)    \
  type successor_##type(const type value)   \
  {                                         \
    return value + 1;                       \
  }                                         \
  type predecessor_##type(const type value) \
  {                                         \
    return value - 1;                       \
  }

#define DECLARE_ARITHMETIC_OPERATIONS(type)            \
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

#define IMPLEMENT_FOR_TYPE(type)       \
  DECLARE_INTEGER_OPERATIONS(type);    \
  DECLARE_ARITHMETIC_OPERATIONS(type); \
  DECLARE_FOLD(type);                  \
  DECLARE_VEC(type);

IMPLEMENT_FOR_TYPE(char);
IMPLEMENT_FOR_TYPE(int);
IMPLEMENT_FOR_TYPE(float);
IMPLEMENT_FOR_TYPE(double);

#endif

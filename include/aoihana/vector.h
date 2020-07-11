#pragma once

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "quicksort.h"
#include "result.h"

#define DECLARE_VEC_IOTA_FUNCTION_SIGNATURE(type)                              \
  typedef type (*vec_##type##_iota_function_sig)(const type);

#define DECLARE_VEC_APPLY_FUNCTION_SIGNATURE(type)                             \
  typedef type (*vec_##type##_apply_function_sig)(const type);

#define DECLARE_VEC_FOLD_FUNCTION_SIGNATURE(type)                              \
  typedef type (*vec_##type##_fold_function_sig)(const type, const type);

#define DECLARE_VEC(type)                                                      \
  typedef struct Vec_##type##_                                                 \
  {                                                                            \
    type* ptr;                                                                 \
    int len;                                                                   \
    int capacity;                                                              \
  } Vec_##type;                                                                \
  void vec_##type##_push_back(Vec_##type* vec, const type x);                  \
  /** Everything below this is actually the definition.*/                      \
  Vec_##type vec_##type##_new()                                                \
  {                                                                            \
    Vec_##type vec;                                                            \
    vec.ptr = (type*)malloc(1 * sizeof(type));                                 \
    vec.len = 0;                                                               \
    vec.capacity = 1;                                                          \
    return vec;                                                                \
  }                                                                            \
  Vec_##type vec_##type##_with_capacity(const int capacity)                    \
  {                                                                            \
    Vec_##type vec;                                                            \
    vec.ptr = (type*)malloc(capacity * sizeof(type));                          \
    vec.len = 0;                                                               \
    vec.capacity = capacity;                                                   \
    return vec;                                                                \
  }                                                                            \
  DECLARE_VEC_IOTA_FUNCTION_SIGNATURE(type);                                   \
  Vec_##type vec_##type##_with_iota(const int capacity,                        \
                                    const type init,                           \
                                    const vec_##type##_iota_function_sig f)    \
  {                                                                            \
    Vec_##type vec;                                                            \
    vec.ptr = (type*)malloc(capacity * sizeof(type));                          \
    vec.len = 0;                                                               \
    vec.capacity = capacity;                                                   \
    type iota = init;                                                          \
    for (int index = 0; index != capacity; index++) {                          \
      vec_##type##_push_back(&vec, iota);                                      \
      iota = f(iota);                                                          \
    }                                                                          \
    return vec;                                                                \
  }                                                                            \
  Vec_##type vec_##type##_with_default(const int capacity,                     \
                                       const type default_value)               \
  {                                                                            \
    Vec_##type vec;                                                            \
    vec.ptr = (type*)malloc(capacity * sizeof(type));                          \
    vec.len = 0;                                                               \
    vec.capacity = capacity;                                                   \
    for (int index = 0; index != capacity; index++) {                          \
      vec_##type##_push_back(&vec, default_value);                             \
    }                                                                          \
    return vec;                                                                \
  }                                                                            \
  Vec_##type vec_##type##_from(type* ptr, const int len)                       \
  {                                                                            \
    Vec_##type vec;                                                            \
    vec.ptr = ptr;                                                             \
    vec.len = len;                                                             \
    vec.capacity = len;                                                        \
    return vec;                                                                \
  }                                                                            \
  void vec_##type##_push_back(Vec_##type* const vec, const type x)             \
  {                                                                            \
    if (vec->len == vec->capacity) {                                           \
      int new_cap = vec->capacity * 2 + 1;                                     \
      type* new_array = (type*)realloc(vec->ptr, new_cap * sizeof(type));      \
      vec->ptr = new_array;                                                    \
      vec->capacity = new_cap;                                                 \
    }                                                                          \
    vec->ptr[vec->len] = x;                                                    \
    vec->len = vec->len + 1;                                                   \
  }                                                                            \
  void vec_##type##_destroy(Vec_##type* vec)                                   \
  {                                                                            \
    free(vec->ptr);                                                            \
    vec->ptr = NULL;                                                           \
    vec->len = 0;                                                              \
  }                                                                            \
  DECLARE_RESULT_TYPE_REF(type);                                               \
  const ResultRef_##type vec_##type##_at(const Vec_##type const vec,           \
                                         const int index)                      \
  {                                                                            \
    if (index >= 0 && index < vec.len) {                                       \
      return resultref_##type##_create_ok(vec.ptr + index);                    \
    } else {                                                                   \
      return resultref_##type##_create_error();                                \
    }                                                                          \
  }                                                                            \
  const bool vec_##type##_remove(Vec_##type* const vec, const int index)       \
  {                                                                            \
    if (index >= 0 && index < vec->len) {                                      \
      memmove(vec->ptr + index,                                                \
              vec->ptr + index + 1,                                            \
              (vec->len - index - 1) * sizeof(type));                          \
      vec->len = vec->len - 1;                                                 \
      return true;                                                             \
    } else {                                                                   \
      return false;                                                            \
    }                                                                          \
  }                                                                            \
  void vec_##type##_clear(Vec_##type* const vec) { vec->len = 0; }             \
  DECLARE_VEC_APPLY_FUNCTION_SIGNATURE(type)                                   \
  bool vec_##type##_apply_if_exist(                                            \
    Vec_##type vec, const int index, vec_##type##_apply_function_sig f)        \
  {                                                                            \
    ResultRef_##type result = vec_##type##_at(vec, index);                     \
    if (result.success) {                                                      \
      *result.ptr = f(*result.ptr);                                            \
      return true;                                                             \
    } else {                                                                   \
      return false;                                                            \
    }                                                                          \
  }                                                                            \
  DECLARE_VEC_FOLD_FUNCTION_SIGNATURE(type);                                   \
  const type vec_##type##_fold(                                                \
    Vec_##type const vec, const type init, vec_##type##_fold_function_sig f)   \
  {                                                                            \
    type acc = init;                                                           \
    for (int index = 0; index != vec.len; index++) {                           \
      acc = f(acc, *(vec.ptr + index));                                        \
    }                                                                          \
    return acc;                                                                \
  }

#define DECLARE_VEC_SORTABLE(type)                                             \
  DECLARE_QUICKSORT_PREDICATE_FUNCTION_SIGNATURE(type);                        \
  DECLARE_QUICKSORT(type);                                                     \
  void vec_##type##_sort(Vec_##type vec,                                       \
                         const quicksort_##type##_function_sig f)              \
  {                                                                            \
    quicksort_##type(vec.ptr, 0, vec.len - 1, f);                              \
  }

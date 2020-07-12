#pragma once

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "quicksort.h"
#include "result.h"

#define DECLARE_VEC_IOTA_FUNCTION_SIGNATURE(type, name)                        \
  typedef type (*name##_iota_function_sig)(const type);

#define DECLARE_VEC_APPLY_FUNCTION_SIGNATURE(type, name)                       \
  typedef type (*name##_apply_function_sig)(const type);

#define DECLARE_VEC_FOLD_FUNCTION_SIGNATURE(type, name)                        \
  typedef type (*name##_fold_function_sig)(const type, const type);

#define DECLARE_VEC_FIND_FUNCTION_SIGNATURE(type, name)                        \
  typedef bool (*name##_find_function_sig)(const type);

#define DECLARE_VEC_INTERNAL(type, name)                                       \
  typedef struct name##_                                                       \
  {                                                                            \
    type* ptr;                                                                 \
    int len;                                                                   \
    int capacity;                                                              \
  } name;                                                                      \
  void name##_push_back(name* vec, const type x);                              \
  /** Everything below this is actually the definition.*/                      \
  name name##_new()                                                            \
  {                                                                            \
    name vec;                                                                  \
    vec.ptr = (type*)malloc(1 * sizeof(type));                                 \
    vec.len = 0;                                                               \
    vec.capacity = 1;                                                          \
    return vec;                                                                \
  }                                                                            \
  name name##_with_capacity(const int capacity)                                \
  {                                                                            \
    name vec;                                                                  \
    vec.ptr = (type*)malloc(capacity * sizeof(type));                          \
    vec.len = 0;                                                               \
    vec.capacity = capacity;                                                   \
    return vec;                                                                \
  }                                                                            \
  DECLARE_VEC_IOTA_FUNCTION_SIGNATURE(type, name);                             \
  name name##_with_iota(                                                       \
    const int capacity, const type init, const name##_iota_function_sig f)     \
  {                                                                            \
    name vec;                                                                  \
    vec.ptr = (type*)malloc(capacity * sizeof(type));                          \
    vec.len = 0;                                                               \
    vec.capacity = capacity;                                                   \
    type iota = init;                                                          \
    for (int index = 0; index != capacity; index++) {                          \
      name##_push_back(&vec, iota);                                            \
      iota = f(iota);                                                          \
    }                                                                          \
    return vec;                                                                \
  }                                                                            \
  name name##_with_default(const int capacity, const type default_value)       \
  {                                                                            \
    name vec;                                                                  \
    vec.ptr = (type*)malloc(capacity * sizeof(type));                          \
    vec.len = 0;                                                               \
    vec.capacity = capacity;                                                   \
    for (int index = 0; index != capacity; index++) {                          \
      name##_push_back(&vec, default_value);                                   \
    }                                                                          \
    return vec;                                                                \
  }                                                                            \
  name name##_from(type* ptr, const int len)                                   \
  {                                                                            \
    name vec;                                                                  \
    vec.ptr = ptr;                                                             \
    vec.len = len;                                                             \
    vec.capacity = len;                                                        \
    return vec;                                                                \
  }                                                                            \
  void name##_push_back(name* const vec, const type x)                         \
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
  void name##_destroy(name* vec)                                               \
  {                                                                            \
    free(vec->ptr);                                                            \
    vec->ptr = NULL;                                                           \
    vec->len = 0;                                                              \
  }                                                                            \
  DECLARE_RESULT_TYPE_REF(type);                                               \
  const ResultRef_##type name##_at(const name const vec, const int index)      \
  {                                                                            \
    if (index >= 0 && index < vec.len) {                                       \
      return resultref_##type##_create_ok(vec.ptr + index);                    \
    } else {                                                                   \
      return resultref_##type##_create_error();                                \
    }                                                                          \
  }                                                                            \
  const bool name##_remove(name* const vec, const int index)                   \
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
  void name##_clear(name* const vec) { vec->len = 0; }                         \
  DECLARE_VEC_APPLY_FUNCTION_SIGNATURE(type, name);                            \
  bool name##_apply_if_exist(                                                  \
    name vec, const int index, name##_apply_function_sig f)                    \
  {                                                                            \
    ResultRef_##type result = name##_at(vec, index);                           \
    if (result.success) {                                                      \
      *result.ptr = f(*result.ptr);                                            \
      return true;                                                             \
    } else {                                                                   \
      return false;                                                            \
    }                                                                          \
  }                                                                            \
  DECLARE_VEC_FOLD_FUNCTION_SIGNATURE(type, name);                             \
  const type name##_fold(                                                      \
    name const vec, const type init, name##_fold_function_sig f)               \
  {                                                                            \
    type acc = init;                                                           \
    for (int index = 0; index != vec.len; index++) {                           \
      acc = f(acc, *(vec.ptr + index));                                        \
    }                                                                          \
    return acc;                                                                \
  }                                                                            \
  DECLARE_VEC_FIND_FUNCTION_SIGNATURE(type, name);                             \
  const ResultRef_##type name##_find(name* const vec,                          \
                                     name##_find_function_sig f)               \
  {                                                                            \
    for (int index = 0; index != vec->len; index++) {                          \
      if (f(*(vec->ptr + index))) {                                            \
        return resultref_##type##_create_ok(vec->ptr + index);                 \
      }                                                                        \
    }                                                                          \
    return resultref_##type##_create_error();                                  \
  }                                                                            \
  DECLARE_QUICKSORT_PREDICATE_FUNCTION_SIGNATURE(type);                        \
  DECLARE_QUICKSORT(type);                                                     \
  void name##_sort(name vec, const quicksort_##type##_function_sig f)          \
  {                                                                            \
    quicksort_##type(vec.ptr, 0, vec.len - 1, f);                              \
  }

#define DECLARE_VEC_NAME(type, name) DECLARE_VEC_INTERNAL(type, name)
#define DECLARE_VEC(type) DECLARE_VEC_INTERNAL(type, Vec_##type)

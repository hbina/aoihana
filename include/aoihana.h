#ifndef AOIHANA_H
#define AOIHANA_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DECLARE_QUICKSORT_PREDICATE_FUNCTION_SIGNATURE(type)                   \
  typedef bool (*quicksort_##type##_function_sig)(const type, const type);

#define DECLARE_QUICKSORT_SWAP(type)                                           \
  void quicksort_##type##_swap(type* lhs, type* rhs)                           \
  {                                                                            \
    const type tmp = *lhs;                                                     \
    *lhs = *rhs;                                                               \
    *rhs = tmp;                                                                \
  }

#define DECLARE_QUICKSORT(type)                                                \
  DECLARE_QUICKSORT_SWAP(type);                                                \
  int quicksort_##type##_partition(type* const ptr,                            \
                                   const int lo,                               \
                                   const int hi,                               \
                                   const quicksort_##type##_function_sig f)    \
  {                                                                            \
    const type pivot = *(ptr + hi);                                            \
    int i = lo;                                                                \
    for (int j = lo; j != hi; j++) {                                           \
      if (f(*(ptr + j), pivot)) {                                              \
        quicksort_##type##_swap(ptr + i, ptr + j);                             \
        i = i + 1;                                                             \
      }                                                                        \
    }                                                                          \
    quicksort_##type##_swap(ptr + i, ptr + hi);                                \
    return i;                                                                  \
  }                                                                            \
  void quicksort_##type(type* const ptr,                                       \
                        const int lo,                                          \
                        const int hi,                                          \
                        const quicksort_##type##_function_sig f)               \
  {                                                                            \
    if (lo < hi) {                                                             \
      int p = quicksort_##type##_partition(ptr, lo, hi, f);                    \
      quicksort_##type(ptr, lo, p - 1, f);                                     \
      quicksort_##type(ptr, p + 1, hi, f);                                     \
    }                                                                          \
  }

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

#define DECLARE_VEC_IOTA_FUNCTION_SIGNATURE(type)                              \
  typedef type (*vec_##type##_iota_function_sig)(type);

#define DECLARE_VEC_APPLY_FUNCTION_SIGNATURE(type)                             \
  typedef type (*vec_##type##_apply_function_sig)(type);

#define DECLARE_VEC_RESULT_TYPE(type)                                          \
  typedef struct Vec_Result_##type##_                                          \
  {                                                                            \
    bool success;                                                              \
    type* ptr;                                                                 \
  } Vec_Result_##type;                                                         \
  Vec_Result_##type vec_##type##_result_create_ok(type* ptr)                   \
  {                                                                            \
    Vec_Result_##type result;                                                  \
    result.success = true;                                                     \
    result.ptr = ptr;                                                          \
    return result;                                                             \
  }                                                                            \
  Vec_Result_##type vec_##type##_result_create_error()                         \
  {                                                                            \
    Vec_Result_##type result;                                                  \
    result.success = false;                                                    \
    result.ptr = NULL;                                                         \
    return result;                                                             \
  }

#define DECLARE_RESULT_TYPE(type)                                              \
  typedef struct Result_##type##_                                              \
  {                                                                            \
    bool success;                                                              \
    type value;                                                                \
  } Result_##type;                                                             \
  Result_##type result_##type##_create_ok(const type value)                    \
  {                                                                            \
    Result_##type result;                                                      \
    result.success = true;                                                     \
    result.value = value;                                                      \
    return result;                                                             \
  }                                                                            \
  Result_##type result_##type##_create_error()                                 \
  {                                                                            \
    Result_##type result;                                                      \
    result.success = false;                                                    \
    result.value; /* FIXME: Currently, access is undefined...*/                \
    return result;                                                             \
  }

#define DECLARE_VEC(type)                                                      \
  DECLARE_VEC_RESULT_TYPE(type)                                                \
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
  void vec_##type##_push_back(Vec_##type* vec, const type x)                   \
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
  const Vec_Result_##type vec_##type##_at(const Vec_##type* const vec,         \
                                          const int index)                     \
  {                                                                            \
    if (index >= 0 && index < vec->len) {                                      \
      return vec_##type##_result_create_ok(vec->ptr + index);                  \
    } else {                                                                   \
      return vec_##type##_result_create_error();                               \
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
    Vec_##type* vec, const int index, vec_##type##_apply_function_sig f)       \
  {                                                                            \
    Vec_Result_##type result = vec_##type##_at(vec, index);                    \
    if (result.success) {                                                      \
      *result.ptr = f(*result.ptr);                                            \
      return true;                                                             \
    } else {                                                                   \
      return false;                                                            \
    }                                                                          \
  }                                                                            \
  DECLARE_QUICKSORT_PREDICATE_FUNCTION_SIGNATURE(type);                        \
  DECLARE_QUICKSORT(type);                                                     \
  void vec_##type##_sort(Vec_##type* vec,                                      \
                         const quicksort_##type##_function_sig f)              \
  {                                                                            \
    quicksort_##type(vec->ptr, 0, vec->len - 1, f);                            \
  }

#define DECLARE_VEC_FOLD_FUNCTION_SIGNATURE(type)                              \
  typedef type (*vec_##type##_fold_function_sig)(type, type);

#define DECLARE_VEC_HELPER_FOLD_FUNCTION(type)                                 \
  DECLARE_VEC_FOLD_FUNCTION_SIGNATURE(type);                                   \
  const type vec_##type##_fold(                                                \
    Vec_##type* const vec, const type init, vec_##type##_fold_function_sig f)  \
  {                                                                            \
    return fold_##type(vec->ptr, vec->len, init, f);                           \
  }

/// TODO: Overflow check?
#define DECLARE_INTEGER_OPERATIONS(type)                                       \
  type successor_##type(const type value) { return value + 1; }                \
  type predecessor_##type(const type value) { return value - 1; }

#define DECLARE_ARITHMETIC_OPERATIONS(type)                                    \
  type plus_##type(const type lhs, const type rhs) { return lhs + rhs; }       \
  type minus_##type(const type lhs, const type rhs) { return lhs - rhs; }      \
  type multiply_##type(const type lhs, const type rhs) { return lhs * rhs; }   \
  type divide_##type(const type lhs, const type rhs) { return lhs / rhs; }     \
  bool eq_##type(const type lhs, const type rhs) { return lhs == rhs; }        \
  bool neq_##type(const type lhs, const type rhs) { return lhs != rhs; }       \
  bool le_##type(const type lhs, const type rhs) { return lhs < rhs; }         \
  bool leq_##type(const type lhs, const type rhs) { return lhs <= rhs; }       \
  bool ge_##type(const type lhs, const type rhs) { return lhs > rhs; }         \
  bool geq_##type(const type lhs, const type rhs) { return lhs >= rhs; }

#define IMPLEMENT_FOR_TYPE(type)                                               \
  DECLARE_INTEGER_OPERATIONS(type);                                            \
  DECLARE_ARITHMETIC_OPERATIONS(type);                                         \
  DECLARE_FOLD(type);                                                          \
  DECLARE_VEC(type);                                                           \
  DECLARE_VEC_HELPER_FOLD_FUNCTION(type);                                      \
  DECLARE_ENUMERATE(type);

IMPLEMENT_FOR_TYPE(char);
IMPLEMENT_FOR_TYPE(int);
IMPLEMENT_FOR_TYPE(float);
IMPLEMENT_FOR_TYPE(double);

#endif

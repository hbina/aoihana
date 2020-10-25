#pragma once

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

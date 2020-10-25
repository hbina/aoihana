#pragma once

#include "result.h"

#define DECLARE_VIEW_FOLD_FUNCTION_SIGNATURE(type, name)                       \
  typedef type (*name##_fold_function_sig)(const type, const type);

#define DECLARE_VIEW_INTERNAL(type, name)                                      \
  typedef struct name##_                                                       \
  {                                                                            \
    const type* ptr;                                                           \
    int len;                                                                   \
  } name;                                                                      \
  /** Everything below this is actually the definition.*/                      \
  name name##_from(const type* const ptr, const int len)                       \
  {                                                                            \
    name view;                                                                 \
    view.ptr = ptr;                                                            \
    view.len = len;                                                            \
    return view;                                                               \
  }                                                                            \
  DECLARE_RESULT_TYPE_CONST_REF(type);                                         \
  const ResultConstRef_##type name##_at(const name const view,                 \
                                        const int index)                       \
  {                                                                            \
    if (index >= 0 && index < view.len) {                                      \
      return resultconstref_##type##_create_ok(view.ptr + index);              \
    } else {                                                                   \
      return resultconstref_##type##_create_error();                           \
    }                                                                          \
  }                                                                            \
  DECLARE_VIEW_FOLD_FUNCTION_SIGNATURE(type, name);                            \
  const type name##_fold(                                                      \
    name const view, const type init, name##_fold_function_sig f)              \
  {                                                                            \
    type acc = init;                                                           \
    for (int index = 0; index != view.len; index++) {                          \
      acc = f(acc, *(view.ptr + index));                                       \
    }                                                                          \
    return acc;                                                                \
  }

#define DECLARE_VIEW_NAME(type, name) DECLARE_VIEW_INTERNAL(type, name);
#define DECLARE_VIEW(type) DECLARE_VIEW_INTERNAL(type, View_##type)

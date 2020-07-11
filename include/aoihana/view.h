#pragma once

#include "result.h"

#define DECLARE_VIEW_FOLD_FUNCTION_SIGNATURE(type)                             \
  typedef type (*view_##type##_fold_function_sig)(const type, const type);

#define DECLARE_VIEW(type)                                                     \
  typedef struct View_##type##_                                                \
  {                                                                            \
    const type* ptr;                                                           \
    int len;                                                                   \
  } View_##type;                                                               \
  /** Everything below this is actually the definition.*/                      \
  View_##type view_##type##_from(const type* const ptr, const int len)         \
  {                                                                            \
    View_##type view;                                                          \
    view.ptr = ptr;                                                            \
    view.len = len;                                                            \
    return view;                                                               \
  }                                                                            \
  DECLARE_RESULT_TYPE_CONST_REF(type);                                         \
  const ResultConstRef_##type view_##type##_at(const View_##type* const view,  \
                                               const int index)                \
  {                                                                            \
    if (index >= 0 && index < view->len) {                                     \
      return resultconstref_##type##_create_ok(view->ptr + index);             \
    } else {                                                                   \
      return resultconstref_##type##_create_error();                           \
    }                                                                          \
  }                                                                            \
  DECLARE_VIEW_FOLD_FUNCTION_SIGNATURE(type);                                  \
  const type view_##type##_fold(View_##type* const view,                       \
                                const type init,                               \
                                view_##type##_fold_function_sig f)             \
  {                                                                            \
    type acc = init;                                                           \
    for (int index = 0; index != view->len; index++) {                         \
      acc = f(acc, *(view->ptr + index));                                      \
    }                                                                          \
    return acc;                                                                \
  }

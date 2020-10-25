#pragma once

#include <stdbool.h>
#include <stdlib.h>

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
    /*result.value;*/ /* FIXME: Currently, access is undefined...*/            \
    return result;                                                             \
  }

#define DECLARE_RESULT_TYPE_REF(type)                                          \
  typedef struct ResultRef_##type##_                                           \
  {                                                                            \
    bool success;                                                              \
    type* ptr;                                                                 \
  } ResultRef_##type;                                                          \
  ResultRef_##type resultref_##type##_create_ok(type* const ptr)               \
  {                                                                            \
    ResultRef_##type result;                                                   \
    result.success = true;                                                     \
    result.ptr = ptr;                                                          \
    return result;                                                             \
  }                                                                            \
  ResultRef_##type resultref_##type##_create_error()                           \
  {                                                                            \
    ResultRef_##type result;                                                   \
    result.success = false;                                                    \
    result.ptr = NULL;                                                         \
    return result;                                                             \
  }                                                                            \
  type resultref_##type##_unwrap(ResultRef_##type resultref)                   \
  {                                                                            \
    if (!resultref.success) {                                                  \
      abort(); /* TODO: Better abortion? */                                    \
    }                                                                          \
    return *resultref.ptr;                                                     \
  }

#define DECLARE_RESULT_TYPE_CONST_REF(type)                                    \
  typedef struct ResultConstRef_##type##_                                      \
  {                                                                            \
    bool success;                                                              \
    const type* ptr;                                                           \
  } ResultConstRef_##type;                                                     \
  ResultConstRef_##type resultconstref_##type##_create_ok(                     \
    const type* const ptr)                                                     \
  {                                                                            \
    ResultConstRef_##type result;                                              \
    result.success = true;                                                     \
    result.ptr = ptr;                                                          \
    return result;                                                             \
  }                                                                            \
  ResultConstRef_##type resultconstref_##type##_create_error()                 \
  {                                                                            \
    ResultConstRef_##type result;                                              \
    result.success = false;                                                    \
    result.ptr = NULL;                                                         \
    return result;                                                             \
  }

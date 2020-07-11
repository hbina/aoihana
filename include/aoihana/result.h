#pragma once

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
  }

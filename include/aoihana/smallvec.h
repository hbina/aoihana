#pragma once

#include <malloc.h>
#include <stdbool.h>
#include <string.h>

#define HANDLE_ERROR                                                           \
  do {                                                                         \
    printf("Error occured at file %s at line %du\n", __FILE__, __LINE__);      \
  } while (0)

#ifndef BOOL
#define BOOL char
#endif

#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE 1
#endif

typedef struct header
{
  int len;
  int cap;
} header;

typedef struct sv
{
  void* ptr;
} sv;

#define DEBUG_PRINT(name, self)                                                \
  printf("%s => sv cap:%d len:%d ptr:%p\n",                                    \
         name,                                                                 \
         sv_cap(self),                                                         \
         sv_len(self),                                                         \
         self.ptr)

#define sv_get_header(self) ((header*)self.ptr - 1)

#define sv_len(self) (sv_get_header(self)->len)

#define sv_setlen(self, new_len)                                               \
  do {                                                                         \
    sv_get_header(self)->len = new_len;                                        \
  } while (0);

#define sv_cap(self) (sv_get_header(self)->cap)

#define sv_setcap(self, new_cap)                                               \
  do {                                                                         \
    sv_get_header(self)->cap = new_cap;                                        \
  } while (0);

sv
new_sv()
{
  sv result;
  result.ptr = NULL;
  return result;
}

#define sv_free(self)                                                          \
  do {                                                                         \
    free((void*)sv_get_header(self));                                          \
    self.ptr = NULL;                                                           \
  } while (0);

#define sv_init(self, type, amount, result)                                    \
  bool result = false;                                                         \
  do {                                                                         \
    void* new_ptr = malloc(sizeof(header) + (sizeof(type) * amount));          \
    if (new_ptr == NULL) {                                                     \
      result = false;                                                          \
    } else {                                                                   \
      ((header*)new_ptr)->len = 0;                                             \
      ((header*)new_ptr)->cap = amount;                                        \
      void* arr_ptr = (void*)((header*)new_ptr + 1);                           \
      self.ptr = arr_ptr;                                                      \
      result = true;                                                           \
    }                                                                          \
  } while (0);

#define sv_reserve(self, type, new_cap, result)                                \
  bool result = false;                                                         \
  do {                                                                         \
    if (new_cap > sv_cap(self)) {                                              \
      void* new_ptr = malloc(sizeof(header) + (new_cap * sizeof(type)));       \
      if (new_ptr == NULL) { /* Must notify caller this failed */              \
        result = false;                                                        \
      } else {                                                                 \
        memcpy(new_ptr,                                                        \
               sv_get_header(self),                                            \
               sizeof(header) + (sv_cap(self) * sizeof(type)));                \
        ((header*)new_ptr)->cap = new_cap;                                     \
        void* arr_ptr = (void*)((header*)new_ptr + 1);                         \
        free(sv_get_header(self));                                             \
        self.ptr = arr_ptr;                                                    \
        result = true;                                                         \
      }                                                                        \
    } else {                                                                   \
      result = true;                                                           \
    }                                                                          \
  } while (0);

#define sv_reinit(self, type, result)                                          \
  bool result = false;                                                         \
  do {                                                                         \
    sv_reserve(self, type, sv_cap(self) * 2, result##reinit);                  \
    result = result##reinit;                                                   \
  } while (0);

#define sv_insert(self, type, value, index, result)                            \
  bool result = false;                                                         \
  do {                                                                         \
    if (self.ptr == NULL || index < 0 || sv_len(self) <= index) {              \
      result = false;                                                          \
    } else {                                                                   \
      if (sv_len(self) == sv_cap(self)) {                                      \
        sv_reinit(self, sizeof(type), result##insert);                         \
        result = result##insert;                                               \
      } else {                                                                 \
        result = true;                                                         \
      }                                                                        \
      if (result) {                                                            \
        memmove(self.ptr + index, self.ptr + index + 1, sv_len(self) - index); \
        *((type*)self.ptr + index) = value;                                    \
      }                                                                        \
    }                                                                          \
  } while (0);

#define sv_pushback(self, type, value, result)                                 \
  bool result = false;                                                         \
  do {                                                                         \
    if (self.ptr == NULL) {                                                    \
      sv_init(self, type, 2, result##pushback);                                \
      result = result##pushback;                                               \
    } else if (sv_cap(self) == sv_len(self)) {                                 \
      sv_reinit(self, type, result##pushback);                                 \
      result = result##pushback;                                               \
    } else {                                                                   \
      result = true;                                                           \
    }                                                                          \
    if (result) {                                                              \
      *((type*)self.ptr + sv_len(self)) = value;                               \
      sv_setlen(self, sv_len(self) + 1);                                       \
    }                                                                          \
  } while (0);

#define sv_get(self, type, index, result)                                      \
  int* result = NULL;                                                          \
  do {                                                                         \
    if (index >= sv_len(self)) {                                               \
      result = NULL;                                                           \
    } else {                                                                   \
      result = (type*)self.ptr + index;                                        \
    }                                                                          \
  } while (0);

#define sv_empty(self) (sv_len(self) == 0)

#define sv_clear(self)                                                         \
  do {                                                                         \
    sv_setlen(self, 0);                                                        \
  } while (0);

#define sv_fold(self, type, foldf, init, result)                               \
  type result = init;                                                          \
  do {                                                                         \
    for (int a = 0; a < sv_len(self); a++) {                                   \
      sv_get(self, type, a, result##fold_iter);                                \
      result = foldf(&result, result##fold_iter);                              \
    }                                                                          \
  } while (0);

#define sv_find(self, type, foldf, value, result)                              \
  type* result = NULL;                                                         \
  do {                                                                         \
    type tmp##value##find = value;                                             \
    for (int a = 0; a < sv_len(self); a++) {                                   \
      sv_get(self, type, a, result##find);                                     \
      if (foldf(&tmp##value##find, result##find)) {                                 \
        result = result##find;                                                 \
        break;                                                                 \
      }                                                                        \
    }                                                                          \
  } while (0);

#define sv_contain(self, type, value, result)                                  \
  bool result = false;                                                         \
  do {                                                                         \
    for (int a = 0; a < sv_len(self); a++) {                                   \
      sv_get(self, type, a, result##contain);                                  \
      if (*result##contain == value) {                                         \
        result = true;                                                         \
      }                                                                        \
    }                                                                          \
    result = false;                                                            \
  } while (0)

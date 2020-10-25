#pragma once

#include <malloc.h>
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

typedef struct
{
  int len;
  int cap;
} header;

typedef struct
{
  void* ptr;
} sv;

#define sv_len(self) ((((header*)self.ptr) - 1)->len)

#define sv_setlen(self, new_len)                                               \
  do {                                                                         \
    (((header*)self.ptr) - 1)->len = new_len;                                  \
  } while (0)

#define sv_cap(self) ((((header*)self.ptr) - 1)->cap)

#define sv_setcap(self, new_cap)                                               \
  do {                                                                         \
    (((header*)self.ptr) - 1)->cap = new_cap;                                  \
  } while (0)

sv
new_sv()
{
  sv result;
  result.ptr = NULL;
  return result;
}

#define sv_free(self)                                                          \
  do {                                                                         \
    free(((header*)self.ptr) - 1);                                             \
  } while (0)

#define sv_init(self, type, amount)                                            \
  do {                                                                         \
    void* new_ptr = malloc(sizeof(type) * amount + sizeof(header));            \
    if (new_ptr == NULL) {                                                     \
      HANDLE_ERROR;                                                            \
    } else {                                                                   \
      ((header*)new_ptr)->len = 0;                                             \
      ((header*)new_ptr)->cap = amount;                                        \
      void* arr_ptr = (void*)((header*)new_ptr + 1);                           \
      self.ptr = arr_ptr;                                                      \
    }                                                                          \
  } while (0)

#define sv_reserve(self, type, new_cap)                                        \
  do {                                                                         \
    void* new_ptr =                                                            \
      realloc((void*)((header*)self.ptr - 1), new_cap * sizeof(type));         \
    if (new_ptr == NULL) {                                                     \
      HANDLE_ERROR;                                                            \
    } else {                                                                   \
      ((header*)new_ptr)->len = sv_len(self);                                  \
      ((header*)new_ptr)->cap = new_cap;                                       \
      void* arr_ptr = (void*)((header*)new_ptr + 1);                           \
      sv_free(self);                                                           \
      self.ptr = arr_ptr;                                                      \
    }                                                                          \
  } while (0)

#define sv_reinit(self, type)                                                  \
  do {                                                                         \
    sv_reserve(self, type, sv_len(self) * 1.6);                                \
  } while (0)

#define sv_insert(self, type, value, index)                                    \
  do {                                                                         \
    if (self.ptr == NULL || index < 0 || sv_len(self) < index) {               \
      HANDLE_ERROR;                                                            \
    }                                                                          \
    if (sv_len(self) == sv_cap(self)) {                                        \
      sv_reinit(self, sizeof(type));                                           \
    }                                                                          \
    memmove(self.ptr + index, self.ptr + index + 1, sv_len(self) - index);     \
    *((type*)self.ptr + index) = value;                                        \
  } while (0)

#define sv_pushback(self, type, value)                                         \
  do {                                                                         \
    if (self.ptr == NULL) {                                                    \
      sv_init(self, type, 1);                                                  \
    }                                                                          \
    if (sv_cap(self) == sv_len(self)) {                                        \
      sv_reinit(self, type);                                                   \
    }                                                                          \
    *((type*)self.ptr + sv_len(self)) = value;                                 \
    sv_setlen(self, sv_len(self) + 1);                                         \
  } while (0)

#define sv_get(self, type, index)                                              \
  ((type*)((index >= sv_len(self)) ? NULL : self.ptr + index))

#define sv_empty(self) (sv_len(self) == 0)

#define sv_clear(self) (sv_setlen(self, 0))

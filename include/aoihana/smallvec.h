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
  } while (0)

#define sv_cap(self) (sv_get_header(self)->cap)

#define sv_setcap(self, new_cap)                                               \
  do {                                                                         \
    sv_get_header(self)->cap = new_cap;                                        \
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
    free((void*)sv_get_header(self));                                          \
    self.ptr = NULL;                                                           \
  } while (0)

#define sv_init(self, type, amount)                                            \
  do {                                                                         \
    void* new_ptr = malloc(sizeof(header) + (sizeof(type) * amount));          \
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
    if (new_cap > sv_cap(self)) {                                              \
      void* new_ptr = malloc(sizeof(header) + (new_cap * sizeof(type)));       \
      if (new_ptr == NULL) { /* Must notify caller this failed */              \
      } else {                                                                 \
        memcpy(new_ptr,                                                        \
               sv_get_header(self),                                            \
               sizeof(header) + (sv_cap(self) * sizeof(type)));                \
        ((header*)new_ptr)->cap = new_cap;                                     \
        void* arr_ptr = (void*)((header*)new_ptr + 1);                         \
        free(sv_get_header(self));                                             \
        self.ptr = arr_ptr;                                                    \
      }                                                                        \
    }                                                                          \
  } while (0)

#define sv_reinit(self, type)                                                  \
  do {                                                                         \
    sv_reserve(self, type, sv_cap(self) * 2);                                  \
  } while (0)

#define sv_insert(self, type, value, index)                                    \
  do {                                                                         \
    if (self.ptr == NULL || index < 0 || sv_len(self) <= index) {              \
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
      sv_init(self, type, 2);                                                  \
    }                                                                          \
    if (sv_cap(self) == sv_len(self)) {                                        \
      sv_reinit(self, type);                                                   \
    }                                                                          \
    *((type*)self.ptr + sv_len(self)) = value;                                 \
    sv_setlen(self, sv_len(self) + 1);                                         \
  } while (0)

#define sv_get(self, type, index, output)                                      \
  do {                                                                         \
    if (index >= sv_len(self)) {                                               \
      output = NULL;                                                           \
    } else {                                                                   \
      output = (type*)self.ptr + index;                                        \
    }                                                                          \
  } while (0)

#define sv_empty(self) (sv_len(self) == 0)

#define sv_clear(self)                                                         \
  do {                                                                         \
    sv_setlen(self, 0);                                                        \
  } while (0)

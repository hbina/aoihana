#include <assert.h>

#include "../include/aoihana/smallvec.h"

void
test_pushback_and_get()
{
  sv vec = new_sv();

  sv_pushback(vec, int, 0);
  int* ptr = NULL;
  sv_get(vec, int, 0, ptr);
  assert(*ptr == 0);

  sv_free(vec);
}

void
test_pushback_many_elements()
{
  sv vec = new_sv();

  for (int a = 0; a < 10; a++) {
    sv_pushback(vec, int, a);
  }

  for (int a = 0; a < 10; a++) {
    int* ptr = NULL;
    sv_get(vec, int, a, ptr);
    assert(*ptr == a);
  }

  sv_free(vec);
}

void
test_pushback_then_clear()
{
  sv vec = new_sv();

  for (int a = 0; a < 10; a++) {
    sv_pushback(vec, int, a);
  }

  sv_clear(vec);
  assert(sv_cap(vec) == 16);

  sv_free(vec);
}

void
test_insert_in_the_middle()
{
  sv vec = new_sv();

  for (int a = 0; a < 10; a++) {
    sv_pushback(vec, int, a);
  }

  sv_insert(vec, int, 100, 5);

  for (int a = 0; a < 5; a++) {
    int* ptr = NULL;
    sv_get(vec, int, a, ptr);
    assert(*ptr == a);
  }
  {
    int* ptr = NULL;
    sv_get(vec, int, 5, ptr);
    assert(*ptr == 100);
  }
  for (int a = 6; a < 11; a++) {
    int* ptr = NULL;
    sv_get(vec, int, a, ptr);
    assert(*ptr == a - 1);
  }

  sv_free(vec);
}

int
main(void)
{
  test_pushback_and_get();
  test_pushback_many_elements();
  test_pushback_then_clear();
}

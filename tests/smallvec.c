#include <assert.h>

#include "../include/aoihana/smallvec.h"

void
test_inserting_elements()
{
  sv vec = new_sv();

  sv_pushback(vec, int, 0);
  int* ptr = sv_get(vec, int, 0);
  assert(*ptr == 0);

  sv_free(vec);
}

int
main(void)
{
  test_inserting_elements();
}

#include <assert.h>

#include "../include/aoihana.h"

int main(int argc, char **argv)
{
    Vec_int vec = vec_int_with_capacity(30);
    for (int c = 0; c != 30; c++)
    {
        vec_int_push_back(&vec, c);
    }
    for (int c = 0; c != 30; c++)
    {
        assert(vec_int_at(&vec, c) == c);
    }
}

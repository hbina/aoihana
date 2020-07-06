#include "../../include/aoihana.h"

#include <stdlib.h>
#include <math.h>

typedef char *charPtr;

DECLARE_FOLD(charPtr);
DECLARE_VEC(charPtr);
DECLARE_FOREACH(charPtr);
DECLARE_ENUMERATE(charPtr);
DECLARE_RESULT_TYPE(int);

void print_value(const int index, char *const ptr)
{
    printf("index:%d value:%s\n", index, ptr);
}

Result_int parse_int(const char *const optarg)
{
    // TODO: Recalculate the actual `minval` and `maxval` that the algorithm can possibly handle.
    char *leftover_string = NULL;
    const int result = strtol(optarg, &leftover_string, 0);
    if (*leftover_string != '\0')
    {
        printf("Unable to convert the input \"%s\" to long and leftover string is \"%s\".\n", optarg, leftover_string);
        return result_int_create_error();
    }
    else
    {
        return result_int_create_ok(result);
    }
}

int main(int argc, char **argv)
{
    if (argc != 4)
    {
        printf("Aborting due to incorrect number of inputs. The program requires 3 integers.\n");
        return -1;
    }

    Vec_charPtr vec = vec_charPtr_from(argv, argc);
    enumerate_charPtr(vec.ptr, vec.len, print_value);

    Vec_Result_charPtr result_a = vec_charPtr_at(&vec, 1);
    Vec_Result_charPtr result_b = vec_charPtr_at(&vec, 2);
    Vec_Result_charPtr result_c = vec_charPtr_at(&vec, 3);

    if (result_a.success && result_b.success && result_c.success)
    {
        const Result_int a = parse_int(*result_a.ptr);
        const Result_int b = parse_int(*result_b.ptr);
        const Result_int c = parse_int(*result_c.ptr);

        if (a.success && b.success && c.success)
        {
            const double omega_n = sqrt(c.value / a.value);
            const double zeta = b.value / (2 * omega_n);

            printf("Obtained omega_n:%f zeta:%f\n", omega_n, zeta);
        }
        else
        {
            printf("Aborting due to parsing error.\n");
            return -1;
        }
    }
    else
    {
        printf("Aborting due to access violation with Vec_type. This is potentially a bug in the logic. Report to the developer.\n");
        return -1;
    }
}

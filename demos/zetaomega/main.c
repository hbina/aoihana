#include "../../include/aoihana.h"

#include <math.h>
#include <stdlib.h>

const float PI = 3.14159265359;

typedef char* charPtr;

DECLARE_FOLD(charPtr);
DECLARE_VEC(charPtr);
DECLARE_FOREACH(charPtr);
DECLARE_ENUMERATE(charPtr);
DECLARE_RESULT_TYPE(int);

void
print_value(const int index, char* ptr)
{
  printf("index:%d value:%s\n", index, ptr);
}

Result_int
parse_int(const char* const optarg)
{
  char* leftover_string = NULL;
  const int result = strtol(optarg, &leftover_string, 0);
  if (*leftover_string != '\0') {
    printf("Unable to convert the input \"%s\" to long and leftover string is "
           "\"%s\".\n",
           optarg,
           leftover_string);
    return result_int_create_error();
  } else {
    return result_int_create_ok(result);
  }
}

int
main(int argc, char** argv)
{
  if (argc != 4) {
    printf("Aborting due to incorrect number of inputs. The program requires 3 "
           "integers.\n");
    return -1;
  }

  /// TODO: This is more like const array isn't it? Its not like I can push into
  /// it anyways...
  const Vec_charPtr vec = vec_charPtr_from(argv, argc);
  enumerate_charPtr(vec.ptr, vec.len, print_value);

  const Vec_Result_charPtr result_a = vec_charPtr_at(&vec, 1);
  const Vec_Result_charPtr result_b = vec_charPtr_at(&vec, 2);
  const Vec_Result_charPtr result_c = vec_charPtr_at(&vec, 3);

  if (result_a.success && result_b.success && result_c.success) {
    const Result_int a = parse_int(*result_a.ptr);
    const Result_int b = parse_int(*result_b.ptr);
    const Result_int c = parse_int(*result_c.ptr);

    if (a.success && b.success && c.success) {
      const double omega_n = sqrt(c.value / a.value);
      const double zeta = b.value / (2 * omega_n);
      const double peak_time = PI / (omega_n * sqrt(1 - pow(zeta, 2)));
      const double rise_time =
        (1.76 * pow(zeta, 3) - 0.417 * pow(zeta, 2) + 1.039 * zeta + 1) /
        omega_n;
      const double overshoot_percentage =
        exp(-(zeta * PI) / (sqrt(1 - pow(zeta, 2)))) * 100;
      const double settling_time = 4 / (zeta * omega_n);
      printf("Obtained:\n\tomega_n:%f\n\tzeta:%f\n\tpeak_time:%f\n\trise_time:%"
             "f\n\tovershoot_percentage:%f\n\tsettling_time:%f\n",
             omega_n,
             zeta,
             peak_time,
             rise_time,
             overshoot_percentage,
             settling_time);
    } else {
      printf("Aborting due to parsing error.\n");
      return -1;
    }
  } else {
    printf("Aborting due to access violation with Vec_type. This is "
           "potentially a bug in the logic. Report to the developer.\n");
    return -1;
  }
}

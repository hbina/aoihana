#pragma once

#include "functional.h"
#include "vector.h"

DECLARE_VEC(float);
DECLARE_VEC(Vec_float);

typedef struct Map_int_float_mod_
{
  int bucket_size;
  Vec_Vec_float storage;
} Map_int_float_mod;
Map_int_float_mod
map_int_float_mod_new()
{
  Map_int_float_mod map;
  vec_Vec_float_push_back(&map.storage, vec_float_with_default(30, 0.0f));
  map.bucket_size = 3;
  return map;
}
bool
map_int_float_mod_insert(Map_int_float_mod* const map,
                         const int key,
                         const float value)
{
  const int index = mod_int(key, map->bucket_size);
  ResultRef_Vec_float bucket_ref = vec_Vec_float_at(map->storage, index);
  if (bucket_ref.success) {
    vec_float_push_back(bucket_ref.ptr, value);
    return true;
  } else {
    return false;
  }
}

DECLARE_BINARY_NUMBER_OPERATIONS(int);
DECLARE_MAP(int, int, mod_int);

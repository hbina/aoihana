#pragma once

#include <stdbool.h>

/// TODO: Overflow check?
#define DECLARE_UNARY_INTEGER_OPERATIONS(type)                                 \
  type successor_##type(const type value) { return value + 1; }                \
  type predecessor_##type(const type value) { return value - 1; }

#define DECLARE_BINARY_NUMBER_OPERATIONS(type)                                 \
  type plus_##type(const type lhs, const type rhs) { return lhs + rhs; }       \
  type minus_##type(const type lhs, const type rhs) { return lhs - rhs; }      \
  type multiply_##type(const type lhs, const type rhs) { return lhs * rhs; }   \
  type divide_##type(const type lhs, const type rhs) { return lhs / rhs; }     \
  type mod_##type(const type lhs, const type rhs) { return lhs % rhs; }        \
  bool eq_##type(const type lhs, const type rhs) { return lhs == rhs; }        \
  bool neq_##type(const type lhs, const type rhs) { return lhs != rhs; }       \
  bool le_##type(const type lhs, const type rhs) { return lhs < rhs; }         \
  bool leq_##type(const type lhs, const type rhs) { return lhs <= rhs; }       \
  bool ge_##type(const type lhs, const type rhs) { return lhs > rhs; }         \
  bool geq_##type(const type lhs, const type rhs) { return lhs >= rhs; }

#define DECLARE_ARITHMETIC_OPERATIONS(type)                                    \
  DECLARE_BINARY_NUMBER_OPERATIONS(type);                                      \
  DECLARE_UNARY_INTEGER_OPERATIONS(type);

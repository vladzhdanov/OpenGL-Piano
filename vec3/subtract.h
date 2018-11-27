#ifndef __VEC3_SUBTRACT
#define __VEC3_SUBTRACT

#include "type.h"
#include "set.h"

/**
 * Subtracts vector b from vector a
 *
 * @param {vec3} out the receiving vector
 * @param {vec3} a the first operand
 * @param {vec3} b the second operand
 * @returns {vec3} out
 */
vec3 vec3_subtract(vec3 out, vec3 a, vec3 b) {
  return vec3_set(out,
    a[0] - b[0],
    a[1] - b[1],
    a[2] - b[2]
  );
}

#endif

#ifndef __VEC3_INVERSE
#define __VEC3_INVERSE

#include "type.h"
#include "set.h"

/**
 * Returns the inverse of the components of a vec3
 *
 * @param {vec3} out the receiving vector
 * @param {vec3} a vector to invert
 * @returns {vec3} out
 */
vec3 vec3_inverse(vec3 out, vec3 a) {
  return vec3_set(out,
    1.0 / a[0],
    1.0 / a[1],
    1.0 / a[2]
  );
}

#endif

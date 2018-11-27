#ifndef __VEC3_COPY
#define __VEC3_COPY

#include "type.h"
#include "set.h"

/**
 * Copy the values from one vec3 to another
 *
 * @param {vec3} out the receiving vector
 * @param {vec3} a the source vector
 * @returns {vec3} out
 */
vec3 vec3_copy(vec3 out, vec3 a) {
  return vec3_set(out, a[0], a[1], a[2]);
}

#endif

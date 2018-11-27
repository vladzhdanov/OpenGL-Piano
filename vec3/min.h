#ifndef __VEC3_MIN
#define __VEC3_MIN

#include <math.h>
#include "set.h"
#include "type.h"

/**
 * Returns the minimum of two vec3's
 *
 * @param {vec3} out the receiving vector
 * @param {vec3} a the first operand
 * @param {vec3} b the second operand
 * @returns {vec3} out
 */
vec3 vec3_min(vec3 out, vec3 a, vec3 b) {
    return vec3_set(out,
      fmin(a[0], b[0]),
      fmin(a[1], b[1]),
      fmin(a[2], b[2])
    );
}

#endif

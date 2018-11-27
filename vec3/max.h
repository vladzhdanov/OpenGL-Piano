#ifndef __VEC3_MAX
#define __VEC3_MAX

#include <math.h>
#include "type.h"
#include "set.h"

/**
 * Returns the maximum of two vec3's
 *
 * @param {vec3} out the receiving vector
 * @param {vec3} a the first operand
 * @param {vec3} b the second operand
 * @returns {vec3} out
 */
vec3 vec3_max(vec3 out, vec3 a, vec3 b) {
    return vec3_set(out,
      fmax(a[0], b[0]),
      fmax(a[1], b[1]),
      fmax(a[2], b[2])
    );
}

#endif

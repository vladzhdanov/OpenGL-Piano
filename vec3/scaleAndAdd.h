#ifndef __VEC3_SCALEANDADD
#define __VEC3_SCALEANDADD

#include "type.h"
#include "set.h"

/**
 * Adds two vec3's after scaling the second operand by a scalar value
 *
 * @param {vec3} out the receiving vector
 * @param {vec3} a the first operand
 * @param {vec3} b the second operand
 * @param {Number} scale the amount to scale b by before adding
 * @returns {vec3} out
 */
vec3 vec3_scaleAndAdd(vec3 out, vec3 a, vec3 b, float scale) {
    return vec3_set(out,
      a[0] + (b[0] * scale),
      a[1] + (b[1] * scale),
      a[2] + (b[2] * scale)
    );
}

#endif

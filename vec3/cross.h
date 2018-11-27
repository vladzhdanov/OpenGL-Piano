#ifndef __VEC3_CROSS
#define __VEC3_CROSS

#include "type.h"
#include "set.h"

/**
 * Computes the cross product of two vec3's
 *
 * @param {vec3} out the receiving vector
 * @param {vec3} a the first operand
 * @param {vec3} b the second operand
 * @returns {vec3} out
 */
vec3 vec3_cross(vec3 out, vec3 a, vec3 b) {
    float ax = a[0], ay = a[1], az = a[2],
        bx = b[0], by = b[1], bz = b[2];

    return vec3_set(out,
      ay * bz - az * by,
      az * bx - ax * bz,
      ax * by - ay * bx
    );
}

#endif

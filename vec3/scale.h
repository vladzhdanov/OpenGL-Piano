#ifndef __VEC3_SCALE
#define __VEC3_SCALE

#include "type.h"
#include "set.h"

/**
 * Scales a vec3 by a scalar number
 *
 * @param {vec3} out the receiving vector
 * @param {vec3} a the vector to scale
 * @param {Number} b amount to scale the vector by
 * @returns {vec3} out
 */
vec3 vec3_scale(vec3 out, vec3 a, float b) {
    return vec3_set(out,
      a[0] * b,
      a[1] * b,
      a[2] * b
    );
}

#endif

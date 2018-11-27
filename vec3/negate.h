#ifndef __VEC3_NEGATE
#define __VEC3_NEGATE

#include "type.h"
#include "set.h"

/**
 * Negates the components of a vec3
 *
 * @param {vec3} out the receiving vector
 * @param {vec3} a vector to negate
 * @returns {vec3} out
 */
vec3 vec3_negate(vec3 out, vec3 a) {
    return vec3_set(out, -a[0], -a[1], -a[2]);
}

#endif

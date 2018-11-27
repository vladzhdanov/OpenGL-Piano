#ifndef __VEC3_SET
#define __VEC3_SET

#include "type.h"

/**
 * Set the components of a vec3 to the given values
 *
 * @param {vec3} out the receiving vector
 * @param {Number} x X component
 * @param {Number} y Y component
 * @param {Number} z Z component
 * @returns {vec3} out
 */
vec3 vec3_set(vec3 out, float x, float y, float z) {
    out[0] = x;
    out[1] = y;
    out[2] = z;
    return out;
}
#endif

#ifndef __VEC3_FROMVALUES
#define __VEC3_FROMVALUES

#include "type.h"
#include "create.h"
#include "set.h"

/**
 * Creates a new vec3 initialized with the given values
 *
 * @param {Number} x X component
 * @param {Number} y Y component
 * @param {Number} z Z component
 * @returns {vec3} a new 3D vector
 */
vec3 vec3_fromValues(float x, float y, float z) {
    return vec3_set(vec3_create(), x, y, z);
}

#endif

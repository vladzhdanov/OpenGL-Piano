#ifndef __VEC3_CLONE
#define __VEC3_CLONE

#include "type.h"
#include "create.h"
#include "set.h"

/**
 * Creates a new vec3 initialized with values from an existing vector
 *
 * @param {vec3} a vector to clone
 * @returns {vec3} a new 3D vector
 */
vec3 vec3_clone(vec3 a) {
    return vec3_set(vec3_create(), a[0], a[1], a[2]);
}
#endif

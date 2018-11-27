#ifndef __VEC3_CREATE
#define __VEC3_CREATE
#include <stdlib.h>
#include "type.h"
/**
 * Creates a new, empty vec3
 *
 * @returns {vec3} a new 3D vector
 */
vec3 vec3_create() {
    vec3 out = malloc(sizeof(float) * 3);
    out[0] = 0;
    out[1] = 0;
    out[2] = 0;
    return out;
}

#endif

#ifndef __VEC3_LENGTH
#define __VEC3_LENGTH

#include <math.h>
#include "type.h"
#include "squaredLength.h"

/**
 * Calculates the length of a vec3
 *
 * @param {vec3} a vector to calculate length of
 * @returns {Number} length of a
 */
float vec3_length(vec3 a) {
    return sqrtf(vec3_squaredLength(a));
}

#endif

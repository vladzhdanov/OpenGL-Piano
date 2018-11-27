#ifndef __VEC3_DISTANCE
#define __VEC3_DISTANCE

#include <math.h>
#include "type.h"
#include "squaredDistance.h"

/**
 * Calculates the euclidian distance between two vec3's
 *
 * @param {vec3} a the first operand
 * @param {vec3} b the second operand
 * @returns {Number} distance between a and b
 */
float vec3_distance(vec3 a, vec3 b) {
    return sqrtf(vec3_squaredDistance(a, b));
}

#endif

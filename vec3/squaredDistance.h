#ifndef __VEC3_SQUAREDDISTANCE
#define __VEC3_SQUAREDDISTANCE

#include "type.h"

/**
 * Calculates the squared euclidian distance between two vec3's
 *
 * @param {vec3} a the first operand
 * @param {vec3} b the second operand
 * @returns {Number} squared distance between a and b
 */
float vec3_squaredDistance(vec3 a, vec3 b) {
    float x = b[0] - a[0],
          y = b[1] - a[1],
          z = b[2] - a[2];
    return x*x + y*y + z*z;
}

#endif

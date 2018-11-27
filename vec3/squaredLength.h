#ifndef __VEC3_SQUAREDLENGTH
#define __VEC3_SQUAREDLENGTH

#include "type.h"

/**
 * Calculates the squared length of a vec3
 *
 * @param {vec3} a vector to calculate squared length of
 * @returns {Number} squared length of a
 */
float vec3_squaredLength(vec3 a) {
    float x = a[0],
          y = a[1],
          z = a[2];
    return x*x + y*y + z*z;
}

#endif

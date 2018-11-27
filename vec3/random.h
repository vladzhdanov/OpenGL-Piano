#ifndef __VEC3_RANDOM
#define __VEC3_RANDOM

#include <math.h>
#include "type.h"
#include "set.h"

/**
 * Generates a random vector with the given scale
 *
 * @param {vec3} out the receiving vector
 * @param {Number} [scale] Length of the resulting vector. If ommitted, a unit vector will be returned
 * @returns {vec3} out
 */
vec3 vec3_random(vec3 out, float scale) {

    float r = (float)(rand())/RAND_MAX * 2.0 * M_PI;
    float z = (float)(rand())/RAND_MAX * 2.0 - 1.0;
    float zScale = sqrtf(1.0 - z * z) * scale;

    return vec3_set(out,
      cosf(r) * zScale,
      sinf(r) * zScale,
      z * scale
    );
}

#endif

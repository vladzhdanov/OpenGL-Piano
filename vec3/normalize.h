#ifndef __VEC3_NORMALIZE
#define __VEC3_NORMALIZE

#include <math.h>
#include "type.h"
#include "set.h"
#include "length.h"

/**
 * Normalize a vec3
 *
 * @param {vec3} out the receiving vector
 * @param {vec3} a vector to normalize
 * @returns {vec3} out
 */
vec3 vec3_normalize(vec3 out, vec3 a) {
    float len = vec3_length(a);
    if (len > 0) {
        //TODO: evaluate use of glm_invsqrt here?
        len = 1 / sqrt(len);
        vec3_set(out, a[0] * len, a[1] * len, a[2] * len);
    }
    return out;
}

#endif

#ifndef __VEC3_ANGLE
#define __VEC3_ANGLE

#include "type.h"
#include "dot.h"
#include "normalize.h"
#include "fromValues.h"

vec3 tempA, tempB;

/**
 * Get the angle between two 3D vectors
 * @param {vec3} a The first operand
 * @param {vec3} b The second operand
 * @returns {Number} The angle in radians
 */
float vec3_angle(vec3 a, vec3 b) {
    tempA = vec3_fromValues(a[0], a[1], a[2]);
    tempB = vec3_fromValues(b[0], b[1], b[2]);

    vec3_normalize(tempA, tempA);
    vec3_normalize(tempB, tempB);

    float cosine = vec3_dot(tempA, tempB);

    if(cosine > 1.0){
        return 0;
    } else {
        return acosf(cosine);
    }
}

#endif

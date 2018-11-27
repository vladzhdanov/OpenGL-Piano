#ifndef __VEC3_ROTATEX
#define __VEC3_ROTATEX

#include <math.h>
#include "type.h"
#include "set.h"

float p[3], r[3];

/**
 * Rotate a 3D vector around the z-axis
 * @param {vec3} out The receiving vec3
 * @param {vec3} a The vec3 point to rotate
 * @param {vec3} b The origin of the rotation
 * @param {Number} c The angle of rotation
 * @returns {vec3} out
 */
vec3_rotateZ(out, a, b, c){
    //Translate point to the origin
    p[0] = a[0] - b[0];
    p[1] = a[1] - b[1];
    p[2] = a[2] - b[2];

    //perform rotation
    r[0] = p[0]*cosf(c) - p[1]*sinf(c);
    r[1] = p[0]*sinf(c) + p[1]*cosf(c);
    r[2] = p[2];

    //translate to correct position
    return vec3_set(out,
      r[0] + b[0],
      r[1] + b[1],
      r[2] + b[2]
    );
}

#endif

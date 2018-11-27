#ifndef __VEC3_LERP
#define __VEC3_LERP

/**
 * Performs a linear interpolation between two vec3's
 *
 * @param {vec3} out the receiving vector
 * @param {vec3} a the first operand
 * @param {vec3} b the second operand
 * @param {Number} t interpolation amount between the two inputs
 * @returns {vec3} out
 */
vec3 vec3_lerp(vec3 out, vec3 a, vec3 b, float t) {
    float ax = a[0], ay = a[1], az = a[2];
    return vec3_set(out,
      ax + t * (b[0] - ax),
      ay + t * (b[1] - ay),
      az + t * (b[2] - az)
    );
}

#endif

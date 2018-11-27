#ifndef __VEC3_TRANSFORRMAT3

/**
 * Transforms the vec3 with a mat3.
 *
 * @param {vec3} out the receiving vector
 * @param {vec3} a the vector to transform
 * @param {mat3} m the 3x3 matrix to transform with
 * @returns {vec3} out
 */
vec3 vec3_transformMat3(vec3 out, vec3 a, float m[9]) {
    float x = a[0], y = a[1], z = a[2];
    return vec3_set(out,
      x * m[0] + y * m[3] + z * m[6],
      x * m[1] + y * m[4] + z * m[7],
      x * m[2] + y * m[5] + z * m[8]
    );
}

#endif

#ifndef __VEC3_TRANSFORMMAT4
#define __VEC3_TRANSFORMMAT4

#include "type.h"
#include "set.h"
#include "float_cmp.h"

/**
 * Transforms the vec3 with a mat4.
 * 4th vector component is implicitly '1'
 *
 * @param {vec3} out the receiving vector
 * @param {vec3} a the vector to transform
 * @param {mat4} m matrix to transform with
 * @returns {vec3} out
 */
vec3 vec3_transformMat4(vec3 out, vec3 a, float m[16]) {
    float x = a[0],
          y = a[1],
          z = a[2],
          w = m[3] * x + m[7] * y + m[11] * z + m[15];

    if (float_cmp(w, 0.0f, 1)) {
      w = 1.0f;
    }

    return vec3_set(out,
      (m[0] * x + m[4] * y + m[8] * z + m[12]) / w,
      (m[1] * x + m[5] * y + m[9] * z + m[13]) / w,
      (m[2] * x + m[6] * y + m[10] * z + m[14]) / w
    );
}

#endif

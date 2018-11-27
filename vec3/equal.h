#ifndef __VEC3_EQUAL
#define __VEC3_EQUAL

#include <math.h>
#include <assert.h>
#include "float_cmp.h"

int vec3_equal(vec3 a, vec3 b) {

  return float_cmp(a[0], b[0], 1) &
         float_cmp(a[1], b[1], 1) &
         float_cmp(a[2], b[2], 1);
}

#endif

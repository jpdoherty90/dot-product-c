#include "vec.h"
#include <time.h>

data_t dotproduct(vec_ptr u, vec_ptr v) {
   int len = vec_length(u);
   int limit = len - 1;
   long acc1 = 0;
   long acc2 = 0;
   data_t *udata = get_vec_start(u);
   data_t *vdata = get_vec_start(v);
   int i;
   for (i = 0; i < limit; i+=2) { // we can assume both vectors are same length
      acc1 += udata[i] * vdata[i];
      acc2 += udata[i+1] * vdata[i+1];
   }
   for (; i < len; i++) {
      acc1 += udata[i] * vdata[i];
   }
   return acc1 + acc2;
}

// Speed ups:
// - Pull the vector length call out of the loop
// - Pull the data access out, make them address lookups instead of function calls
// - Use a temp var (acc) instead of sum (which will be in memory)
// - Unroll the loop to do 2 calculations at once
// - Add another temp var (acc2) to allow instruction level parallelism
// - Add another acc and unrolling to do 3 at
// Result: from about ~30ms on the longer one down to ~16ms

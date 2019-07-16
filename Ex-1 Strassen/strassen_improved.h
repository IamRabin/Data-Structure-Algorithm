#ifndef __STRASSEN_IMPROVED__

#include <stdlib.h>


/**
 * Matrix multiplication of squared matrices A, B of size n x n using the improved
 * Strassen algorithm of size n*n. The idea is to reduce the use of temporary memory space by reusing
 * the temporary memory space effectively. So  resulting matrix C 's blocks are reused temporarily.
 */
void strassen_improved(float **C, float **A, float **B, const size_t n);

#endif // __STRASSEN_IMPROVED__

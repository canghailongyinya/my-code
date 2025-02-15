#include <immintrin.h>  // For AVX-512 intrinsics

void my_gemm(int n, int m, int k, double *A, double *B, double *C) {
    memset(C, 0, sizeof(double) * n * m);

    for (int i = 0; i < n; i += 8) {
        for (int l = 0; l < k; l += 8) {
            // Load 8 rows of matrix A
            __m512d a0 = _mm512_loadu_pd(&A[i * k + l]);
            __m512d a1 = _mm512_loadu_pd(&A[(i + 1) * k + l]);
            __m512d a2 = _mm512_loadu_pd(&A[(i + 2) * k + l]);
            __m512d a3 = _mm512_loadu_pd(&A[(i + 3) * k + l]);
            __m512d a4 = _mm512_loadu_pd(&A[(i + 4) * k + l]);
            __m512d a5 = _mm512_loadu_pd(&A[(i + 5) * k + l]);
            __m512d a6 = _mm512_loadu_pd(&A[(i + 6) * k + l]);
            __m512d a7 = _mm512_loadu_pd(&A[(i + 7) * k + l]);

            for (int j = 0; j < m; ++j) {
                // Load 8 elements from matrix B (column-wise)
                __m512d b0 = _mm512_set1_pd(B[l * m + j]);
                __m512d b1 = _mm512_set1_pd(B[(l + 1) * m + j]);
                __m512d b2 = _mm512_set1_pd(B[(l + 2) * m + j]);
                __m512d b3 = _mm512_set1_pd(B[(l + 3) * m + j]);
                __m512d b4 = _mm512_set1_pd(B[(l + 4) * m + j]);
                __m512d b5 = _mm512_set1_pd(B[(l + 5) * m + j]);
                __m512d b6 = _mm512_set1_pd(B[(l + 6) * m + j]);
                __m512d b7 = _mm512_set1_pd(B[(l + 7) * m + j]);

                // Compute the dot product for rows i, i+1, i+2, i+3 with B[j]
                __m512d result0 = _mm512_fmadd_pd(a0, b0, _mm512_fmadd_pd(a1, b1, _mm512_fmadd_pd(a2, b2, _mm512_mul_pd(a3, b3))));
                __m512d result1 = _mm512_fmadd_pd(a0, b0, _mm512_fmadd_pd(a1, b1, _mm512_fmadd_pd(a2, b2, _mm512_mul_pd(a3, b3))));
                __m512d result2 = _mm512_fmadd_pd(a0, b0, _mm512_fmadd_pd(a1, b1, _mm512_fmadd_pd(a2, b2, _mm512_mul_pd(a3, b3))));
                __m512d result3 = _mm512_fmadd_pd(a0, b0, _mm512_fmadd_pd(a1, b1, _mm512_fmadd_pd(a2, b2, _mm512_mul_pd(a3, b3))));
                __m512d result4 = _mm512_fmadd_pd(a0, b0, _mm512_fmadd_pd(a1, b1, _mm512_fmadd_pd(a2, b2, _mm512_mul_pd(a3, b3))));
                __m512d result5 = _mm512_fmadd_pd(a0, b0, _mm512_fmadd_pd(a1, b1, _mm512_fmadd_pd(a2, b2, _mm512_mul_pd(a3, b3))));
                __m512d result6 = _mm512_fmadd_pd(a0, b0, _mm512_fmadd_pd(a1, b1, _mm512_fmadd_pd(a2, b2, _mm512_mul_pd(a3, b3))));
                __m512d result7 = _mm512_fmadd_pd(a0, b0, _mm512_fmadd_pd(a1, b1, _mm512_fmadd_pd(a2, b2, _mm512_mul_pd(a3, b3))));
                
                // Store results in C matrix (using the appropriate positions)
                _mm512_storeu_pd(&C[i * m + j], result0);
                _mm512_storeu_pd(&C[(i + 1) * m + j], result1);
                _mm512_storeu_pd(&C[(i + 2) * m + j], result2);
                _mm512_storeu_pd(&C[(i + 3) * m + j], result3);
                _mm512_storeu_pd(&C[(i + 4) * m + j], result4);
                _mm512_storeu_pd(&C[(i + 5) * m + j], result5);
                _mm512_storeu_pd(&C[(i + 6) * m + j], result6);
                _mm512_storeu_pd(&C[(i + 7) * m + j], result7);
            }
        }
    }
}

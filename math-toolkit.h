#ifndef __RAY_MATH_TOOLKIT_H
#define __RAY_MATH_TOOLKIT_H

#include <math.h>
#include <stdio.h>
#include <assert.h>
#include <immintrin.h>


static inline
void normalize(double *v)
{
    double d = sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
    assert(d != 0.0 && "Error calculating normal");

    v[0] /= d;
    v[1] /= d;
    v[2] /= d;
}

static inline
double length(const double *v)
{
    return sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
}

static inline
void add_vector(const double *a, const double *b, double *out)
{
	out[0] = a[0] + b[0];
	out[1] = a[1] + b[1];
	out[2] = a[2] + b[2];
}

static inline
void subtract_vector(const double *a, const double *b, double *out)
{
	out[0] = a[0] - b[0];
	out[1] = a[1] - b[1];
	out[2] = a[2] - b[2];
}

static inline
void multiply_vectors(const double *a, const double *b, double *out)
{
	out[0] = a[0] * b[0];
	out[1] = a[1] * b[1];
	out[2] = a[2] * b[2];
}

static inline
void multiply_vector(const double *a, double b, double *out)
{
	out[0] = a[0] * b;
	out[1] = a[1] * b;
	out[2] = a[2] * b;
}

static inline
void cross_product(const double *v1, const double *v2, double *out)
{
    out[0] = v1[1] * v2[2] - v1[2] * v2[1];
    out[1] = v1[2] * v2[0] - v1[0] * v2[2];
    out[2] = v1[0] * v2[1] - v1[1] * v2[0];
}

static inline
double dot_product(const double *v1, const double *v2)
{
	return v1[0]*v2[0] + v1[1]*v2[1] + v1[2]*v2[2];
}

static inline
void scalar_triple_product(const double *u, const double *v, const double *w,
                           double *out)
{
	__m256d U  = _mm256_set_pd( u[0], u[1], u[2], 0.0 );
	__m256d V1 = _mm256_set_pd( v[2], v[1], v[0], 0.0 );
	__m256d V2 = _mm256_set_pd( v[2], v[0], v[1], 0.0 );
	__m256d W1 = _mm256_set_pd( w[2], w[1], w[0], 0.0 );	
	__m256d W2 = _mm256_set_pd( w[2], w[0], w[1], 0.0 );	
					   
   	__m256d cross_result = _mm256_sub_pd(
	_mm256_mul_pd(_mm256_shuffle_pd(V1, V1, 6), _mm256_shuffle_pd(W2, W2, 10)), 
	_mm256_mul_pd(_mm256_shuffle_pd(V2, V2, 10), _mm256_shuffle_pd(W1, W1, 6)));
 	__m256d mul_result = _mm256_mul_pd( U, cross_result );

	out[0] = mul_result[3];
	out[1] = mul_result[2];
	out[2] = mul_result[1];
}

static inline
double scalar_triple(const double *u, const double *v, const double *w)
{
    double tmp[3];
    cross_product(w, u, tmp);
    return dot_product(v, tmp);
}

#endif

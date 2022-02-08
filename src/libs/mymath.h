#ifndef MYMATH_HEADER
#define MYMATH_HEADER

#include "./matrix.h"

#define ABS(n) (n < 0 ? -n : n)
#define CLAMP_MIN(n, min) (n < min ? min : n)
#define CLAMP_MAX(n, max) (n > max ? max : n)
#define CLAMP(n, min, max) (CLAMP_MAX(CLAMP_MIN(n, min), max))

typedef struct
{
    double (*ceil)(double);
    long (*sum)(Matrix *);
    double (*average)(Matrix *);
    double (*variance)(Matrix *);
    double (*standard_deviation)(Matrix *);
} _mymath_namespace;

extern _mymath_namespace const mymath;

#endif
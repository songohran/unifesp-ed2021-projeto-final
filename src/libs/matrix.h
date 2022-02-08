#ifndef MATRIX_HEADER
#define MATRIX_HEADER

#include <stdlib.h>

typedef struct _Matrix Matrix;

typedef struct
{
    Matrix *(*create)(u_int);
    Matrix *(*adimensional_create)(int);

    Matrix *(*get)(Matrix *, size_t);
    int (*adimensional_value)(Matrix *);

    size_t (*index)(Matrix *, Matrix *);

    void (*append)(Matrix *, Matrix *);
    void (*adimensional_set_value)(Matrix *, int);
    void (*fill)(Matrix *, size_t);

    Matrix *(*remove)(Matrix *, size_t);
    void (*clear)(Matrix *);

    void (*foreach)(Matrix *, void (*callback)(Matrix *, size_t, Matrix *));

    u_int (*dimension)(Matrix *);
    size_t (*length)(Matrix *);
    size_t (*get_sizeof)();
} _matrix_namespace;

extern _matrix_namespace const matrix;

#endif
#include <stdlib.h>
#include <assert.h>
#include <math.h>

#include "./matrix.h"
#include "./mymath.h"

double mymath_ceil(double number)
{
    number = ABS(number);

    int number_ceil = ceil(number);
    int qt_five = number_ceil / 5;

    return number_ceil % 5 == 0 ? number_ceil : (qt_five * 5) + 5;
}

long mymath_sum(Matrix *_matrix)
{
    assert(_matrix != NULL);
    assert(matrix.dimension(_matrix) == 1);

    long sum_result = 0;

    for (size_t i = 0; i < matrix.length(_matrix); i++)
    {
        sum_result += matrix.adimensional_value(matrix.get(_matrix, i));
    }

    return sum_result;
}

double mymath_average(Matrix *_matrix)
{
    assert(_matrix != NULL);
    assert(matrix.dimension(_matrix) == 1);

    double sum = mymath_sum(_matrix);
    double length = matrix.length(_matrix);

    return sum / length;
}

double mymath_variance(Matrix *_matrix)
{
    assert(_matrix != NULL);
    assert(matrix.dimension(_matrix) == 1);

    double variance_result = 0;
    double average = mymath_average(_matrix);
    size_t length = matrix.length(_matrix);

    for (size_t i = 0; i < length; i++)
    {
        double curr_value = matrix.adimensional_value(matrix.get(_matrix, i));
        variance_result += pow(curr_value - average, 2);
    }

    variance_result /= length;

    return variance_result;
}

double mymath_standard_deviation(Matrix *_matrix)
{
    assert(_matrix != NULL);
    assert(matrix.dimension(_matrix) == 1);

    return sqrt(mymath_variance(_matrix));
}

_mymath_namespace const mymath = {
    mymath_ceil,
    mymath_sum,
    mymath_average,
    mymath_variance,
    mymath_standard_deviation};

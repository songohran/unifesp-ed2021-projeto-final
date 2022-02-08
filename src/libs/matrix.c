#include <stdlib.h>
#include <assert.h>

#include "./matrix.h"

typedef struct _Node
{
    Matrix *value;
    struct _Node *next;
    struct _Node *prev;
} Node;

typedef struct _Matrix
{
    int value;
    Node *first;
    Node *last;
    u_int dimension;
    size_t length;
} Matrix;

Matrix *matrix_create(u_int dimension)
{
    Matrix *_matrix = malloc(sizeof(Matrix));
    _matrix->dimension = dimension;
    return _matrix;
}

Matrix *matrix_adimensional_create(int value)
{
    Matrix *_matrix = matrix_create(0);
    _matrix->value = value;
    return _matrix;
}

Node *matrix_node_create(Matrix *value)
{
    Node *node = malloc(sizeof(Node));
    node->value = value;
    return node;
}

Node *_matrix_get_node(Matrix *_matrix, size_t index)
{
    assert(_matrix != NULL);
    assert(_matrix->dimension > 0);

    if (index > _matrix->length - 1 || _matrix->length == 0)
    {
        return NULL;
    }

    Node *curr_node;

    if (index < _matrix->length / 2)
    {
        curr_node = _matrix->first;

        for (size_t i = 1; i <= index; i++)
        {
            curr_node = curr_node->next;
        }
    }
    else
    {
        curr_node = _matrix->last;

        for (size_t i = _matrix->length - 1; i != index; i--)
        {
            curr_node = curr_node->prev;
        }
    }

    return curr_node;
}

Matrix *matrix_get(Matrix *_matrix, size_t index)
{
    assert(_matrix != NULL);
    assert(_matrix->dimension > 0);

    return _matrix_get_node(_matrix, index)->value;
}

int matrix_adimensional_value(Matrix *_matrix)
{
    assert(_matrix != NULL);
    assert(_matrix->dimension == 0);

    return _matrix->value;
}

size_t matrix_index(Matrix *_matrix, Matrix *value)
{
    assert(_matrix != NULL);
    assert(_matrix->dimension > 0);

    if (_matrix->length == 0)
    {
        return -1;
    }

    Node *curr_node = _matrix->first;

    for (size_t i = 0; i < _matrix->length; i++)
    {
        if (curr_node->value == value)
        {
            return i;
        }

        curr_node = curr_node->next;
    }

    return -1;
}

void matrix_append(Matrix *_matrix, Matrix *low_matrix)
{
    assert(_matrix != NULL);
    assert(_matrix->dimension > 0);
    assert(_matrix->dimension == low_matrix->dimension + 1);

    Node *node = matrix_node_create(low_matrix);

    if (_matrix->length == 0)
    {
        _matrix->first = node;
    }
    else if (_matrix->length != 0)
    {
        _matrix->last->next = node;
        node->prev = _matrix->last;
    }

    _matrix->last = node;
    _matrix->length += 1;
}

void matrix_adimensional_set_value(Matrix *_matrix, int value)
{
    assert(_matrix != NULL);
    assert(_matrix->dimension == 0);

    _matrix->value = value;
}

void matrix_fill(Matrix *_matrix, size_t qt)
{
    assert(_matrix != NULL);
    assert(_matrix->dimension > 0);

    int lower_dimension = _matrix->dimension - 1;

    for (size_t i = 0; i < qt; i++)
    {
        matrix_append(_matrix, matrix_create(lower_dimension));
    }
}

Matrix *matrix_remove(Matrix *_matrix, size_t index)
{
    assert(_matrix != NULL);
    assert(_matrix->dimension > 0);

    Node *found_node, *prev_node, *next_node;
    Matrix *found_value;

    found_node = _matrix_get_node(_matrix, index);
    prev_node = found_node->prev;
    next_node = found_node->next;

    found_value = found_node->value;

    if (prev_node != NULL)
    {
        prev_node->next = next_node;
    }

    if (next_node != NULL)
    {
        next_node->prev = prev_node;
    }

    _matrix->length -= 1;

    if (_matrix->last == found_node && _matrix->first != found_node)
    {
        _matrix->last = prev_node;
    }

    if (_matrix->first == found_node)
    {
        if (_matrix->first == _matrix->last)
        {
            _matrix->first = NULL;
            _matrix->last = NULL;
            _matrix->length = 0;
        }
        else
        {
            _matrix->first = next_node;
        }
    }

    free(found_node);

    return found_value;
}

void matrix_clear(Matrix *_matrix)
{
    assert(_matrix != 0);
    assert(_matrix->dimension > 0);

    size_t length = _matrix->length;

    for (size_t i = 0; i < length; i++)
    {
        matrix_remove(_matrix, 0);
    }
}

void matrix_foreach(Matrix *_matrix, void (*callback)(Matrix *, size_t, Matrix *))
{
    assert(_matrix != NULL);

    if (_matrix->dimension == 0 || _matrix->length == 0)
    {
        return;
    }

    Node *curr_node = _matrix->first;

    for (size_t i = 0; i < _matrix->length; i++)
    {
        callback(curr_node->value, i, _matrix);
        curr_node = curr_node->next;
    }
}

u_int matrix_dimension(Matrix *_matrix)
{
    assert(_matrix != NULL);
    return _matrix->dimension;
}

size_t matrix_length(Matrix *_matrix)
{
    assert(_matrix != NULL);
    return _matrix->length;
}

size_t matrix_get_sizeof()
{
    return sizeof(Matrix);
}

_matrix_namespace const matrix = {
    matrix_create,
    matrix_adimensional_create,
    matrix_get,
    matrix_adimensional_value,
    matrix_index,
    matrix_append,
    matrix_adimensional_set_value,
    matrix_fill,
    matrix_remove,
    matrix_clear,
    matrix_foreach,
    matrix_dimension,
    matrix_length,
    matrix_get_sizeof};

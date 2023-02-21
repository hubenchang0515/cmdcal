#ifndef VECTOR_H
#define VECTOR_H

#include <stddef.h>
#include <stdbool.h>

typedef struct Vector vector_t;

struct Vector
{
    void* data;
    size_t element_size;
    size_t length;
    size_t capacity;
};

bool vector_init(vector_t* vec, size_t element_size);
void vector_release(vector_t* vec, void (*deleter)(void*));
bool vector_get(const vector_t* vec, size_t index, void* data);
bool vector_append(vector_t* vec, const void* data);

#endif // VECTOR_H
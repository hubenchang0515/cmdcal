#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "vector.h"

bool vector_init(vector_t* vec, size_t element_size)
{
    if (vec == NULL || element_size == 0)
        return false;

    vec->data = NULL;
    vec->element_size = element_size;
    vec->length = 0;
    vec->capacity = 0;

    return true;
}

void vector_release(vector_t* vec, void (*deleter)(void*))
{
    if (vec == NULL)
        return;

    if (deleter != NULL && vec->data != NULL && vec->length > 0)
    {
        uint8_t* data = (uint8_t*)vec->data;
        for(size_t i = 0; i < vec->length; i++)
        {
            deleter((void*)(data + vec->element_size * i));
        }
    }

    if (vec->data != NULL)
        free(vec->data);
}

bool vector_get(const vector_t* vec, size_t index, void* data)
{
    if (vec == NULL || vec->length <= index)
        return false;

    uint8_t* inner = (uint8_t*)vec->data;
    memcpy(data, inner + vec->element_size * index, vec->element_size);
    return true;
}

bool vector_append(vector_t* vec, const void* data)
{
    if (vec == NULL)
        return false;

    uint8_t* inner = (uint8_t*)vec->data;

    if (vec->length >= vec->capacity)
    {
        size_t bigger = vec->capacity == 0 ? 1 : 2 * vec->capacity;
        inner = realloc(inner, bigger * vec->element_size);
        if (inner == NULL)
            return false;

        vec->data = (void*)inner;
        vec->capacity = bigger;
    }

    memcpy(inner + vec->element_size * vec->length, data, vec->element_size);
    vec->length += 1;
    
    return true;
}
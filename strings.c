#include <stdlib.h>
#include <string.h>

#include "strings.h"
#include "utils.h"

bool string_init(string_t* str, const char* data)
{
    if (str == NULL)
        return false;
    
    if (data == NULL || strlen(data) == 0)
    {
        str->data = NULL;
        return true;
    }

    size_t length = strlen(data);
    str->data = malloc(length + 1);
    if (str->data == NULL)
        return false;

    strcpy(str->data, data);

    return true;
}

void string_release(string_t* str)
{
    if (str == NULL)
        return;

    if (str->data != NULL)
        free(str->data);
}

bool string_concat(string_t* str, const char* suffix)
{
    if (str == NULL || suffix == NULL || strlen(suffix) == 0)
        return true;

    size_t length = strlen(str->data) + strlen(suffix);
    void* data = realloc(str->data, length + 1);
    if (data == NULL)
        return false;

    str->data = data;
    strcat(str->data, suffix);
    return true;
}

bool string_append(string_t* str, char suffix)
{
    if (str == NULL)
        return true;

    size_t length = str->data == NULL ? 0 : strlen(str->data);
    void* data = realloc(str->data, length + 2);
    if (data == NULL)
        return false;

    str->data = data;
    str->data[length] = suffix;
    str->data[length + 1] = 0;
    return true;
}
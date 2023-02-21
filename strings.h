#ifndef STRINGS_H
#define STRINGS_H

#include <stddef.h>
#include <stdbool.h>

typedef struct String string_t;

struct String
{
    char* data;
};

bool string_init(string_t* str, const char* data);
void string_release(string_t* str);

bool string_concat(string_t* str, const char* suffix);
bool string_append(string_t* str, char suffix);

#endif // STRING_H
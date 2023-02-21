#ifndef LEXER_H
#define LEXER_H

#include <stddef.h>
#include <stdbool.h>
#include "token.h"
#include "vector.h"

typedef struct Lexer lexer_t;

struct Lexer
{
    const char* code;
    size_t length;
    size_t current_index;
    char current_char;
};

bool lexer_init(lexer_t* lexer, const char* code);
bool lexer_parse(lexer_t* lexer, vector_t* tokens);

#endif // LEXER_H
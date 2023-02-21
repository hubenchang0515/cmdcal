#ifndef PARSER_H
#define PARSER_H

#include <stddef.h>
#include <stdbool.h>

#include "vector.h"
#include "token.h"
#include "ast.h"

typedef struct Parser parser_t;

struct Parser
{
    const vector_t* tokens;
    size_t current_index;
    token_t current_token;
    ast_node_t* prev_node;
};

bool parser_init(parser_t* parser, const vector_t* tokens);
ast_node_t* parser_generate_ast(parser_t* parser);

#endif // PARSER_H
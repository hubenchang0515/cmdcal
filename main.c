#include <stdio.h>
#include <stdlib.h>

#include "token.h"
#include "lexer.h"
#include "vector.h"
#include "ast.h"
#include "parser.h"
#include "executor.h"

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s <expr>\n", argv[0]);
        printf("     : %s '1+1'\n", argv[0]);
        return EXIT_FAILURE;
    }

    vector_t tokens;
    vector_init(&tokens, sizeof(token_t));
    
    lexer_t lexer;
    lexer_init(&lexer, argv[1]);
    lexer_parse(&lexer, &tokens);

    parser_t parser;
    parser_init(&parser, &tokens);

    ast_node_t* root = parser_generate_ast(&parser);
    vector_release(&tokens, NULL);

    double result = execute(root);
    ast_node_release(root);

    printf("%f\n", result);
    return EXIT_SUCCESS;
}
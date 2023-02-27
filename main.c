#include <stdio.h>
#include <stdlib.h>

#include "token.h"
#include "lexer.h"
#include "vector.h"
#include "ast.h"
#include "parser.h"
#include "executor.h"

double eval(const char* expr)
{
    vector_t tokens;
    vector_init(&tokens, sizeof(token_t));
    
    lexer_t lexer;
    lexer_init(&lexer, expr);
    lexer_parse(&lexer, &tokens);

    parser_t parser;
    parser_init(&parser, &tokens);

    ast_node_t* root = parser_generate_ast(&parser);
    vector_release(&tokens, NULL);

    double result = execute(root);
    ast_node_release(root);
    return result;
}

int main(int argc, char* argv[])
{
    if (argc > 2)
    {
        printf("Usage: %s [expr]\n", argv[0]);
        printf("       %s       start interactive mode\n", argv[0]);
        printf("       %s '1+1' eval 1+1\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (argc == 2)
    {
        double result = eval(argv[1]);
        printf("%f\n", result);
        return EXIT_SUCCESS;
    }

    char expr[1024];
    while (true)
    {
        printf("> ");
        scanf("%[^\n]%*c", expr);
        double result = eval(expr);
        printf("= %f\n", result);
    }
    
}
#include <stdio.h>
#include <stdlib.h>

#include "token.h"
#include "lexer.h"
#include "vector.h"
#include "ast.h"
#include "parser.h"
#include "executor.h"

#define BUFF_SIZE 8

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

char* get_input()
{
    char* expr = malloc(BUFF_SIZE);
    if (expr == NULL)
        return NULL;
    int capacity = BUFF_SIZE;
    int len = 0;
    while (1)
    {
        int ch = getchar();
        if (ch == EOF)
        {
            free(expr);
            return NULL;
            break;
        }

        if (ch == '\n')
        {
            expr[len] = '\0';
            break;
        }

        if (len + 1 >= capacity)
        {
            char* ptr = realloc(expr, capacity + BUFF_SIZE);
            if (ptr == NULL)
            {
                free(expr);
                return NULL;
            }
            expr = ptr;
            capacity += BUFF_SIZE;
        }

        expr[len] = (char)ch;
        len += 1;
    }

    return expr;
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

    while (true)
    {
        printf("> ");
        char* expr = get_input();
        if (expr == NULL)
        {
            printf("\n");
            break;
        }
        double result = eval(expr);
        printf("= %f\n", result);
        free(expr);
    }
    

    return 0;
}
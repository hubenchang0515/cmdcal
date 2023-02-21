#include "token.h"
#include "utils.h"

void token_print(token_t* token)
{
    switch (token->category)
    {
    case TC_FUNCTION:
        printf("[FUNC, %s]\n", token->func.name.data);
        break;

    case TC_NUMBER:
        printf("[NUM, %f]\n", token->number.value);
        break;
    
    case TC_ADD:
        printf("[ADD]\n");
        break;

    case TC_SUB:
        printf("[SUB]\n");
        break;

    case TC_MUL:
        printf("[MUL]\n");
        break;

    case TC_DIV:
        printf("[DIV]\n");
        break;

    case TC_COMMA:
        printf("[COMMA]\n");
        break;

    case TC_LEFT_BRACKET:
        printf("[TC_LEFT_BRACKET]\n");
        break;

    case TC_RIGHT_BRACKET:
        printf("[TC_RIGHT_BRACKET]\n");
        break;

    default:
        ERR("[unknown:%d]\n", token->category);
        break;
    }
}

void token_release(token_t* token)
{
     switch (token->category)
    {
    case TC_FUNCTION:
        string_release(&(token->func.name));
        break;

    default:
        break;
    }
}

bool token_make_functon(token_t* token, string_t name)
{
    if (token == NULL)
        return false;

    token->category = TC_FUNCTION;
    token->func.name = name;
    return true;
}

bool token_make_number(token_t* token, double value)
{
    if (token == NULL)
        return false;

    token->category = TC_NUMBER;
    token->number.value = value;
    return true;
}

bool token_make_add(token_t* token)
{
    if (token == NULL)
        return false;

    token->category = TC_ADD;
    return true;
}

bool token_make_sub(token_t* token)
{
    if (token == NULL)
        return false;

    token->category = TC_SUB;
    return true;
}

bool token_make_mul(token_t* token)
{
    if (token == NULL)
        return false;

    token->category = TC_MUL;
    return true;
}

bool token_make_div(token_t* token)
{
    if (token == NULL)
        return false;

    token->category = TC_DIV;
    return true;
}

bool token_make_comma(token_t* token)
{
    if (token == NULL)
        return false;

    token->category = TC_COMMA;
    return true;
}

bool token_make_left_bracket(token_t* token)
{
    if (token == NULL)
        return false;

    token->category = TC_LEFT_BRACKET;
    return true;
}

bool token_make_right_bracket(token_t* token)
{
    if (token == NULL)
        return false;

    token->category = TC_RIGHT_BRACKET;
    return true;
}
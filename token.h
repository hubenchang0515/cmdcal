#ifndef TOKEN_H
#define TOKEN_H

#include <stdbool.h>
#include "strings.h"

typedef enum TokenCategory token_category_t;
typedef union Token token_t;

enum TokenCategory
{
    TC_INVALID,
    // Key Word Token

    // Identifier Token
    TC_FUNCTION,

    // Literal Token
    TC_NUMBER,
    
    // Operation Token
    TC_ADD,
    TC_SUB,
    TC_MUL,
    TC_DIV,

    // Bound Symbol Token
    TC_COMMA,
    TC_LEFT_BRACKET,
    TC_RIGHT_BRACKET,
};

struct FunctionToken
{
    token_category_t category;
    string_t name;
};

struct NumberToken
{
    token_category_t category;
    double value;
};

struct OperationToken
{
    token_category_t category;
};

union Token
{
    token_category_t category;
    struct FunctionToken func;
    struct NumberToken number;
    struct OperationToken add;
    struct OperationToken sub;
    struct OperationToken mul;
    struct OperationToken div;
};

void token_print(token_t* token);
void token_release(token_t* token);

bool token_make_functon(token_t* token, string_t name);
bool token_make_number(token_t* token, double value);
bool token_make_add(token_t* token);
bool token_make_sub(token_t* token);
bool token_make_mul(token_t* token);
bool token_make_div(token_t* token);
bool token_make_comma(token_t* token);
bool token_make_left_bracket(token_t* token);
bool token_make_right_bracket(token_t* token);

#endif // TOKEN_H
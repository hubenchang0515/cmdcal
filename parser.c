#include "parser.h"
#include "utils.h"

static bool parser_next(parser_t* parser);
static ast_node_t* parser_factor(parser_t* parser);
static ast_node_t* parser_term(parser_t* parser);
static ast_node_t* parser_expr(parser_t* parser);
static ast_node_t* parser_invoke(parser_t* parser);

bool parser_init(parser_t* parser, const vector_t* tokens)
{
    if (parser == NULL || tokens == NULL || tokens->length == 0)
        return false;

    parser->tokens = tokens;
    parser->current_index = 0;
    vector_get(tokens, 0, &(parser->current_token));
    parser->prev_node = NULL;
    return true;
}

static bool parser_is_end(parser_t* parser)
{
    return (parser->current_index >= parser->tokens->length);
}

static bool parser_next(parser_t* parser)
{
    if (parser == NULL || parser_is_end(parser))
        return false;

    parser->current_index += 1;
    if (parser->current_index >= parser->tokens->length)
        return false;

    vector_get(parser->tokens, parser->current_index, &(parser->current_token));
    return true;
}

static ast_node_t* parser_factor(parser_t* parser)
{
    if (parser == NULL || parser_is_end(parser))
        return NULL;

    int symbols[] = {TC_ADD, TC_SUB};

    // factor -> NUMBER
    if (parser->current_token.category == TC_NUMBER)
    {
        ast_node_t* node = ast_make_number_node(parser->current_token.number.value);
        parser_next(parser);
        return node;
    }

    // factor -> (ADD | SUB) factor
    else if (is_int_in(parser->current_token.category, symbols, 2))
    {
        node_category_t category = parser->current_token.category == TC_ADD ? NC_POSITIVE : NC_NEGATIVE;
        parser_next(parser);
        ast_node_t* operand = parser_factor(parser);
        ast_node_t* node = ast_make_unary_node(category, operand);
        return node;
    }

    // factor -> LEFT_BRACKET expr RIGHT_BRACKET
    else if (parser->current_token.category == TC_LEFT_BRACKET)
    {
        parser_next(parser);
        ast_node_t* son = parser_expr(parser);
        if (parser->current_token.category == TC_RIGHT_BRACKET)
        {
            parser_next(parser);
        }
        else
        {
            ERR("loss )\n");
        }
        ast_node_t* node = ast_make_bracket_node(son);
        return node;
    }

    // factor -> invoke
    else if (parser->current_token.category == TC_FUNCTION)
    {
        ast_node_t* node = parser_invoke(parser);
        return node;
    }
    else
    {
        ERR("invalid factor %d\n", parser->current_token.category);
    }

    return NULL;
}

static ast_node_t* parser_term(parser_t* parser)
{
    if (parser == NULL || parser_is_end(parser))
        return NULL;

    // term -> factor ((MUL | DIV) factor)*
    int symbols[] = {TC_MUL, TC_DIV};
    ast_node_t* left = parser_factor(parser);
    while (is_int_in(parser->current_token.category, symbols, 2))
    {
        node_category_t category = 0;
        switch (parser->current_token.category)
        {
        case TC_MUL:
            category = NC_MUL;
            break;

        case TC_DIV:
            category = NC_DIV;
            break;
        
        default:
            ERR("invalid term\n");
            break;
        }

        parser_next(parser);
        ast_node_t* right = parser_factor(parser);
        ast_node_t* node = ast_make_binary_node(category, left, right);
        left = node;
    }

    return left;
}

static ast_node_t* parser_expr(parser_t* parser)
{
    if (parser == NULL || parser_is_end(parser))
        return NULL;

    // expr -> term ((ADD | SUB) term)*
    int symbols[] = {TC_ADD, TC_SUB};
    ast_node_t* left = parser_term(parser);
    while (is_int_in(parser->current_token.category, symbols, 2))
    {
        node_category_t category = 0;
        switch (parser->current_token.category)
        {
        case TC_ADD:
            category = NC_ADD;
            break;

        case TC_SUB:
            category = NC_SUB;
            break;
        
        default:
            ERR("invalid expr\n");
            break;
        }

        parser_next(parser);
        ast_node_t* right = parser_term(parser);
        ast_node_t* node = ast_make_binary_node(category, left, right);
        left = node;
    }

    return left;
}

static ast_node_t* parser_invoke(parser_t* parser)
{
    if (parser == NULL || parser_is_end(parser))
        return NULL;

    // invoke -> FUNCTION LEFT_BRACKET [expression] {COMMA, expression} RIGHT_BRACKET;
    if (parser->current_token.category == TC_FUNCTION)
    {
        string_t func = parser->current_token.func.name;
        parser_next(parser);

        if (parser->current_token.category == TC_LEFT_BRACKET)
        {
            parser_next(parser);
        }
        else
        {
            ERR("loss (\n");
        }

        vector_t args;
        vector_init(&args, sizeof(ast_node_t));

        while (!parser_is_end(parser))
        {
            if (parser->current_token.category == TC_RIGHT_BRACKET)
            {
                parser_next(parser);
                break;
            }

            ast_node_t* arg = parser_expr(parser);
            vector_append(&args, arg);

            if (parser->current_token.category == TC_RIGHT_BRACKET)
            {
                parser_next(parser);
                break;
            }
            else if (parser->current_token.category == TC_COMMA)
            {
                parser_next(parser);
            }
            else
            {
                ERR("loss )\n");
            }
        }
        return ast_make_invoke_node(func, args);
    }
    else
    {
        ERR("invalid invoke\n");
    }

    return NULL;
}


ast_node_t* parser_generate_ast(parser_t* parser)
{
    if (parser == NULL)
        return NULL;

    return parser_expr(parser);
}
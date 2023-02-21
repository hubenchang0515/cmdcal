#include "executor.h"
#include "utils.h"
#include "function.h"

double execute(const ast_node_t* node)
{
    switch(node->category)
    {
    case NC_NUMBER:
        return node->number.value;

    case NC_POSITIVE:
        return execute(node->unary.operand);

    case NC_NEGATIVE:
        return -1 * execute(node->unary.operand);

    case NC_ADD:
        return execute(node->binary.left) + execute(node->binary.right);

    case NC_SUB:
        return execute(node->binary.left) - execute(node->binary.right);

    case NC_MUL:
        return execute(node->binary.left) * execute(node->binary.right);

    case NC_DIV:
        return execute(node->binary.left) / execute(node->binary.right);

    case NC_BRACKET:
        return execute(node->bracket.son);

    case NC_INVOKE:
        func_t func = func_find(node->invoke.func.data);
        vector_t args;
        vector_init(&args, sizeof(double));
        for (size_t i = 0; i < node->invoke.arg_nodes.length; i++)
        {
            ast_node_t arg_node;
            vector_get(&(node->invoke.arg_nodes), i, &arg_node);
            double value = execute(&arg_node);
            vector_append(&args, &value);
        }
        return func(&args);

    default:
        ERR("unknown node: %d\n", node->category);
        return 0.0;
    }
}
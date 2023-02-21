#ifndef FUNCTION_H
#define FUNCTION_H

#include "strings.h"
#include "vector.h"

typedef double (*func_t)(vector_t* args);
typedef struct FuncListNode func_node_t;

struct FuncListNode
{
    char name[32];
    func_t func;
};

extern func_node_t func_list[];

func_t func_find(const char* name);

#endif // FUNCTION_H
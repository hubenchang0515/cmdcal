#include "function.h"
#include "utils.h"
// #include "token.h"

#include <math.h>
#include <string.h>

#define DEF_FUNC1(fun)                      \
static double func_##fun(vector_t* args)    \
{                                           \
    double arg1;                            \
    vector_get(args, 0, &arg1);             \
    return fun(arg1);                       \
}

#define DEF_FUNC2(fun)                      \
static double func_##fun(vector_t* args)    \
{                                           \
    double arg1, arg2;                      \
    vector_get(args, 0, &arg1);             \
    vector_get(args, 1, &arg2);             \
    return fun(arg1, arg2);                 \
}

DEF_FUNC1(fabs)
DEF_FUNC2(fmod)
DEF_FUNC1(sin)
DEF_FUNC1(cos)
DEF_FUNC1(tan)
DEF_FUNC1(asin)
DEF_FUNC1(acos)
DEF_FUNC1(atan)
DEF_FUNC1(sqrt)
DEF_FUNC1(ceil)
DEF_FUNC1(round)
DEF_FUNC1(floor)
DEF_FUNC2(pow)
DEF_FUNC1(exp)
DEF_FUNC1(log)

#define REG_CFUNC(cfun) {#cfun, func_##cfun}
#define NAMED_CFUNC(name, cfun) {name, func_##cfun}

func_node_t func_list[] = {
    NAMED_CFUNC("abs", fabs),
    NAMED_CFUNC("mod", fmod),
    REG_CFUNC(sin),
    REG_CFUNC(cos),
    REG_CFUNC(tan),
    REG_CFUNC(asin),
    REG_CFUNC(acos),
    REG_CFUNC(atan),
    REG_CFUNC(sqrt),
    REG_CFUNC(ceil),
    REG_CFUNC(round),
    REG_CFUNC(floor),
    REG_CFUNC(pow),
    REG_CFUNC(exp),
    REG_CFUNC(log),

    {"", NULL},
};

func_t func_find(const char* name)
{
    for (size_t i = 0; func_list[i].func != NULL; i++)
    {
        if (strcmp(func_list[i].name, name) == 0)
        {
            return func_list[i].func;
        }
    }

    ERR("undefined function '%s'\n", name);
    // ERR("loss )\n");
    return NULL;
}
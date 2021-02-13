#ifndef UM_AST_H
#define UM_AST_H
typedef struct AST_STRUCT {
    enum {
        AST_COMPUND,
        AST_FUNCTION_DEFINITION,
        AST_DEFINITION_TYPE,
        AST_VARIABLE,
        AST_STATEMENT,
        AST_NOOP,
    };
} AST_T;

AST_T* init_ast(int type);
#endif
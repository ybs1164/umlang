#include "include/parser.h"
#include <stdio.h>
#include <stdlib.h>

parser_T* init_parser(lexer_T* lexer) {
    parser_T* parser = calloc(1, sizeof(struct PARSER_STRUCT));

    parser->lexer = lexer;
    parser->token = lexer_next_token(lexer);

    return parser;
}

token_T* parser_eat(parser_T* parser, int type) {
    if (parser->token->type != type) {
        printf("[어휘 분석] : 정해지지 않은 토큰: `%s`, was expecting: `%s`\n", token_to_str(parser->token), token_type_to_str(type));
        exit(1);
    }

    parser->token = lexer_next_token(parser->lexer);

    return parser->token;
}

AST_T* parser_parse(parser_T* parser) {
    return init_ast(AST_NOOP);
}

AST_T* parser_parse_compound(parser_T* parser) {
    // AST_T* compount = init_ast(AST_COMPOUND);
    while (parser->token->type != TOKEN_EOF) {
        /*AST_T* child = */parser_parse(parser);
    }

    return init_ast(AST_NOOP);
}
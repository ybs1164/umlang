#include "include/um.h"
#include "include/lexer.h"
#include "include/parser.h"
#include "include/io.h"
#include <stdlib.h>

void um_compile(char* src) {
    lexer_T* lexer = init_lexer(src);
    parser_T* parser = init_parser(lexer);
    // AST_T* root = parser_parse(parser);
    // printf("%p\n", root);
    token_T* um = parser->token;
    while (1) {
        printf("%s\n", token_to_str(um));
        um = lexer_next_token(lexer);
        if (um->type == TOKEN_EOF)
            break;
    }
}

void um_compile_file(const char* filename) {
    char* src = um_read_file(filename);
    um_compile(src);
    free(src);
}
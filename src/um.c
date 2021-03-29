#include "include/um.h"
#include "include/lexer.h"
#include "include/parser.h"
#include "include/io.h"
#include <stdlib.h>

// 컴파일 함수.
void um_compile(char* src) {
    lexer_T* lexer = init_lexer(src);
    parser_T* parser = init_parser(lexer);
    //AST_T* root = parser_parse(parser);
    
    // printf("%p\n", root->children->size);
    
    // 어휘 분석기가 생성한 토큰 저장하는 변수
    token_T* um = 0;
    while ((um = lexer_next_token(lexer))->type != TOKEN_EOF) {
        printf("%s\n", token_to_str(um));
    }
}

void um_compile_file(const char* filename) {
    char* src = um_read_file(filename);
    um_compile(src);
    free(src);
}
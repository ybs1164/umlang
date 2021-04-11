#include "include/macros.h"
#include "include/lexer.h"
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

// 어휘 분석기 (lexer) 생성 [코드 문자열 하나를 받는다.]
lexer_T* init_lexer(char* src) {
    lexer_T* lexer = calloc(1, sizeof(struct LEXER_STRUCT));
    lexer->src = src;
    lexer->src_size = strlen(src);
    lexer->i = 0;
    lexer->c = src[lexer->i];

    return lexer;
}

// 공백 문자 스킵
void lexer_skip_whitespace(lexer_T* lexer) {
    while (lexer->c == 13 || lexer->c == 10 || lexer->c == ' ' || lexer->c == '/t')
        lexer_advance(lexer);
}

void lexer_advance(lexer_T* lexer) {
    lexer->i++;
    lexer->c = lexer->src[lexer->i];
}

// 단일 문자를 읽어준다.
token_T* lexer_advance_current(lexer_T* lexer, int type) {
    char* value = calloc(2, sizeof(char));
    value[0] = lexer->c;
    value[1] = '\0';

    token_T* token = init_token(value, type);
    lexer_advance(lexer);

    return token;
}

// 한글 문자열 (id) 를 읽어주는 역할을 한다.
token_T* lexer_parse_id(lexer_T* lexer) {
    char* value = calloc(1, sizeof(char));

    while (lexer->c & 0x80 || isdigit(lexer->c)) {
        value = realloc(value, (strlen(value) + 2) * sizeof(char));
        strcat(value, (char[]){lexer->c,0});
        lexer_advance(lexer);
    }

    if (value == "음") {
        return init_token(value, KEYWORD_IF);
    } else if (value == "아님") {
        return init_token(value, KEYWORD_ELSE);
    } else if (value == "반복") {
        return init_token(value, KEYWORD_FOR);
    } else if (value == "함") {
        return init_token(value, KEYWORD_FUNC);
    } else if (value == "나감") {
        return init_token(value, KEYWORD_BREAK);
    } else {
        return init_token(value, TOKEN_ID);
    }
}

// 숫자 문자열 (number) 를 읽어주는 역할을 한다.
token_T* lexer_parse_number(lexer_T* lexer) {
    char* value = calloc(1, sizeof(char));

    while (isdigit(lexer->c)) {
        value = realloc(value, (strlen(value) + 2) * sizeof(char));
        strcat(value, (char[]){lexer->c, 0});
        lexer_advance(lexer);
    }

    if (lexer->c == '.') {
        value = realloc(value, (strlen(value) + 2) * sizeof(char));
        strcat(value, (char[]){lexer->c, 0});
        lexer_advance(lexer);

        while (isdigit(lexer->c)) {
            value = realloc(value, (strlen(value) + 2) * sizeof(char));
            strcat(value, (char[]){lexer->c, 0});
            lexer_advance(lexer);
        }

        return init_token(value, VALUE_FLOAT);
    } else {
        return init_token(value, VALUE_INT);
    }
}

// 어휘 분석기 (lexer) 에서 토큰을 하나 단위로 읽어주는 역할을 함.
token_T* lexer_next_token(lexer_T* lexer) {
    while (lexer->c != '\0') {
        lexer_skip_whitespace(lexer);

        // 한글 문자열은 id 로 처리한다.
        if (lexer->c & 0x80) 
            return lexer_parse_id(lexer);
    

        // 숫자는 number 로 처리한다. (실수 처리도 유한 오토마타 활용해서 구현해야 함)
        if (isdigit(lexer->c))
            return lexer_parse_number(lexer);


        // 남은 단일 문자열들을 체크한다.
        switch (lexer->c) {
            case '=': return lexer_advance_current(lexer, TOKEN_EQUALS);
            case '(': return lexer_advance_current(lexer, TOKEN_LPAREN);
            case ')': return lexer_advance_current(lexer, TOKEN_RPAREN);
            case '{': return lexer_advance_current(lexer, TOKEN_LBRACE);
            case '}': return lexer_advance_current(lexer, TOKEN_RBRACE);
            case ':': return lexer_advance_current(lexer, TOKEN_COLON);
            case ',': return lexer_advance_current(lexer, TOKEN_COMMA);
            case '\"': {
                char* s = calloc(1, sizeof(char));
                lexer_advance(lexer);
                while (lexer->c != '\"') {
                    //printf("%c", lexer->c);
                    s = realloc(s, (strlen(s) + 2) * sizeof(char));
                    strcat(s, (char[]){lexer->c, 0});
                    lexer_advance(lexer);
                }
                lexer_advance(lexer);
                return init_token(s, VALUE_STR);
            }
            case '.': {
                char* s = calloc(1, sizeof(char));
                while (lexer->c == '.') {
                    s = realloc(s, (strlen(s) + 2) * sizeof(char));
                    strcat(s, (char[]){lexer->c, 0});
                    lexer_advance(lexer);
                }
                return init_token(s, TOKEN_DOT);
            };
            case '+': return lexer_advance_current(lexer, OP_ADD);
            case '-': return lexer_advance_current(lexer, OP_SUB);
            case '*': return lexer_advance_current(lexer, OP_MUL);
            case '/': return lexer_advance_current(lexer, OP_DIV);
            case '<': {
                token_T* token = lexer_advance_current(lexer, OP_LS);
                if (lexer->c == '=') {
                    lexer_advance(lexer);
                    return init_token("<=", OP_LSEQ);
                } else {
                    return token;
                }
            }
            case '>': {
                return lexer_advance_current(lexer, OP_GT);
            }
            case ';': return lexer_advance_current(lexer, TOKEN_SEMI);
            case '\0': break;
            default: printf("[구문 분석]: 알 수 없는 문자 '%c' %d\n", lexer->c, lexer->c); exit(1); break;
        }
    }

    return init_token(0, TOKEN_EOF);
}
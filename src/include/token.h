#ifndef UM_TOKEN_H
#define UM_TOKEN_H

typedef struct TOKEN_STRUCT {
    char* value;
    enum {
        TOKEN_EOF,
        TOKEN_ID,
        TOKEN_SEMI,
        TOKEN_EQUALS,
        TOKEN_LPAREN,
        TOKEN_RPAREN,
        TOKEN_LBRACE,
        TOKEN_RBRACE,
        TOKEN_COLON,
        TOKEN_COMMA,
        TOKEN_DOT,
        VALUE_BOOL,
        VALUE_INT,
        VALUE_FLOAT,
        VALUE_STR,
        OP_ADD,
        OP_SUB,
        OP_MUL,
        OP_DIV,
        OP_LS, // <
        OP_LSEQ, // <=
        OP_GT, // >
        OP_GTEQ, // >=
        KEYWORD_IF, // 음
        KEYWORD_ELSE, // 아님
        KEYWORD_FOR, // 반복
        KEYWORD_FUNC, // 함
        KEYWORD_TYPE, // 형
        KEYWORD_BREAK, // 나감 [반환과 똑같은 역할을 할 것]
        KEYWORD_OBJECT, // 객체
        KEYWORD_IMPORT, //
        KEYWORD_EXPORT, // 
        KEYWORD_INT, // 정수
    } type;
} token_T;

token_T* init_token(char* value, int type);

const char* token_type_to_str(int type);

char* token_to_str(token_T* token);
#endif
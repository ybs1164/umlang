#ifndef UM_TOKEN_H
#define UM_TOKEN_H

typedef struct TOKEN_STRUCT {
    char* value;
    enum {
        TOKEN_ID,
        TOKEN_EQUALS,
        TOKEN_LPAREN,
        TOKEN_RPAREN,
        TOKEN_LBRACE,
        TOKEN_RBRACE,
        TOKEN_COLON,
        TOKEN_COMMA,
        TOKEN_FUNC,
        TOKEN_LT,
        TOKEN_GT,
        TOEKN_RIGHT_ARROW,
        TOKEN_INT,
        TOKEN_SEMI,
        TOKEN_EOF,
    } type;
} token_T;

token_T* init_token(char* value, int type);

const char* token_type_to_str(int type);

char* token_to_str(token_T* token);
#endif
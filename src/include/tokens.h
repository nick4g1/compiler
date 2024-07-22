#ifndef TOKEN
#define TOKEN
typedef enum {
  INT_CONST = 0,
  ADD_OP = 1,
  SUB_OP = 2,
  MUL_OP = 3,
  DIV_OP = 4,
  LESS_THAN_OP = 5,
  GREATER_THAN_OP = 6,
  RETURN_KEYW0RD,
  INT_KEYWORD,
  IDENTIFIER,
  OPEN_PAREN,
  CLOSE_PAREN,
  OPEN_BRACE,
  CLOSE_BRACE,
  SEMI,
  END_OF_TOKENS,
  IF_COND,
} TokenType;
typedef struct {
  TokenType type;
  char *value;
} Token;
#endif

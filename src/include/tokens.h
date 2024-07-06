#ifndef TOKEN
#define TOKEN
typedef enum {
  INT = 0,
  SEPARATOR = 0,
  KEYWORD = 0,
  END_OF_TOKENS = 0,
  ADD_OP = 1,
  SUB_OP = 2,
  MUL_OP = 3,
  DIV_OP = 4,
} TokenType;
typedef struct {
  TokenType type;
  char *value;
} Token;
#endif

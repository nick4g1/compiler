typedef enum {
  INT,
  SEPARATOR,
  KEYWORD,
  END_OF_TOKENS,
  OPERATOR,
} TokenType;
typedef struct {
  TokenType type;
  char *value;
} Token;

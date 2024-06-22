typedef enum {
  INT,
  SEPARATOR,
  KEYWORD,
  END_OF_TOKEN,
} TokenType;
typedef struct {
  TokenType type;
  char *value;
} Token;

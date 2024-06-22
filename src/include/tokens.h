typedef enum {
	SEMI,
  OPEN_PAREN,
  CLOSE_PAREN,
} TypeSeparator;

typedef enum {
  ADD,
  SUB,
  MUL,
  DIV,
} TypeOperator;

typedef enum {
  INT,
} TypeLiteral;

typedef enum {
  EXIT,
} TypeKeyword;

typedef struct {
  TypeLiteral type;
  int value;
} TokenLiteral;

typedef struct {
  TypeKeyword type;
  char *word;
} TokenKeyword;

typedef struct {
  TypeSeparator type;
} TokenSeparator;

typedef struct {
  TypeOperator type;
  char op;
} TokenOperator;

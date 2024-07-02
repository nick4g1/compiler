#include "tokens.h"
#ifndef NODE
#define NODE
typedef enum {
  START,
  EXPR_ADD,
  EXPR_SUB,
  EXPR_MUL,
  EXPR_DIV,
  LITERAL,
} NodeType;


typedef struct Node{
  char* value;
  NodeType type;
  struct Node *left;
  struct Node *right;
}Node;

Node *parse(Token *tokens);
Node *initNode(NodeType type, char* value);
#endif

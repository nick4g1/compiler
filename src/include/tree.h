#include <stdio.h>
#include <stdlib.h>
#include "tokens.h"
#ifndef NODE
#define NODE
typedef enum {
  EXPR_ADD = 1,
  EXPR_SUB = 2,
  EXPR_MUL = 3,
  EXPR_DIV = 4,
  LITERAL = 0,
  GREATER_THAN = 5,
  LESS_THAN = 6,
  GREATER_EQ,
  LESS_EQ,
  EQ,
  IF,
} NodeType;


typedef struct Node{
  char* value;
  NodeType op;
  struct Node *left;
  struct Node *right;
}Node;

struct Node *parse(Token *tokens);
struct Node *binExp(Token *tokens, int prec);
struct Node *initNode(NodeType type, struct Node *left, struct Node *right, char* value);
void printTree(struct Node *root, int space);
void destroyTree(struct Node *root);
void destroyNode(struct Node *root);
#endif

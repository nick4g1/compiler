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
} NodeType;


typedef struct Node{
  int value;
  NodeType op;
  struct Node *left;
  struct Node *right;
}Node;

struct Node *parse(Token *tokens);
struct Node *binExp(Token *tokens, int prec);
struct Node *initNode(int op, struct Node *left, struct Node *right, int value);
void printTree(struct Node *root, int space);
void destroyTree(struct Node *root);
void destroyNode(struct Node *root);
#endif

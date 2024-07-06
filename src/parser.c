#include "include/lexer.h"
#include "include/tokens.h"
#include "include/tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define COUNT 5

static int OpPrec[] = {0, 10, 10, 20, 20};

int opPrecedence(int type) {
  int prec = OpPrec[type];
  if (prec == 0) {
    printf("Error with opPrecedence\n");
    exit(1);
  }
  return prec;
}

struct Node *initNode(int op, struct Node *left, struct Node *right,
                      int value) {
  struct Node *n;

  n = (struct Node *)malloc(sizeof(struct Node));
  if (n == NULL) {
    printf("Unable to allocate in initNode\n");
    exit(1);
  }
  n->left = left;
  n->right = right;
  n->value = value;
  n->op = op;
  return n;
}
void printTree(struct Node *root, int space) {
  if (root == NULL)
    return;
  space += COUNT;
  printTree(root->right, space);
  printf("\n");
  for (int i = COUNT; i < space; i++)
    printf(" ");
  switch (root->op) {
  case 1:
    printf("+\n");
    break;
  case 2:
    printf("-\n");
    break;
  case 3:
    printf("*\n");
    break;
  case 4:
    printf("/\n");
    break;
  default:
    printf("%d\n", root->value);
    break;
  }
  printTree(root->left, space);
}

void destroyTree(struct Node *root) {
  if (root == NULL)
    return;
  destroyTree(root->left);
  destroyTree(root->right);
  destroyNode(root);
}

void destroyNode(struct Node *node) {
  node->left = NULL;
  node->right = NULL;
  free(node);
}

size_t tokIndex;
struct Node *literal(Token *tokens) {
  struct Node *n;
  n = initNode(0, NULL, NULL, atoi(tokens[tokIndex].value));
  tokIndex++;
  return n;
}

int findOp(TokenType type) {
  switch (type) {
  case ADD_OP:
    return 1;
  case SUB_OP:
    return 2;
  case MUL_OP:
    return 3;
  case DIV_OP:
    return 4;
  default:
    return 0;
  }
}

struct Node *binExp(Token *tokens, int prec) {
  struct Node *left, *right;
  // get int on the left and increment tokIndex
  left = literal(tokens);

  TokenType type = tokens[tokIndex].type;
  if (type == END_OF_TOKENS)
    return left;
  while (opPrecedence(type) > prec) {
    tokIndex++;
    right = binExp(tokens, opPrecedence(type));
    left = initNode(findOp(type), left, right, 0);
    type = tokens[tokIndex].type;
    if (type == END_OF_TOKENS)
      return left;
  }
  return left;
}

struct Node *parse(Token *tokens) {
  tokIndex = 0;
  return binExp(tokens, 0);
}


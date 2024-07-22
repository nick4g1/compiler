#include "include/lexer.h"
#include "include/tokens.h"
#include "include/tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define COUNT 5

static int OpPrec[] = {0, 10, 10, 20, 20, 10, 10};

int opPrecedence(int type) {
  int prec = OpPrec[type];
  if (prec == 0) {
    printf("Error with opPrecedence\n");
    exit(1);
  }
  return prec;
}

struct Node *initNode(NodeType type, struct Node *left, struct Node *right,
                      char *value) {
  struct Node *n;

  n = (struct Node *)malloc(sizeof(struct Node));
  if (n == NULL) {
    printf("Unable to allocate in initNode\n");
    exit(1);
  }
  n->left = left;
  n->right = right;
  n->value = (char *)malloc(strlen(value) + 1);
  strncpy(n->value, value, strlen(value) + 1);
  n->op = type;
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
    printf("%s\n", root->value);
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
  free(node->value);
  free(node);
}

size_t tokIndex;
struct Node *literal(Token *tokens) {
  struct Node *n;
  n = initNode(LITERAL, NULL, NULL, tokens[tokIndex].value);
  tokIndex++;
  return n;
}

struct Node *condition(Token *tokens) {
  struct Node *root;
  if (tokens[tokIndex].type == IF_COND) {
    root = initNode(IF, NULL, NULL, tokens[tokIndex].value);
  }
  tokIndex++;
  // consume open paren
  if (tokens[tokIndex].type != OPEN_PAREN) {
    printf("Need OPEN_PAREN after if\n");
    exit(1);
  }
  tokIndex++;
  return root;
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
  case LESS_THAN_OP:
    return 6;
  case GREATER_THAN_OP:
    return 5;
  default:
    return 0;
  }
}

struct Node *conditionalExp(Token *tokens) {
  struct Node *root, *left, *right;
  root = condition(tokens);
  left = binExp(tokens, 0);
  // Consume CLOSE_PAREN
  if (tokens[tokIndex].type != CLOSE_PAREN) {
    printf("Need CLOSE_PAREN after condition\n");
    exit(1);
  }
  tokIndex++;
  //if (tokens[tokIndex].type != OPEN_BRACE) {
  //  printf("Need OPEN_BRACE after IF statement\n");
  //  exit(1);
  //}
  //tokIndex++;
  right = binExp(tokens, 0);
  //if (tokens[tokIndex].type != CLOSE_BRACE) {
  //  printf("Need CLOSE_BRACE to close IF statement\n");
  //  exit(1);
  //}
  root->left = left;
  root->right = right;
  return root;
}

struct Node *binExp(Token *tokens, int prec) {
  struct Node *left, *right;
  // get int on the left and increment tokIndex
  left = literal(tokens);

  TokenType type = tokens[tokIndex].type;
  char *value = tokens[tokIndex].value;
  if (type == END_OF_TOKENS || type == CLOSE_PAREN || type == SEMI) {
    return left;
  }
  while (opPrecedence(type) > prec) {
    tokIndex++;
    right = binExp(tokens, opPrecedence(type));
    left = initNode(findOp(type), left, right, value);
    type = tokens[tokIndex].type;
    if (type == END_OF_TOKENS || type == CLOSE_PAREN || type == SEMI)
      return left;
  }
  return left;
}

struct Node *parse(Token *tokens) {
  tokIndex = 0;
  return conditionalExp(tokens);
}

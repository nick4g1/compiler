#include "include/lexer.h"
#include "include/tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define COUNT 5

Node *initNode(NodeType type, char * value) {
  Node *n = (Node *) malloc(sizeof(Node));
  n->left = NULL;
  n->right = NULL;
  n->value = malloc(sizeof(char) * 2);
  n->value = value;
  n->type = type;
  return n;
}
void printTree(Node *root, int space) {
  if (root == NULL) 
    return;
  space += COUNT;
  printTree(root->right, space);
  printf("\n");
  for (int i = COUNT; i < space; i++)
    printf(" ");
  printf("%s\n", root->value);
  printTree(root->left, space);
}

Node *handleExpr(Node *head, char *lval, char *rval) {
  Node **left = &head;
  Node **right= &head;
  left = &(*left)->left;
  right = &(*right)->right;
  *left = initNode(LITERAL, lval);
  *right = initNode(LITERAL, rval);
  return head;
}

Node *parse(Token *tokens) {
  Node *head = malloc(sizeof(Node));
  head = initNode(START, "st");
  Node **curr = &head;
  for (int i = 0; tokens[i].type != END_OF_TOKENS; i++) {
    if (strcmp(tokens[i].value, "+") == 0) {
      *curr = initNode(EXPR_ADD, "+");
      *curr = handleExpr(*curr, tokens[i - 1].value, tokens[i + 1].value);
      curr = &(*curr)->right;
    }
    if (strcmp(tokens[i].value, "*") == 0) {
      *curr = initNode(EXPR_MUL, "*");
      *curr = handleExpr(*curr, tokens[i - 1].value, tokens[i + 1].value);
      curr = &(*curr)->right;
    }
  }
  printTree(head, 0);
  return head;
}

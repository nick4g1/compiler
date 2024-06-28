#include "include/lexer.h"
#include "include/tree.h"
#include <stdio.h>
#include <stdlib.h>

Node* initNode(Node *n, NodeType type, char * value) {
  n = (Node *) malloc(sizeof(Node));
  n->left = NULL;
  n->right = NULL;
  n->value = malloc(sizeof(char) * 2);
  n->value = value;
  n->type = type;
  return n;
}
Node* parser(Token *tokens) {
  Token *currToken = &tokens[0];
  for (int i = 0; tokens[i].type != END_OF_TOKENS; i++) {
    
  }
  return NULL;
}

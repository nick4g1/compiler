#include "include/codeGen.h"
#include "include/tree.h"
#include <stdio.h>

void startCodeGen(struct Node *root) {
  printf("\n\n\nAssembly generation:\n\n");
  codeGen(root);
}

 
void codeGen(struct Node *root) {
  if (root->op == FUNCTION_DEF) {
    printf("    .global %s\n", root->left->value);
    printf("%s:\n", root->left->value);
    // prologue
    printf("    pushq    %%rbp\n");
    printf("    movq    %%rsp, %%rbp\n");
    printf("    subq    $8, %%rsp\n");
    codeGen(root->right);
  } else if (root->op == STATEMENT) {
    codeGen(root->right);
    codeGen(root->left);
  } else if (root->op == LITERAL) {
    printf("    movl    $%s, -%d(%%rbp)\n", root->value, 4);
  } else if (root->op == RETURN_KW) {
    printf("    movl    -%d(%%rbp), %%eax\n", 4);
    printf("    movq    %%rbp, %%rsp\n");
    printf("    popq    %%rbp\n");
    printf("    ret\n");
  }
}

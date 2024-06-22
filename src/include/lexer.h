#include <stdio.h>
#include "tokens.h"

Token *lexer(FILE *input);

Token *numberToken(int *currentIndex, char *currentBuffer);
Token *keywordToken(int *currentIndex, char *currentBuffer);
Token *separatorToken(int *currentIndex, char *currentBuffer);
void printToken(Token t);

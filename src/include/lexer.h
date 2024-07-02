#include <stdio.h>
#include "tokens.h"
#ifndef LEX
#define LEX
Token *lexer(FILE *input);

Token *numberToken(int *currentIndex, char *currentBuffer);
Token *keywordToken(int *currentIndex, char *currentBuffer);
Token *separatorToken(int *currentIndex, char *currentBuffer);
#endif

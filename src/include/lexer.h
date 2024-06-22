#include <stdio.h>
#include "tokens.h"

void lexer(FILE *input, FILE *output);

TokenLiteral *numberToken(char current, FILE *input);
TokenKeyword *keywordToken(char current, FILE *input);

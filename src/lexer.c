#include "include/lexer.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Finds a number token
TokenLiteral *numberToken(char current, FILE *input) {
  TokenLiteral *literal = malloc(sizeof(TokenLiteral));
  literal->type = INT;
  char buff[12];
  int count = 0;

  while (isdigit(current) && current != EOF) {
    if (count >= 11) {
      printf("Number too large\n");
      exit(1);
    }
    buff[count++] = current;
    current = fgetc(input);
  }
  literal->value = atoi(buff);
  fseek(input, -1, SEEK_CUR);
  return (literal);
}

// Finds a keyword token
TokenKeyword *keywordToken(char current, FILE *input) {
  TokenKeyword *keyword = malloc(sizeof(TokenKeyword));
  char buff[20];
  int count = 0;
  while (((current >= 'a' && current <= 'z') ||
          (current >= 'A' && current <= 'Z')) &&
         current != EOF) {
    buff[count++] = current;
    current = fgetc(input);
  }
  if (strcmp(buff, "exit")) {
    keyword->type = EXIT;
  }
  fseek(input, -1, SEEK_CUR);
  return keyword;
}

// Manages overall lexer
void lexer(FILE *input, FILE *output) {

  // Loop through each character in input file until end of file
  char current = fgetc(input);
  while (current != EOF) {
    if (isdigit(current)) {
      TokenLiteral *literal = numberToken(current, input);
      fprintf(output, "Number found: %d\n", literal->value);
    } else if ((current >= 'a' && current <= 'z') ||
               (current >= 'A' && current <= 'Z')) {
      TokenKeyword *keyword = keywordToken(current, input);
      if (keyword->type == EXIT) {
        fprintf(output, "Keyword found: exit\n");
      }
    } else if (current == '(') {
      fprintf(output, "Open Paren found\n");
    } else if (current == ')') {
      fprintf(output, "Close Paren found\n");
    } else if (current == ';') {
      fprintf(output, "Semi found\n");
    }
    current = fgetc(input);
  }
}

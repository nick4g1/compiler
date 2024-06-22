#include "include/lexer.h"
#include "include/tokens.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// Finds a number token
int numberToken(char current, FILE *input) {
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
  return atoi(buff);
}


// Manages overall lexer
void lexer(FILE *input, FILE *output) {

  // Loop through each character in input file until end of file
  char current = fgetc(input);
  while (current != EOF) {
    if (isdigit(current)) {
      TokenLiteral literal;
      literal.type = INT;
      literal.value = numberToken(current, input);
      fprintf(output, "Number found: %d\n", literal.value); 
    }
    current = fgetc(input);
  }
}

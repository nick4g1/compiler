#include "include/lexer.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Finds a number token
Token *numberToken(int *currentIndex, char *currentBuffer) {
  Token *token = malloc(sizeof(Token));
  token->type = INT;
  char *value = malloc(sizeof(char) * 8);
  int valueIndex = 0;
  while (isdigit(currentBuffer[*currentIndex]) &&
         currentBuffer[*currentIndex] != EOF) {
    if (!isdigit(currentBuffer[*currentIndex])) {
      break;
    }
    value[valueIndex++] = currentBuffer[*currentIndex];
    *currentIndex += 1;
  }
  value[valueIndex] = '\0';
  token->value = value;
  return token;
}

// Finds a keyword token
Token *keywordToken(int *currentIndex, char *currentBuffer) {
  Token *token = malloc(sizeof(Token));
  char *value = malloc(sizeof(char) * 20);
  int valueIndex = 0;
  while (((currentBuffer[*currentIndex] >= 'a' && currentBuffer[*currentIndex] <= 'z') ||
          (currentBuffer[*currentIndex] >= 'A' && currentBuffer[*currentIndex] <= 'Z')) &&
         currentBuffer[*currentIndex] != EOF) {
    value[valueIndex++] = currentBuffer[*currentIndex];
    *currentIndex += 1;
  }
  value[valueIndex] = '\0';
  token->value = value;
  if (strcmp(value, "exit")) {
    token->type = KEYWORD;
    token->value = "EXIT";
  }
  return token;
}

// Finds a separator token
Token *separatorToken(int *currentIndex, char *currentBuffer) {
  Token *token = malloc(sizeof(Token));
  token->value = malloc(sizeof(char) * 2);
  token->value[0] = currentBuffer[*currentIndex];
  *currentIndex += 1;
  token->value[1] = '\0';
  return token;
}

// Prints a token
void printToken(Token t) {
  for (int i = 0; t.value[i] != '\0'; i++) {
    printf("%c", t.value[i]);
  }
  printf("\n");
  if (t.type == INT) {
    printf("TOKEN TYPE INT\n");
  }
  if (t.type == SEPARATOR) {
    printf("TOKEN TYPE SEPARATOR\n");
  }
  if (t.type == KEYWORD) {
    printf("TOKEN TYPE KEYWORD\n");
  }
}

size_t tokenIndex;
// Manages overall lexer
Token *lexer(FILE *input) {
  int length;
  char *buffer = 0;
  fseek(input, 0, SEEK_END);
  length = ftell(input);
  fseek(input, 0, SEEK_SET);
  buffer = malloc(length);
  fread(buffer, 1, length, input);
  fclose(input);
  buffer[length + 1] = '\0';
  char *currentBuffer = malloc(length + 1);
  int currentIndex = 0;

  Token *tokens = malloc(sizeof(Token) * 20);
  tokenIndex = 0;
  char current = currentBuffer[currentIndex];
  // loops thru each character in the buffer
  while (current != '\0') {
    Token *token = malloc(sizeof(Token));
    if (isdigit(current)) {
      token = numberToken(&currentIndex, currentBuffer);
      tokens[tokenIndex++] = *token;
      currentIndex--;
    } else if ((current >= 'a' && current <= 'z') ||
               (current >= 'A' && current <= 'Z')) {
      token = keywordToken(&currentIndex, currentBuffer);
      tokens[tokenIndex++] = *token;
      currentIndex--;
    } else if (current == '(' || current == ')' || current == ';') {
      token = separatorToken(&currentIndex, currentBuffer);
      tokens[tokenIndex++] = *token;
      currentIndex--;
    }
    currentIndex++;
    current = currentBuffer[currentIndex];
  }
  return tokens;
}

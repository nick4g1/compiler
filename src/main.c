#include "include/lexer.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
  // Ensure correct args
  if (argc != 3) {
    printf("Incorrect args\n");
    exit(1);
  }

  // Open Files
  char *inputFileName = argv[1];
  FILE *input = fopen(inputFileName, "r");
  char *outputFileName = argv[2];
  FILE *output = fopen(outputFileName, "w");

  // Make sure input file opens
  if (input == NULL) {
    printf("Error opening input file\n");
    exit(1);
  }
  // make sure output file opens
  if (output == NULL) {
    printf("Error opening output file\n");
    exit(1);
  }

  Token *tokens = lexer(input);
  for (int i = 0; tokens[i].type != END_OF_TOKENS; i++){
    for (int j = 0; tokens[i].value[j]; j++) {
      printf("%c", tokens[i].value[j]);
    }
    printf("\n");
  }
  fclose(output);
  return 0;
}

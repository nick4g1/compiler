#include "include/tokens.h"
#include "include/lexer.h"
#include <ctype.h>
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

  lexer(input, output);
  fclose(input);
  fclose(output);
  return 0;
}

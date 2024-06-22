#include "include/enums.h"
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
  if (input == NULL) {
    printf("Error opening input file\n");
    exit(1);
  }
  if (output == NULL) {
    printf("Error opening output file\n");
    exit(1);
  }


  TokenLiteral token;
  token.type = INT;
  token.value = 10;
  printf("%d\n", token.value);


  return 0;
}

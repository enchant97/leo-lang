#include "tokens.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Operators char_to_operator(char *operator_char) {
  if (strcmp(operator_char, "VAR") == 0) {
    return VAR;
  } else if (strcmp(operator_char, "OUT") == 0) {
    return OUT;
  }

  fprintf(stderr, "unknown operator %s", operator_char);
  exit(EXIT_FAILURE);
}

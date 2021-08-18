#include "tokens.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Operators char_to_operator(char *operator_char) {
  if (strcmp(operator_char, "IN") == 0) {
    return IN;
  } else if (strcmp(operator_char, "OUT") == 0) {
    return OUT;
  } else if (strcmp(operator_char, "VAR") == 0) {
    return VAR;
  } else if (strcmp(operator_char, "SET") == 0) {
    return SET;
  } else if (strcmp(operator_char, "CALC") == 0) {
    return CALC;
  } else if (strcmp(operator_char, "IF") == 0) {
    return IF;
  } else if (strcmp(operator_char, "FORI") == 0) {
    return FORI;
  } else if (strcmp(operator_char, "FORV") == 0) {
    return FORV;
  } else if (strcmp(operator_char, "BREAK") == 0) {
    return BREAK;
  } else if (strcmp(operator_char, "FN") == 0) {
    return FN;
  } else if (strcmp(operator_char, "RETURN") == 0) {
    return RETURN;
  } else if (strcmp(operator_char, "CALL") == 0) {
    return CALL;
  } else if (strcmp(operator_char, "USE") == 0) {
    return USE;
  } else if (strcmp(operator_char, "EXIT") == 0) {
    return EXIT;
  } else if (strcmp(operator_char, "COMMENT") == 0) {
    return COMMENT;
  } else {
    fprintf(stderr, "unknown operator %s", operator_char);
    exit(EXIT_FAILURE);
  }
}

Data_Types char_to_data_type(char *src) {
  if (strcmp(src, "STRING") == 0) {
    return STRING;
  } else if (strcmp(src, "INTEGER") == 0) {
    return INTEGER;
  } else {
    fprintf(stderr, "unknown data-type %s", src);
    exit(EXIT_FAILURE);
  }
}

#include "writers.h"
#include "tokens.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void write_variable(FILE *fp, Char_Slice curr_line) {
  char *variable_name = curr_line.array[1];
  char *data_type = curr_line.array[2];
  char *default_value = NULL;
  if (curr_line.rows == 5) {
    default_value = curr_line.array[4];
  } else {
    default_value = "NULL";
  }

  // check for valid known data-types
  Data_Types enum_data_type = char_to_data_type(data_type);

  // handle each data-type differently
  if (enum_data_type == STRING) {
    // TODO extract string quotes from array
    fprintf(fp, "char* %s = %s;", variable_name, default_value);
  } else if (enum_data_type == INTEGER) {
    fprintf(fp, "int %s = %s;", variable_name, default_value);
  } else {
    fprintf(stderr, "unhandled data-type %s", data_type);
    exit(EXIT_FAILURE);
  }
}

void write_out(FILE *fp, Char_Slice curr_line) {
  char *variable_name = curr_line.array[2];
  fprintf(fp, "printf(\"%%s\", %s);", variable_name);
}

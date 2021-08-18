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
  if (curr_line.rows >= 5) {
    default_value = curr_line.array[4];
  } else {
    default_value = "NULL";
  }

  // check for valid known data-types
  Data_Types enum_data_type = char_to_data_type(data_type);

  // handle each data-type differently
  if (enum_data_type == STRING) {
    if (strcmp(default_value, "NULL") == 0) {
      fprintf(fp, "char* %s = %s;", variable_name, default_value);
    } else {
      // check for quotes at start and end
      int end_i = curr_line.rows - 1;
      if (strcmp(&curr_line.array[4][0], "\"") != 0 &&
          strcmp(&curr_line.array[end_i][strlen(curr_line.array[end_i]) - 1],
                 "\"") != 0) {
        fprintf(stderr, "missing double quotes around defined string");
        exit(EXIT_FAILURE);
      }
      default_value = combine_sliced(curr_line, 4, end_i, " ");
      fprintf(fp, "char* %s = %s;", variable_name, default_value);
      free(default_value);
    }
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

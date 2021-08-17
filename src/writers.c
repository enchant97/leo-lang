#include "writers.h"
#include "utils.h"
#include <stdio.h>
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
  if (strcmp(data_type, "STRING") == 0) {
    fprintf(fp, "char* ");
  }
  fprintf(fp, "%s = %s;", variable_name, default_value);
}

void write_out(FILE *fp, Char_Slice curr_line) {
  char *variable_name = curr_line.array[2];
  fprintf(fp, "printf(\"%%s\", %s);", variable_name);
}

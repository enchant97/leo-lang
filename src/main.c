#include "tokens.h"
#include "utils.h"
#include "writers.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SPACE " "

void compile_mode(char *src_path, char *dest_path) {
  FILE *fp;
  char *line = NULL;
  size_t len = 0;
  ssize_t read;
  fp = fopen(src_path, "r");

  if (fp == NULL) {
    fprintf(stderr, "src file to compile not found");
    exit(EXIT_FAILURE);
  }

  FILE *fp_dest;
  fp_dest = fopen(dest_path, "w");

  fprintf(fp_dest, "#include <stdio.h>\n");
  fprintf(fp_dest, "#include <stdlib.h>\n");
  fprintf(fp_dest, "#include <inbuilt.h>\n");
  fprintf(fp_dest, "int main(){");

  Char_Slice curr_line;
  Status_Info curr_status;
  int curr_line_number = 0;

  while ((read = getline(&line, &len, fp)) != -1) {
    curr_line_number++;
    // we don't want a newline character
    trim_newline(line);
    if (strcmp(line, "") == 0) {
      // skip blank lines
      continue;
    }
    // slice each whitespace character
    curr_line = split_line(line, SPACE);
    // find the matching operator
    Operators op = char_to_operator(curr_line.array[0]);
    switch (op) {
    case UNKNOWN_OP:
      curr_status = (Status_Info){true, "unknown operator"};
      break;
    case VAR:
      curr_status = write_variable(fp_dest, curr_line);
      break;
    case SET:
      curr_status = write_set(fp_dest, curr_line);
      break;
    case OUT:
      curr_status = write_out(fp_dest, curr_line);
      break;
    case IN:
      curr_status = write_in(fp_dest, curr_line);
      break;
    case FREE:
      curr_status = write_free(fp_dest, curr_line);
      break;
    case EXIT:
      curr_status = write_exit(fp_dest, curr_line);
      break;
    default:
      curr_status = (Status_Info){true, "unhandled operator"};
      break;
    }
    if (curr_status.has_error) {
      output_compile_error_msg(curr_line, curr_status, curr_line_number);
      remove(dest_path);
      exit(EXIT_FAILURE);
    }
    free(curr_line.array);
  }

  fprintf(fp_dest, "return 0;}\n");

  fclose(fp);
  fclose(fp_dest);
}

int main(int argc, char *argv[]) {
  if (argc == 1) {
    printf("No args were provided");
    return 1;
  }
  if (strcmp(argv[1], "compile") == 0) {
    if (argv[2] != NULL) {
      compile_mode(argv[2], argv[3]);
    }
  }
  return 0;
}

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
  fprintf(fp_dest, "int main(){");

  Char_Slice curr_line;

  while ((read = getline(&line, &len, fp)) != -1) {
    // we don't want a newline character
    trim_newline(line);
    // slice each whitespace character
    curr_line = split_line(line, SPACE);
    // find the matching operator
    Operators op = char_to_operator(curr_line.array[0]);
    switch (op) {
    case VAR:
      write_variable(fp_dest, curr_line);
      break;
    case OUT:
      write_out(fp_dest, curr_line);
      break;
    default:
      fprintf(stderr, "unhandled operator");
      exit(EXIT_FAILURE);
      break;
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

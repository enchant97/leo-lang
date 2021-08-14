#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SPACE " "

struct Char_Tokens {
  int rows;
  char **array;
};

struct Char_Tokens split_line(char *line) {
  char **dest = NULL;
  char *context = NULL;
  int spaces = 0;
  // Windows=strtok_s, POSIX=strtok_r
  char *word = strtok_r(line, SPACE, &context);
  while (word != NULL) {
    dest = realloc(dest, sizeof(char *) * ++spaces);
    dest[spaces - 1] = word;
    word = strtok_r(NULL, SPACE, &context);
  }
  dest = realloc(dest, sizeof(char *) * (spaces + 1));
  dest[spaces] = 0;
  return (struct Char_Tokens){spaces, dest};
}

void output_char_tokens(struct Char_Tokens *char_tokens) {
  for (int i = 0; i < char_tokens->rows; i++) {
    printf("%s\n", char_tokens->array[i]);
  }
}

void compile_mode(char *src_path) {
  FILE *fp;
  char *line = NULL;
  size_t len = 0;
  ssize_t read;
  fp = fopen(src_path, "r");

  if (fp == NULL) {
    fprintf(stderr, "src file to compile not found");
    exit(EXIT_FAILURE);
  }

  struct Char_Tokens curr_line;

  while ((read = getline(&line, &len, fp)) != -1) {
    curr_line = split_line(line);
    output_char_tokens(&curr_line);
    free(curr_line.array);
  }

  fclose(fp);
}

int main(int argc, char *argv[]) {
  if (argc == 1) {
    printf("No args were provided");
    return 1;
  }
  if (strcmp(argv[1], "compile") == 0) {
    if (argv[2] != NULL) {
      compile_mode(argv[2]);
    }
  }
  return 0;
}

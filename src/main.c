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

typedef enum {
  VAR,
  OUT,
} Operators;

Operators char_to_operator(char *operator_char) {
  if (strcmp(operator_char, "VAR") == 0) {
    return VAR;
  } else if (strcmp(operator_char, "OUT") == 0) {
    return OUT;
  }

  fprintf(stderr, "unknown operator %s", operator_char);
  exit(EXIT_FAILURE);
}

void write_variable(FILE *fp, struct Char_Tokens curr_line) {
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

void write_out(FILE *fp, struct Char_Tokens curr_line) {
  char *variable_name = curr_line.array[2];
  fprintf(fp, "printf(\"%%s\", %s);", variable_name);
}

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
  fp_dest = fopen(dest_path, "a");

  fprintf(fp_dest, "#include <stdio.h>\n");
  fprintf(fp_dest, "int main(){");

  struct Char_Tokens curr_line;

  while ((read = getline(&line, &len, fp)) != -1) {
    curr_line = split_line(line);
    Operators op = char_to_operator(curr_line.array[0]);
    switch (op) {
    case VAR:
      write_variable(fp_dest, curr_line);
      break;
    case OUT:
      write_out(fp_dest, curr_line);
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

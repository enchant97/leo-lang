#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Char_Slice split_line(char *line, char *sep) {
  char **dest = NULL;
  char *context = NULL;
  int spaces = 0;
  // Windows=strtok_s, POSIX=strtok_r
  char *word = strtok_r(line, sep, &context);
  while (word != NULL) {
    dest = realloc(dest, sizeof(char *) * ++spaces);
    dest[spaces - 1] = word;
    word = strtok_r(NULL, sep, &context);
  }
  dest = realloc(dest, sizeof(char *) * (spaces + 1));
  dest[spaces] = 0;
  return (Char_Slice){spaces, dest};
}

void output_char_slices(Char_Slice *char_slices) {
  for (int i = 0; i < char_slices->rows; i++) {
    printf("%s\n", char_slices->array[i]);
  }
}

char *combine_sliced(Char_Slice sliced, int start_i, int end_i, char *sep) {
  char *combined = NULL;
  for (int i = start_i; i < (end_i + 1); i++) {
    char *curr_row = sliced.array[i];
    // allocate enough space for current row
    size_t new_size = sizeof(combined) + sizeof(curr_row) + sizeof(sep);
    combined = realloc(combined, new_size);
    if (combined == NULL) {
      fprintf(stderr, "memory allocation error");
      exit(EXIT_FAILURE);
    }
    if (i != start_i) {
      // we don't want a seperator on the first element
      combined = strcat(combined, sep);
    }
    combined = strcat(combined, curr_row);
  }
  return combined;
}

void trim_newline(char *src) {
  int last_index = strlen(src) - 1;
  // make sure src string has minimum length
  if (last_index >= 0) {
    if (src[last_index] == '\n') {
      // make the newline character null
      src[last_index] = '\0';
    }
  }
}

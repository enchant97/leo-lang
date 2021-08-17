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

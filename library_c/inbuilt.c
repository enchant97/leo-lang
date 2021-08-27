#include "inbuilt.h"
#include <stdio.h>
#include <string.h>

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

char* read_stdin_line() {
  // This method requires the char to be freed manually using free()
  char *line;
  size_t len = 0;
  getline(&line, &len, stdin);
  trim_newline(line);
  return line;
}

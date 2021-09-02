#include "utils.h"
#include <stdbool.h>
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

int find_string_end_quote(char *src, int start_i) {
  // quote should be included in src
  char quote_char = src[start_i];
  start_i++;
  int src_len = strlen(src);
  bool skip = false;
  for (int i = start_i; i < src_len; i++) {
    if (skip) {
      skip = false;
    } else {
      if (src[i] == quote_char) {
        return i;
      } else if (src[i] == '\\') {
        skip = true;
      }
    }
  }
  return -1;
}

int calculate_substring_length(int start_i, int end_i) {
  return (end_i - start_i) + 1;
}

void substring(char *src, char *dst, int start_i, int length) {
  int dst_i = 0;

  while (dst_i < length) {
    dst[dst_i] = src[start_i + dst_i];
    dst_i++;
  }
  dst[dst_i] = '\0';
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

void output_compile_error_msg(Char_Slice curr_line, Status_Info curr_status,
                              int curr_line_number) {
  char *combined_line = combine_sliced(curr_line, 0, curr_line.rows - 1, " ");
  fprintf(stderr, "compile error:\n");
  fprintf(stderr, "\t%s\n", curr_status.message);
  fprintf(stderr, "current line (%d):\n", curr_line_number);
  fprintf(stderr, "\t'%s'\n", combined_line);
}

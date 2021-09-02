#ifndef UTILS_H_
#define UTILS_H_
#include <stdbool.h>
typedef struct {
  int rows;
  char **array;
} Char_Slice;
typedef struct {
  bool has_error;
  char *message;
} Status_Info;
Char_Slice split_line(char *line, char *sep);
void output_char_slices(Char_Slice *char_slices);
int find_string_end_quote(char *src, int start_i);
int calculate_substring_length(int start_i, int end_i);
void substring(char *src, char *dst, int start_i, int length);
char *combine_sliced(Char_Slice sliced, int start_row, int end_row, char *sep);
void trim_newline(char *src);
void output_compile_error_msg(Char_Slice curr_line, Status_Info curr_status,
                              int curr_line_number);
#endif

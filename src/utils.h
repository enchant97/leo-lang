#ifndef UTILS_H_
#define UTILS_H_
typedef struct {
  int rows;
  char **array;
} Char_Slice;
Char_Slice split_line(char *line, char *sep);
void output_char_slices(Char_Slice *char_slices);
char *combine_sliced(Char_Slice sliced, int start_row, int end_row, char *sep);
void trim_newline(char *src);
#endif

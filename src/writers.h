#ifndef WRITERS_H_
#define WRITERS_H_
#include "utils.h"
#include <stdio.h>
Status_Info write_variable(FILE *fp, Char_Slice curr_line);
Status_Info write_set(FILE *fp, Char_Slice curr_line);
Status_Info write_out(FILE *fp, Char_Slice curr_line);
Status_Info write_in(FILE *fp, Char_Slice curr_line);
Status_Info write_calc(FILE *fp, Char_Slice curr_line);
Status_Info write_free(FILE *fp, Char_Slice curr_line);
Status_Info write_exit(FILE *fp, Char_Slice curr_line);
#endif

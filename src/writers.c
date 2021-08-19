#include "writers.h"
#include "tokens.h"
#include "utils.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Status_Info write_variable(FILE *fp, Char_Slice curr_line) {
  char *variable_name = curr_line.array[1];
  char *data_type = curr_line.array[2];
  char *default_value;
  bool has_default = false;

  // check if variable has default
  if (curr_line.rows >= 5) {
    if (strcmp(curr_line.array[3], "=") != 0) {
      return (Status_Info){true, "invalid sign"};
    }
    has_default = true;
  }

  // check for valid known data-types
  Data_Types enum_data_type = char_to_data_type(data_type);

  // handle each data-type differently
  if (enum_data_type == STRING) {
    if (!has_default) {
      default_value = "NULL";
      fprintf(fp, "char* %s = %s;", variable_name, default_value);
    } else {
      // check for quotes at start and end
      int end_i = curr_line.rows - 1;
      if (strcmp(&curr_line.array[4][0], "\"") != 0 &&
          strcmp(&curr_line.array[end_i][strlen(curr_line.array[end_i]) - 1],
                 "\"") != 0) {
        return (Status_Info){true,
                             "missing double quotes around defined string"};
      }
      default_value = combine_sliced(curr_line, 4, end_i, " ");
      fprintf(fp, "char* %s = %s;", variable_name, default_value);
      free(default_value);
    }
  } else if (enum_data_type == INTEGER) {
    default_value = curr_line.array[4];
    fprintf(fp, "int %s = %s;", variable_name, default_value);
  } else if (enum_data_type == UNKNOWN_DT) {
    return (Status_Info){true, "unknown data-type"};
  } else {
    return (Status_Info){true, "unhandled data-type"};
  }
  return (Status_Info){false};
}

Status_Info write_set(FILE *fp, Char_Slice curr_line) {
  // TODO check for if variable exists
  // TODO check data-types
  // checks if SET command is valid
  if (curr_line.rows < 4) {
    return (Status_Info){true, "invalid SET"};
  } else if (strcmp(curr_line.array[2], "=") != 0) {
    return (Status_Info){true, "invalid sign"};
  }

  char *variable_name = curr_line.array[1];
  char *new_value = combine_sliced(curr_line, 3, curr_line.rows - 1, " ");

  fprintf(fp, "%s = %s;", variable_name, new_value);

  return (Status_Info){false};
}

Status_Info write_out(FILE *fp, Char_Slice curr_line) {
  Std_Streams stream_type = char_to_std_stream(curr_line.array[1]);
  char *print_content;
  if (strncmp(curr_line.array[2], "\"", 1) == 0) {
    // print from a inline string
    int end_i = curr_line.rows - 1;
    if (strcmp(&curr_line.array[end_i][strlen(curr_line.array[end_i]) - 1],
               "\"") != 0) {
      return (Status_Info){true, "missing double quotes around defined string"};
    }
    print_content = combine_sliced(curr_line, 2, end_i, " ");
  } else {
    // print from a variable
    if (curr_line.rows > 3) {
      return (Status_Info){true, "invalid OUT command"};
    }
    print_content = curr_line.array[2];
  }
  switch (stream_type) {
  case STDOUT:
    fprintf(fp, "printf(\"%%s\", %s);", print_content);
    break;
  case STDERR:
    fprintf(fp, "fprintf(stderr, \"%%s\", %s);", print_content);
    break;
  case UNKNOWN_SS:
    return (Status_Info){true, "unknown std stream type"};
  default:
    return (Status_Info){true, "unhandled std stream type"};
  }
  return (Status_Info){false};
}

Status_Info write_exit(FILE *fp, Char_Slice curr_line) {
  char *exit_code = "0";
  if (curr_line.rows > 2) {
    return (Status_Info){true, "invalid exit command"};
  } else if (curr_line.rows == 2) {
    exit_code = curr_line.array[1];
    // validate that exit code is between 0-255 (and is a integer)
    int exit_code_int = strtol(exit_code, NULL, 10);
    if ((exit_code_int < 1 && strcmp(exit_code, "0") != 0) ||
        exit_code_int > 255) {
      return (Status_Info){true,
                           "invalid exit code integer, must be between 0-255"};
    }
  }
  fprintf(fp, "exit(%s);", exit_code);
  return (Status_Info){false};
}

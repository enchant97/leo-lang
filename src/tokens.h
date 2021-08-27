#ifndef TOKENS_H_
#define TOKENS_H_
typedef enum {
  UNKNOWN_OP,
  IN,
  OUT,
  VAR,
  SET,
  CALC,
  IF,
  FORI,
  FORV,
  BREAK,
  FN,
  RETURN,
  CALL,
  FREE,
  USE,
  EXIT,
  COMMENT
} Operators;
typedef enum {
  UNKNOWN_DT,
  STRING,
  INTEGER,
} Data_Types;
typedef enum {
  UNKNOWN_SS,
  STDOUT,
  STDERR,
  STDIN,
} Std_Streams;
Operators char_to_operator(char *operator_char);
Data_Types char_to_data_type(char *src);
Std_Streams char_to_std_stream(char *src);
#endif

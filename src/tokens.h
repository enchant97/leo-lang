#ifndef TOKENS_H_
#define TOKENS_H_
typedef enum {
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
  USE,
  EXIT,
  COMMENT
} Operators;
typedef enum {
  STRING,
  INTEGER,
} Data_Types;
typedef enum {
  STDOUT,
  STDERR,
  STDIN,
} Std_Streams;
Operators char_to_operator(char *operator_char);
Data_Types char_to_data_type(char *src);
Std_Streams char_to_std_stream(char *src);
#endif

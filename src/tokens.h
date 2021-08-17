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
Operators char_to_operator(char *operator_char);
#endif

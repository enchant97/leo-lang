#ifndef TOKENS_H_
#define TOKENS_H_
typedef enum {
  VAR,
  OUT,
} Operators;
Operators char_to_operator(char *operator_char);
#endif

#ifndef __PRATT_LEXER__
#define __PRATT_LEXER__

#include <stddef.h>
#include <stdbool.h>
#include "token.h"

typedef struct {
  const char *source;
  const char *token_start;
  const char *current;
  size_t line;
} plexer_t;

void lexer_init(const char *source);
ptoken_t lexer_get_token();

#endif

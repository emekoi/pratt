/*====================================================
 * LABEL
 *====================================================*/

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "lib/dmt/dmt.h"
#include "pratt.h"
#include "lexer.h"
#include "util.h"

static void *zrealloc(void *ptr, size_t size) {
  if (ptr && size == 0) {
    dmt_free(ptr);
    return NULL;
  }
  void *p = dmt_realloc(ptr, size);
  if (!p) ERROR("out of memory");
  memset(p, 0, size);
  return p;
}

static void zfree(void *ptr) {
  zrealloc(ptr, 0);
}

/*====================================================
 * STANDALONE
 *====================================================*/

int main(int argc, const char **argv) {
  if (argc < 2) return 0;
  lexer_init(argv[1]);
  ptoken_t t = lexer_get_token();
  while (t.type != TOK_EOF) {
    for (size_t i = 0; i < t.len; i++) {
      putchar(*(t.start+i));
    }
    putchar('\n');
    t = lexer_get_token();
  }

  return 0;
}

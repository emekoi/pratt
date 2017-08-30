/*====================================================
 * LABEL
 *====================================================*/

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "lib/dmt/dmt.h"
#include "lib/fs/fs.h"
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

int main(int argc, char **argv) {
  // if (argc < 2) return 0;

  if (argc > 1) {
    const char *path = dirname(concat("./", strip(argv[1]), NULL));
    const char *file = basename(concat("./", strip(argv[1]), NULL));
    printf("\nexe : %s\n", argv[0]);
    printf("path : %s\n", path);
    printf("file : %s\n\n", file);

    fs_error(fs_mount(path));
    fs_error(fs_setWritePath(path));
    /* check that file exists */
    if (fs_exists(file)) {
      /* read the file */
      size_t len;
      char *data = fs_read(file, &len);
      /* parse file */
      lexer_init(data);
      ptoken_t t = lexer_get_token();
      while (t.type != TOK_EOF) {
        if (t.type == TOK_ERROR) {
          printf("%s: %s: %lu: ", basename(argv[0]), file, t.line + 1);
        } else {
          printf("%s : ", token_name(t.type));
        }
        for (size_t i = 0; i < t.len; i++) {
          putchar(*(t.start+i));
        }
        putchar('\n');
        t = lexer_get_token();
      }
    }
    fs_unmount(path);
    fs_deinit();
  } else {
    /* get input from console */
    char buf[0xFFFFF];
    gets(buf);
    /* parse input */
    lexer_init(buf);
    ptoken_t t = lexer_get_token();
    while (t.type != TOK_EOF) {
      if (t.type == TOK_ERROR) {
        printf("%s: %s:%lu: ", argv[0], "stdin", t.line);
      } else {
        printf("%d: ", t.type);
      }
      for (size_t i = 0; i < t.len; i++) {
        putchar(*(t.start+i));
      }
      putchar('\n');
      t = lexer_get_token();
    }
  }

  return 0;
}

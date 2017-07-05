#ifndef __PRATT_MIN_AST__
#define __PRATT_MIN_AST__

typedef struct pexpr_t pexpr_t;

typedef enum {
  GROUPING,
  LITERAL,
  BINARY,
  UNARY,
} pmintype_t;

struct pexpr_t {
  pmintype_t type;
  union {
    struct { pexpr_t *left; } grouping;
    struct { pexpr_t *left; } literal;
    struct { pexpr_t *left, *op, *right; } binary;
    struct { pexpr_t *left; } unary;
  } u;
};

#endif

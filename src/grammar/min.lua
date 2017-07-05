return {
  { "GROUPING", "grouping: pexpr_t expr;" },
  { "LITERAL",  "literal: pexpr_t value;", },
  { "BINARY",   "binary: pexpr_t left; ptoken_t oper; pexpr_t right;" },
  { "UNARY",    "unary: ptoken_t oper; pexpr_t right;"},

}

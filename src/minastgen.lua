-- lua src/minastgen.lua src/grammar/min src/min.inc

function enum(IN, OUT)
  OUT:write([[
#ifndef __PRATT_MIN_AST__
#define __PRATT_MIN_AST__

typedef struct pexpr_t pexpr_t;

typedef enum {
]])
  for i = 1, #IN do
    local str = string.format("\t%s,\n", IN[i][1])
    OUT:write(str)
  end
  OUT:write("} pmintype_t;\n\n")
end

function struct(IN, OUT)
  OUT:write([[
struct pexpr_t {
  pmintype_t type;
  union {
]])
  for i = 1, #IN do
    local str0 = "\t\tstruct { "
    local str1 = IN[i][2]:match("%a+: (.+)")
    local str2 = " } " .. IN[i][2]:match("%a+") .. ";\n"
    OUT:write(str0 .. str1 .. str2)
  end
  OUT:write([[
  } u;
};

#endif
]])
end

function generate(IN, OUT)
  local IN = require(IN)
  local OUT = io.open(OUT, "wb")
  enum(IN, OUT)
  struct(IN, OUT)


end

generate(arg[1], arg[2])

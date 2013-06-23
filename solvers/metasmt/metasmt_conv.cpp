#include "metasmt_conv.h"

#include <solvers/prop/prop_conv.h>

// To avoid having to build metaSMT into multiple files,
prop_convt *
create_new_metasmt_solver(bool int_encoding, bool is_cpp, const namespacet &ns)
{
  return new metasmt_convt(int_encoding, is_cpp, ns);
}

metasmt_convt::metasmt_convt(bool int_encoding, bool is_cpp,
                             const namespacet &ns)
  : smt_convt(false, int_encoding, ns, is_cpp, false), ctx(), symbols(),
    astsyms(), sym_lookup(symbols, astsyms)
{

  smt_post_init();
}

metasmt_convt::~metasmt_convt()
{
}

void
metasmt_convt::set_to(const expr2tc &expr, bool value)
{
  abort();
}

prop_convt::resultt
metasmt_convt::dec_solve()
{
  abort();
}

expr2tc
metasmt_convt::get(const expr2tc &expr)
{
  abort();
}

tvt
metasmt_convt::l_get(literalt a)
{
  abort();
}

const std::string
metasmt_convt::solver_text()
{
  abort();
}


void
metasmt_convt::assert_lit(const literalt &l)
{
  abort();
}

smt_ast *
metasmt_convt::mk_func_app(const smt_sort *s, smt_func_kind k,
                           const smt_ast **args, unsigned int numargs)
{
  abort();
}

smt_sort *
metasmt_convt::mk_sort(const smt_sort_kind k, ...)
{
  va_list ap;

  va_start(ap, k);
  switch (k) {
  case SMT_SORT_BV:
  {
    unsigned long u = va_arg(ap, unsigned long);
    return new metasmt_smt_sort(k, u);
  }
  case SMT_SORT_ARRAY:
  {
    unsigned long d = va_arg(ap, unsigned long);
    unsigned long r = va_arg(ap, unsigned long);
    metasmt_smt_sort *s = new metasmt_smt_sort(k);
    s->arrdom_width = d;
    s->arrrange_width = r;
    return s;
  }
  case SMT_SORT_BOOL:
    return new metasmt_smt_sort(k);
  case SMT_SORT_INT:
  case SMT_SORT_REAL:
  default:
    std::cerr << "SMT SORT type " << k << " is unsupported by metasmt"
              << std::endl;
  }
}

literalt
metasmt_convt::mk_lit(const smt_ast *s)
{
  abort();
}

smt_ast *
metasmt_convt::mk_smt_int(const mp_integer &theint, bool sign)
{
  abort();
}

smt_ast *
metasmt_convt::mk_smt_real(const std::string &str)
{
  abort();
}

smt_ast *
metasmt_convt::mk_smt_bvint(const mp_integer &theint, bool sign, unsigned int w)
{
  abort();
}

smt_ast *
metasmt_convt::mk_smt_bool(bool val)
{
  abort();
}

smt_ast *
metasmt_convt::mk_smt_symbol(const std::string &name, const smt_sort *s)
{
  // It seems metaSMT makes us generate our own symbol table. Which is annoying.
  // More annoying is that it seems to be a one way process, in which some kind
  // of AST node id is stored, and you can't convert it back to the array, bv
  // or predicate that it originally was.
  // So, keep a secondary symbol table.

  // First: is this already in the symbol table?
  smt_ast *ast = sym_lookup(name);
  if (ast != NULL)
    // Yes, return that piece of AST. This means that, as an opposite to what
    // Z3 does, we get the free variable associated with the name.
    return ast;

  // Nope; generate an appropriate ast.
  const metasmt_smt_sort *ms = metasmt_sort_downcast(s);
  switch (s->id) {
  case SMT_SORT_BV:
  {
    metaSMT::logic::QF_BV::bitvector b =
      metaSMT::logic::QF_BV::new_bitvector(ms->width);
    metasmt_smt_ast *mast = new metasmt_smt_ast(b, s);
    sym_lookup.insert(mast, b, name);
  }
  case SMT_SORT_ARRAY:
  {
    metaSMT::logic::Array::array a =
      metaSMT::logic::Array::new_array(ms->arrrange_width, ms->arrdom_width);
    metasmt_smt_ast *mast = new metasmt_smt_ast(a, s);
    sym_lookup.insert(mast, a, name);
  }
  case SMT_SORT_BOOL:
  {
    metaSMT::logic::predicate p = metaSMT::logic::new_variable();
    metasmt_smt_ast *mast = new metasmt_smt_ast(p, s);
    sym_lookup.insert(mast, p, name);
  }
  default:
    std::cerr << "Unrecognized smt sort in metasmt mk_symbol" << std::endl;
    abort();
  }
}

smt_sort *
metasmt_convt::mk_struct_sort(const type2tc &type)
{
  abort();
}

smt_sort *
metasmt_convt::mk_union_sort(const type2tc &type)
{
  abort();
}

smt_ast *
metasmt_convt::mk_extract(const smt_ast *a, unsigned int high,
                          unsigned int low, const smt_sort *s)
{
  abort();
}

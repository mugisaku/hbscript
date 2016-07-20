#include"hbs_value.hpp"
#include"hbs_memory.hpp"
#include"hbs_context.hpp"
#include"hbs_structure.hpp"




Value
Value::
invert(Memory&  mem) const
{
  auto&  v = dereference(mem);

    if(v.kind == ValueKind::integer)
    {
      return Value(-v.get_integer());
    }


  return Value(ValueKind::undefined);
}


Value
Value::
bit_not(Memory&  mem) const
{
  auto&  v = dereference(mem);

    if(v.kind == ValueKind::integer)
    {
      return Value(~v.get_integer());
    }


  return Value(ValueKind::undefined);
}


Value
Value::
logical_not(Memory&  mem) const
{
  auto&  v = dereference(mem);

    switch(v.kind)
    {
      case(ValueKind::integer):
      case(ValueKind::boolean):
        return Value(!v.get_integer());
        break;
      default:;
    }


  return Value(ValueKind::undefined);
}



Value
Value::
new_(Context&  ctx) const
{
  auto&  mem = ctx.get_memory();

  auto&  v = dereference(mem);

  auto  ptr = mem.allocate();

    switch(v.kind)
    {
      case(ValueKind::structure):
        v.data.st->initialize(ctx);
        break;
    }


  mem[ptr] = v;

  return Value(Reference(ptr));
}


Value
Value::
delete_(Memory&  mem) const
{
    if(kind == ValueKind::reference)
    {
      mem.free(data.i);
    }


  return Value(ValueKind::void_);
}





#include"hbs_value.hpp"
#include"hbs_memory.hpp"
#include"hbs_context.hpp"
#include"hbs_structure.hpp"




Value
Value::
indirect(Memory&  mem) const
{
  auto&  v = dereference(mem);

    switch(v.kind)
    {
      case(ValueKind::pointer):
      case(ValueKind::integer):
        return Value(Reference(Pointer(v.get_integer())));
      default:;
    }


  printf("整数値でもポインタ値でもない値は、脱参照できません\n");

  return Value(ValueKind::undefined);
}


Value
Value::
get_address(Memory&  mem) const
{
    if(kind == ValueKind::reference)
    {
      return Value(Pointer(data.i));
    }



  printf("参照型でない値のアドレスは取得できません\n");

  return Value(ValueKind::undefined);
}


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
      case(ValueKind::pointer):
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

  return Value(ptr);
}


Value
Value::
delete_(Memory&  mem) const
{
  auto&  v = dereference(mem);

    switch(v.kind)
    {
      case(ValueKind::integer):
      case(ValueKind::pointer):
        mem.free(v.data.i);
        break;
      default:;
    }


  return Value(ValueKind::void_);
}





#include"hbs_value.hpp"
#include"hbs_memory.hpp"




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
      default:;
    }


  return Value(ValueKind::undefined);
}





#include"hbs_value.hpp"
#include"hbs_memory.hpp"




Value
Value::
operate_add(Memory&  mem, const Value&  rhs) const
{
  return Value(dereference(mem).get_integer()+rhs.dereference(mem).get_integer());
}



Value
Value::
operate_sub(Memory&  mem, const Value&  rhs) const
{
  return Value(dereference(mem).get_integer()-rhs.dereference(mem).get_integer());
}



Value
Value::
operate_mul(Memory&  mem, const Value&  rhs) const
{
  return Value(dereference(mem).get_integer()*rhs.dereference(mem).get_integer());
}


Value
Value::
operate_div(Memory&  mem, const Value&  rhs) const
{
  return Value(dereference(mem).get_integer()/rhs.dereference(mem).get_integer());
}


Value
Value::
operate_rem(Memory&  mem, const Value&  rhs) const
{
  return Value(dereference(mem).get_integer()%rhs.dereference(mem).get_integer());
}


Value
Value::
operate_bit_or(Memory&  mem, const Value&  rhs) const
{
  return Value(dereference(mem).get_integer()|rhs.dereference(mem).get_integer());
}


Value
Value::
operate_bit_and(Memory&  mem, const Value&  rhs) const
{
  return Value(dereference(mem).get_integer()&rhs.dereference(mem).get_integer());
}


Value
Value::
operate_bit_xor(Memory&  mem, const Value&  rhs) const
{
  return Value(dereference(mem).get_integer()^rhs.dereference(mem).get_integer());
}


Value
Value::
operate_shl(Memory&  mem, const Value&  rhs) const
{
  return Value(dereference(mem).get_integer()<<rhs.dereference(mem).get_integer());
}


Value
Value::
operate_shr(Memory&  mem, const Value&  rhs) const
{
  return Value(dereference(mem).get_integer()>>rhs.dereference(mem).get_integer());
}




Value
Value::
operate_add_assign(Memory&  mem, const Value&  rhs)
{
  return Value(dereference(mem).get_integer() += rhs.dereference(mem).get_integer());
}


Value
Value::
operate_sub_assign(Memory&  mem, const Value&  rhs)
{
  return Value(dereference(mem).get_integer() -= rhs.dereference(mem).get_integer());
}


Value
Value::
operate_mul_assign(Memory&  mem, const Value&  rhs)
{
  return Value(dereference(mem).get_integer() *= rhs.dereference(mem).get_integer());
}


Value
Value::
operate_div_assign(Memory&  mem, const Value&  rhs)
{
  return Value(dereference(mem).get_integer() /= rhs.dereference(mem).get_integer());
}


Value
Value::
operate_rem_assign(Memory&  mem, const Value&  rhs)
{
  return Value(dereference(mem).get_integer() %= rhs.dereference(mem).get_integer());
}


Value
Value::
operate_bit_or_assign(Memory&  mem, const Value&  rhs)
{
  return Value(dereference(mem).get_integer() |= rhs.dereference(mem).get_integer());
}


Value
Value::
operate_bit_and_assign(Memory&  mem, const Value&  rhs)
{
  return Value(dereference(mem).get_integer() &= rhs.dereference(mem).get_integer());
}


Value
Value::
operate_bit_xor_assign(Memory&  mem, const Value&  rhs)
{
  return Value(dereference(mem).get_integer() ^= rhs.dereference(mem).get_integer());
}


Value
Value::
operate_shl_assign(Memory&  mem, const Value&  rhs)
{
  return Value(dereference(mem).get_integer() <<= rhs.dereference(mem).get_integer());
}


Value
Value::
operate_shr_assign(Memory&  mem, const Value&  rhs)
{
  return Value(dereference(mem).get_integer() >>= rhs.dereference(mem).get_integer());
}


Value
Value::
operate_assign(Memory&  mem, const Value&  rhs)
{
    if(kind == ValueKind::reference)
    {
      dereference(mem) = rhs.dereference(mem);
    }

  else
    {
      printf("参照型でない値に代入しようとしています\n");

      return Value(ValueKind::undefined);
    }


  return Value(*this);
}




Value
Value::
operate_eq(Memory&  mem, const Value&  rhs) const
{
  return Value(dereference(mem).get_integer() == rhs.dereference(mem).get_integer());
}


Value
Value::
operate_neq(Memory&  mem, const Value&  rhs) const
{
  return Value(dereference(mem).get_integer() != rhs.dereference(mem).get_integer());
}


Value
Value::
operate_lt(Memory&  mem, const Value&  rhs) const
{
  return Value(dereference(mem).get_integer() < rhs.dereference(mem).get_integer());
}


Value
Value::
operate_lteq(Memory&  mem, const Value&  rhs) const
{
  return Value(dereference(mem).get_integer() <= rhs.dereference(mem).get_integer());
}


Value
Value::
operate_gt(Memory&  mem, const Value&  rhs) const
{
  return Value(dereference(mem).get_integer() > rhs.dereference(mem).get_integer());
}


Value
Value::
operate_gteq(Memory&  mem, const Value&  rhs) const
{
  return Value(dereference(mem).get_integer() >= rhs.dereference(mem).get_integer());
}


Value
Value::
operate_logical_or(Memory&  mem, const Value&  rhs) const
{
  return Value(dereference(mem).get_integer() || rhs.dereference(mem).get_integer());
}


Value
Value::
operate_logical_and(Memory&  mem, const Value&  rhs) const
{
  return Value(dereference(mem).get_integer() && rhs.dereference(mem).get_integer());
}






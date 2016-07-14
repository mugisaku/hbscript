#include"hbs_value.hpp"
#include"hbs_expression_node.hpp"
#include"hbs_calling.hpp"




void
Value::
reset(ValueKind  k)
{
  clear();
  kind = k;
}


void
Value::
reset(int  i)
{
  clear();

  kind = ValueKind::integer;

  data.i = i;
}


void
Value::
reset(bool  b)
{
  clear();

  kind = ValueKind::boolean;

  data.i = b? 1:0;
}


void
Value::
reset(std::string*  s_)
{
  clear();

  kind = ValueKind::string;

  data.s = s_;
}


void
Value::
reset(Function*  fn)
{
  clear();

  kind = ValueKind::function;

  data.fn = fn;
}


void
Value::
reset(const Pointer&  ptr)
{
  clear();

  kind = ValueKind::pointer;

  data.i = ptr;
}


void
Value::
reset(const Reference&  ref)
{
  clear();

  kind = ValueKind::reference;

  data.i = ref.pointer;
}





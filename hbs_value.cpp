#include"hbs_value.hpp"
#include"hbs_expression_node.hpp"
#include"hbs_function.hpp"
#include"hbs_structure.hpp"
#include"hbs_memory.hpp"
#include"hbs_context.hpp"




const Value
Value::
undefined(ValueKind::undefined);


Value::Value(ValueKind  k): kind(k){}
Value::Value(int                 i): kind(ValueKind::null){reset(i);}
Value::Value(bool                b): kind(ValueKind::null){reset(b);}
Value::Value(std::string*       s_): kind(ValueKind::null){reset(s_);}
Value::Value(Function*          fn): kind(ValueKind::null){reset(fn);}
Value::Value(expression::Node*  expr): kind(ValueKind::null){reset(expr);}
Value::Value(const Pointer&    ptr): kind(ValueKind::null){reset(ptr);}
Value::Value(const Reference&  ref): kind(ValueKind::null){reset(ref);}
Value::Value(const Value&   rhs)         : kind(ValueKind::null){*this =          (rhs);}
Value::Value(      Value&&  rhs) noexcept: kind(ValueKind::null){*this = std::move(rhs);}


Value::
~Value()
{
  clear();
}




Value&
Value::
operator=(const Value&   rhs)
{
  clear();

  kind = rhs.kind;

    switch(kind)
    {
      case(ValueKind::integer):
      case(ValueKind::pointer):
      case(ValueKind::boolean):
      case(ValueKind::reference):
        data.i = rhs.data.i;
        break;
      case(ValueKind::string):
        data.s = new std::string(*rhs.data.s);
        break;
      case(ValueKind::function):
//        data.fn = new Function(*rhs.data.fn);
        break;
      case(ValueKind::array):
        break;
      case(ValueKind::structure):
        data.st = new Structure(*rhs.data.st);
        break;
      case(ValueKind::expression):
        data.expr = new expression::Node(*rhs.data.expr);
        break;
      default:;
    }


  return *this;
}


Value&
Value::
operator=(Value&&  rhs)
{
  clear();

  kind = rhs.kind                  ;
         rhs.kind = ValueKind::null;

  data = rhs.data;

  return *this;
}




void
Value::
clear()
{
    switch(kind)
    {
      case(ValueKind::integer):
      case(ValueKind::pointer):
      case(ValueKind::boolean):
      case(ValueKind::reference):
      case(ValueKind::array):
        break;
      case(ValueKind::structure):
        delete data.st;
        break;
      case(ValueKind::string):
        delete data.s;
        break;
      case(ValueKind::function):
        delete data.fn;
        break;
      case(ValueKind::expression):
        delete data.expr;
        break;
      default:;
    }


  kind = ValueKind::null;
}


const int&   Value::get_integer() const{return data.i;}
int&         Value::get_integer()      {return data.i;}


Value&
Value::
dereference(Memory&  mem)
{
  return((kind == ValueKind::reference)? mem[data.i]:*this);
}


const Value&
Value::
dereference(Memory&  mem) const
{
  return((kind == ValueKind::reference)? mem[data.i]:*this);
}


void
Value::
print(const Memory&  mem) const
{
    switch(kind)
    {
      case(ValueKind::null):
        printf("null");
        break;
      case(ValueKind::void_):
        printf("void");
        break;
      case(ValueKind::undefined):
        printf("undefined");
        break;
      case(ValueKind::reference):
        printf("REF(%d)->",data.i);
        mem[data.i].print(mem);
        break;
      case(ValueKind::integer):
        printf("INT(%d)",data.i);
        break;
      case(ValueKind::pointer):
        printf("PTR(%d)",data.i);
        break;
      case(ValueKind::boolean):
        printf("%s",data.i? "true":"false");
        break;
      case(ValueKind::string):
        printf("\"%s\"",data.s->data());
        break;
      case(ValueKind::function):
        printf("function");
        data.fn->print(mem);
        break;
      case(ValueKind::structure):
        data.st->print();
        break;
      case(ValueKind::expression):
        printf("expr ");
        data.expr->print(mem);
        break;
      default:;
        report;
    }
}






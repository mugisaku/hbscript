#include"hbs_expression_element.hpp"
#include"hbs_expression_node.hpp"
#include"hbs_calling.hpp"
#include"hbs_function.hpp"




namespace expression{




Element::Element(ElementKind  k): kind(k){}
Element::Element(Operand*  operand): kind(ElementKind::null){reset(operand);}
Element::Element(UnaryOperator  unop): kind(ElementKind::null){reset(unop);}
Element::Element(BinaryOperator  binop, bool  assign): kind(ElementKind::null){reset(binop,assign);}
Element::Element(const Element&   rhs): kind(ElementKind::null){*this =          (rhs);}
Element::Element(      Element&&  rhs) noexcept: kind(ElementKind::null){*this = std::move(rhs);}


Element::
~Element()
{
  clear();
}




Element&
Element::
operator=(const Element&  rhs)
{
  clear();

  kind = rhs.kind;

    switch(kind)
    {
      case(ElementKind::operand):
        data.operand = new Operand(*rhs.data.operand);
        break;
      case(ElementKind::unary_operator):
        data.unop = rhs.data.unop;
        break;
      case(ElementKind::binary_operator):
      case(ElementKind::assign_operator):
        data.binop = rhs.data.binop;
        break;
      default:;
    }


  return *this;
}


Element&
Element::
operator=(Element&&  rhs)
{
  clear();

  kind = rhs.kind                    ;
         rhs.kind = ElementKind::null;

  data = rhs.data;

  return *this;
}




void
Element::
clear()
{
    if(kind == ElementKind::operand)
    {
      delete data.operand;
    }


  kind = ElementKind::null;
}




void
Element::
reset(Operand*  operand)
{
  clear();

  kind = ElementKind::operand;

  data.operand = operand;
}


void
Element::
reset(UnaryOperator  unop)
{
  clear();

  kind = ElementKind::unary_operator;

  data.unop = unop;
}


void
Element::
reset(BinaryOperator  binop, bool   assign)
{
  clear();

  kind = assign? ElementKind::assign_operator:ElementKind::binary_operator;

  data.binop = binop;
}


bool
Element::
test(OperandKind  k) const
{
    if(kind == ElementKind::operand)
    {
      return(data.operand->kind == k);
    }


  return false;
}


namespace{
const char*
get_string(UnaryOperator  op)
{
    switch(op)
    {
      case(UnaryOperator::logical_not): return"!";
      case(UnaryOperator::bit_not    ): return"~";
      case(UnaryOperator::invrt      ): return"-";
      case(UnaryOperator::new_       ): return"new ";
      case(UnaryOperator::delete_    ): return"delete ";

      default:;
    }


  return "<UNKNOWN OPERATOR>";
}


const char*
get_string(BinaryOperator  op, bool  assign)
{
    switch(op)
    {
      case(BinaryOperator::nop           ): return assign? "=": "NOP";
      case(BinaryOperator::add           ): return assign? "+=":  "+";
      case(BinaryOperator::sub           ): return assign? "-=":  "-";
      case(BinaryOperator::mul           ): return assign? "*=":  "*";
      case(BinaryOperator::div           ): return assign? "/=":  "/";
      case(BinaryOperator::rem           ): return assign? "%=":  "%";
      case(BinaryOperator::bit_or        ): return assign? "|=":  "|";
      case(BinaryOperator::bit_and       ): return assign? "&=":  "&";
      case(BinaryOperator::bit_xor       ): return assign? "^=":  "^";
      case(BinaryOperator::shl           ): return assign? "<<=":"<<";
      case(BinaryOperator::shr           ): return assign? ">>=":">>";

      case(BinaryOperator::eq            ): return"==";
      case(BinaryOperator::neq           ): return"!=";
      case(BinaryOperator::lt            ): return"<";
      case(BinaryOperator::lteq          ): return"<=";
      case(BinaryOperator::gt            ): return">";
      case(BinaryOperator::gteq          ): return">=";
      case(BinaryOperator::logical_or    ): return"||";
      case(BinaryOperator::logical_and   ): return"&&";
      case(BinaryOperator::memb          ): return".";

      default:;
    }


  return "<UNKNOWN OPERATOR>";
}
}


void
Element::
print(const Memory&  mem) const
{
    switch(kind)
    {
      case(ElementKind::null):
        printf("null");
        break;
      case(ElementKind::operand):
        data.operand->print(mem);
        break;
      case(ElementKind::unary_operator):
        printf("%s",get_string(data.unop));
        break;
      case(ElementKind::binary_operator):
        printf("%s",get_string(data.binop,false));
        break;
      case(ElementKind::assign_operator):
        printf("%s",get_string(data.binop,true));
        break;
      default:;
    }
}





}






#include"hbs_expression_node.hpp"
#include"hbs_block.hpp"
#include"hbs_context.hpp"
#include"hbs_structure.hpp"




namespace expression{


Node::
Node():
left(nullptr),
right(nullptr)
{
}


Node::
Node(const Element&  el):
left(nullptr),
right(nullptr)
{
  *this = el;
}


Node::
Node(Element&&  el):
left(nullptr),
right(nullptr)
{
  *this = std::move(el);
}


Node::
Node(Node&&  rhs) noexcept:
left(nullptr),
right(nullptr)
{
  *this = std::move(rhs);
}


Node::
Node(const Node&  rhs):
left(nullptr),
right(nullptr)
{
  *this = rhs;
}


Node::
~Node()
{
  clear();
}




Node&
Node::
operator=(const Node&  rhs)
{
  clear();

  element = rhs.element;

   left = rhs.left ? new Node(*rhs.left ):nullptr;
  right = rhs.right? new Node(*rhs.right):nullptr;

  return *this;
}


Node&
Node::
operator=(Node&&  rhs)
{
  clear();

  element = std::move(rhs.element);

  std::swap( left, rhs.left);
  std::swap(right,rhs.right);

  return *this;
}


Node&
Node::
operator=(const Element&  el)
{
  clear();

  element = el;

  return *this;
}


Node&
Node::
operator=(Element&&  el)
{
  clear();

  element = std::move(el);

  return *this;
}


Node::
operator bool() const
{
  return(element.kind != ElementKind::null);
}


void
Node::
clear()
{
  element.clear();

  delete left          ;
         left = nullptr;

  delete right          ;
         right = nullptr;
}


bool
Node::
test_leaf() const
{
  return(!left && !right);
}


namespace
{
Value
get_member(Value&  lhs, const std::string&  id, Memory&  mem)
{
    if(lhs.kind == ValueKind::pointer)
    {
      auto&  v = mem[lhs.data.i];

        if(v.kind != ValueKind::structure)
        {
          report;
        }


      auto&  memb = v.data.st->get_member(id);

      return Value(Reference(memb.pointer));
    }

  else
    if(lhs.kind == ValueKind::structure)
    {
      auto&  memb = lhs.data.st->get_member(id);

      return Value(Reference(memb.pointer));
    }

  else
    {
      report;
    }


  return Value::undefined;
}
}


Value
Node::
get_value(Context&  ctx) const
{
    if(element.kind == ElementKind::operand)
    {
      return element.data.operand->get_value(ctx);
    }


  Memory&  mem = ctx.get_memory();

  auto  a = left->get_value(ctx);

    if(element.kind == ElementKind::unary_operator)
    {
        switch(element.data.unop)
        {
          case(UnaryOperator::indir      ): return a.indirect(mem);
          case(UnaryOperator::addr       ): return a.get_address(mem);
          case(UnaryOperator::logical_not): return a.logical_not(mem);
          case(UnaryOperator::bit_not    ): return a.bit_not(mem);
          case(UnaryOperator::invrt      ): return a.invert(mem);
          case(UnaryOperator::new_       ): return a.new_(mem);
          case(UnaryOperator::delete_    ): return a.delete_(mem);
        }
    }


    if((element.kind       == ElementKind::binary_operator) &&
       (element.data.binop == BinaryOperator::memb))
    {
        if(!right                                                         ||
           (right->element.kind               != ElementKind::operand   ) ||
           (right->element.data.operand->kind != OperandKind::identifier))
        {
          printf("メンバー参照は、右辺値が識別子でなくてはなりません\n");
        }


      return get_member(a.dereference(mem),*right->element.data.operand->data.str,mem);
    }


  auto  b = right->get_value(ctx);

    if(element.kind == ElementKind::binary_operator)
    {
        switch(element.data.binop)
        {
          case(BinaryOperator::mul           ): return a.operate_mul(mem,b);
          case(BinaryOperator::div           ): return a.operate_div(mem,b);
          case(BinaryOperator::rem           ): return a.operate_rem(mem,b);

          case(BinaryOperator::add           ): return a.operate_add(mem,b);
          case(BinaryOperator::sub           ): return a.operate_sub(mem,b);

          case(BinaryOperator::shl           ): return a.operate_shl(mem,b);
          case(BinaryOperator::shr           ): return a.operate_shr(mem,b);

          case(BinaryOperator::lt            ): return a.operate_lt(mem,b);
          case(BinaryOperator::lteq          ): return a.operate_lteq(mem,b);
          case(BinaryOperator::gt            ): return a.operate_gt(mem,b);
          case(BinaryOperator::gteq          ): return a.operate_gteq(mem,b);

          case(BinaryOperator::eq            ): return a.operate_eq(mem,b);
          case(BinaryOperator::neq           ): return a.operate_neq(mem,b);


          case(BinaryOperator::bit_and       ): return a.operate_bit_and(mem,b);
          case(BinaryOperator::bit_or        ): return a.operate_bit_or(mem,b);
          case(BinaryOperator::bit_xor       ): return a.operate_bit_xor(mem,b);

          case(BinaryOperator::logical_and   ): return a.operate_logical_and(mem,b);
          case(BinaryOperator::logical_or    ): return a.operate_logical_or(mem,b);
        }
    }

  else
    if(element.kind == ElementKind::assign_operator)
    {
        switch(element.data.binop)
        {
          case(BinaryOperator::nop           ): return a.operate_assign(mem,b);
          case(BinaryOperator::mul           ): return a.operate_mul_assign(mem,b);
          case(BinaryOperator::div           ): return a.operate_div_assign(mem,b);
          case(BinaryOperator::rem           ): return a.operate_rem_assign(mem,b);

          case(BinaryOperator::add           ): return a.operate_add_assign(mem,b);
          case(BinaryOperator::sub           ): return a.operate_sub_assign(mem,b);

          case(BinaryOperator::shl           ): return a.operate_shl_assign(mem,b);
          case(BinaryOperator::shr           ): return a.operate_shr_assign(mem,b);

          case(BinaryOperator::bit_and       ): return a.operate_bit_and_assign(mem,b);
          case(BinaryOperator::bit_or        ): return a.operate_bit_or_assign(mem,b);
          case(BinaryOperator::bit_xor       ): return a.operate_bit_xor_assign(mem,b);
        }
    }


  return Value(ValueKind::undefined);
}


void
Node::
print(const Memory&  mem) const
{
    if(element.kind == ElementKind::null)
    {
      return;
    }


    if(element.kind == ElementKind::operand)
    {
      element.print(mem);

      return;
    }


    if(element.kind == ElementKind::unary_operator)
    {
      element.print(mem);
    }


    if(left)
    {
        if(!left->test_leaf())
        {
          printf("(");
        }


      left->print(mem);

        if(!left->test_leaf())
        {
          printf(")");
        }
    }


    if((element.kind == ElementKind::binary_operator) ||
       (element.kind == ElementKind::assign_operator))
    {
      element.print(mem);
    }


    if(right)
    {
        if(!right->test_leaf())
        {
          printf("(");
        }


      right->print(mem);

        if(!right->test_leaf())
        {
          printf(")");
        }
    }
}


}






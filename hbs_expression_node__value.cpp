#include"hbs_expression_node.hpp"
#include"hbs_block.hpp"
#include"hbs_context.hpp"
#include"hbs_structure.hpp"




namespace expression{


namespace
{
Value
get_member(Value&  lhs, const std::string&  id, Memory&  mem)
{
    if(lhs.kind == ValueKind::structure)
    {
      auto&  memb = lhs.data.st->get_member(id);

      return Value(Reference(memb.pointer));
    }

  else
    {
      report;

      printf("%d\n",(int)lhs.kind);
    }


  return Value::undefined;
}


Value
operate_binary(Context&  ctx, Value&  a, BinaryOperator  op, const Node*  right)
{
  Memory&  mem = ctx.get_memory();

    if(op == BinaryOperator::memb)
    {
        if((right->element.kind               != ElementKind::operand   ) ||
           (right->element.data.operand->kind != OperandKind::identifier))
        {
          printf("メンバー参照は、右辺値が識別子でなくてはなりません\n");
        }


      return get_member(a.dereference(mem),*right->element.data.operand->data.str,mem);
    }


  auto  b = right->get_value(ctx);

    switch(op)
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
          case(UnaryOperator::logical_not): return a.logical_not(mem);
          case(UnaryOperator::bit_not    ): return a.bit_not(mem);
          case(UnaryOperator::invrt      ): return a.invert(mem);
          case(UnaryOperator::new_       ): return a.new_(ctx);
          case(UnaryOperator::delete_    ): return a.delete_(mem);
        }
    }


    if(element.kind == ElementKind::binary_operator)
    {
      return operate_binary(ctx,a,element.data.binop,right);
    }

  else
    if(element.kind == ElementKind::assign_operator)
    {
        if(a.kind != ValueKind::reference)
        {
          printf("代入演算の右辺値は参照でなければなりません");
        }


      auto  b = right->get_value(ctx);

      auto&  dst = a.dereference(mem).data.i;
      auto&  src = b.dereference(mem).data.i;

        switch(element.data.binop)
        {
          case(BinaryOperator::nop    ): dst   = src;break;
          case(BinaryOperator::mul    ): dst  *= src;break;
          case(BinaryOperator::div    ): dst  /= src;break;
          case(BinaryOperator::rem    ): dst  %= src;break;
          case(BinaryOperator::add    ): dst  += src;break;
          case(BinaryOperator::sub    ): dst  -= src;break;
          case(BinaryOperator::shl    ): dst <<= src;break;
          case(BinaryOperator::shr    ): dst >>= src;break;
          case(BinaryOperator::bit_and): dst  &= src;break;
          case(BinaryOperator::bit_or ): dst  |= src;break;
          case(BinaryOperator::bit_xor): dst  ^= src;break;
        }


      return Value(dst);
    }


  return Value(ValueKind::undefined);
}


}






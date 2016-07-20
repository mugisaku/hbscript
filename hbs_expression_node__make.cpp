#include"hbs_expression_node.hpp"
#include<list>




namespace expression{


namespace{
int
get_priority(const Element&  el)
{
    switch(el.kind)
    {
      case(ElementKind::unary_operator):
          switch(el.data.unop)
          {
            case(UnaryOperator::logical_not):
            case(UnaryOperator::bit_not    ):
            case(UnaryOperator::invrt      ):
            case(UnaryOperator::new_       ):
            case(UnaryOperator::delete_    ): return 0x80;
          }
        break;
      case(ElementKind::binary_operator):
          switch(el.data.binop)
          {
            case(BinaryOperator::memb): return 0x90;

            case(BinaryOperator::mul        ):
            case(BinaryOperator::div        ):
            case(BinaryOperator::rem        ): return 0x70;

            case(BinaryOperator::add        ):
            case(BinaryOperator::sub        ): return 0x60;

            case(BinaryOperator::shl        ):
            case(BinaryOperator::shr        ): return 0x50;

            case(BinaryOperator::lt         ):
            case(BinaryOperator::lteq       ):
            case(BinaryOperator::gt         ):
            case(BinaryOperator::gteq       ): return 0x40;

            case(BinaryOperator::eq         ):
            case(BinaryOperator::neq        ): return 0x30;


            case(BinaryOperator::bit_and    ): return 0x22;
            case(BinaryOperator::bit_or     ): return 0x21;
            case(BinaryOperator::bit_xor    ): return 0x20;

            case(BinaryOperator::logical_and): return 0x11;
            case(BinaryOperator::logical_or ): return 0x10;
          }
        break;
      case(ElementKind::assign_operator):
          switch(el.data.binop)
          {
            case(BinaryOperator::add    ):
            case(BinaryOperator::sub    ):
            case(BinaryOperator::mul    ):
            case(BinaryOperator::div    ):
            case(BinaryOperator::rem    ):
            case(BinaryOperator::bit_or ):
            case(BinaryOperator::bit_and):
            case(BinaryOperator::bit_xor):
            case(BinaryOperator::shl    ):
            case(BinaryOperator::shr    ):
            case(BinaryOperator::nop    ): return 0x00;

            default:;
          }
        break;
    }


  return 0;
}


Node*
make_tree(std::list<Node*>&  ls)
{
  static Node  null_node;

  std::vector<Node*>  operand_buf;

    while(ls.size())
    {
      auto  nd = ls.front();
                 ls.pop_front();

        if(nd->element.kind == ElementKind::operand)
        {
          operand_buf.emplace_back(nd);
        }

      else
        if(nd->element.kind == ElementKind::unary_operator)
        {
            if(operand_buf.size() < 1)
            {
              report;
              return &null_node;
            }


          nd->left = operand_buf.back();

          operand_buf.pop_back();
          operand_buf.emplace_back(nd);
        }

      else
        if((nd->element.kind == ElementKind::binary_operator) ||
           (nd->element.kind == ElementKind::assign_operator))
        {
            if(operand_buf.size() < 2)
            {
              report;
              return &null_node;
            }


          nd->right = operand_buf.back();

          operand_buf.pop_back();

          nd->left = operand_buf.back();

          operand_buf.pop_back();


          operand_buf.emplace_back(nd);
        }
    }


    if(operand_buf.size() != 1)
    {
      report;
      return &null_node;
    }


  return operand_buf.front();
}


}


void
Node::
make(ElementList&&  src)
{
  ElementList  ls(std::move(src));

  std::list<Node*>          node_stack;
  std::vector<Element>  operator_stack;

    for(auto&  el: ls)
    {
        if((el.kind == ElementKind::unary_operator ) ||
           (el.kind == ElementKind::binary_operator) ||
           (el.kind == ElementKind::assign_operator))
        {
          int  now = get_priority(el);

            while(operator_stack.size())
            {
              auto&  tail = operator_stack.back();

              int  last = get_priority(tail);

                if(now <= last)
                {
                  node_stack.emplace_back(new Node(std::move(tail)));

                  operator_stack.pop_back();
                }

              else
                {
                  break;
                }
            }


          operator_stack.emplace_back(std::move(el));
        }

      else
        if(el.kind == ElementKind::operand)
        {
          node_stack.emplace_back(new Node(std::move(el)));
        }
    }


    while(operator_stack.size())
    {
      auto  nd = new Node(std::move(operator_stack.back()));

      node_stack.emplace_back(nd);

      operator_stack.pop_back();
    }


  *this = Element(new Operand(make_tree(node_stack)));
}


}





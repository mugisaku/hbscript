#include"hbs_expression_node.hpp"




namespace expression{




namespace{
Element
read_binary_operator(const mkf::Node&  base)
{
  mkf::Cursor  cur(base);

    while(!cur.test_ended())
    {
      auto&  nd = cur.get();

           if(nd == "+" ){return Element(BinaryOperator::add);}
      else if(nd == "-" ){return Element(BinaryOperator::sub);}
      else if(nd == "*" ){return Element(BinaryOperator::mul);}
      else if(nd == "/" ){return Element(BinaryOperator::div);}
      else if(nd == "%" ){return Element(BinaryOperator::rem);}
      else if(nd == "<<"){return Element(BinaryOperator::shl);}
      else if(nd == ">>"){return Element(BinaryOperator::shr);}
      else if(nd == "=="){return Element(BinaryOperator::eq);}
      else if(nd == "!="){return Element(BinaryOperator::neq);}
      else if(nd == "<" ){return Element(BinaryOperator::lt);}
      else if(nd == "<="){return Element(BinaryOperator::lteq);}
      else if(nd == ">" ){return Element(BinaryOperator::gt);}
      else if(nd == ">="){return Element(BinaryOperator::gteq);}
      else if(nd == "|" ){return Element(BinaryOperator::bit_or);}
      else if(nd == "&" ){return Element(BinaryOperator::bit_and);}
      else if(nd == "^" ){return Element(BinaryOperator::bit_xor);}
      else if(nd == "&&"){return Element(BinaryOperator::logical_and);}
      else if(nd == "||"){return Element(BinaryOperator::logical_or);}
      else if(nd == "." ){return Element(BinaryOperator::memb);}
      else if(nd == "=" ){return Element(BinaryOperator::nop,true);}
      else if(nd == "+="){return Element(BinaryOperator::add,true);}
      else if(nd == "-="){return Element(BinaryOperator::sub,true);}
      else if(nd == "*="){return Element(BinaryOperator::mul,true);}
      else if(nd == "/="){return Element(BinaryOperator::div,true);}
      else if(nd == "%="){return Element(BinaryOperator::rem,true);}
      else if(nd == "<<="){return Element(BinaryOperator::shl,true);}
      else if(nd == ">>="){return Element(BinaryOperator::shr,true);}
      else if(nd == "|="){return Element(BinaryOperator::bit_or,true);}
      else if(nd == "&="){return Element(BinaryOperator::bit_and,true);}
      else if(nd == "^="){return Element(BinaryOperator::bit_xor,true);}

      cur.advance();
    }


  return Element();
}


Element
read_unary_operator(const mkf::Node&  base)
{
  mkf::Cursor  cur(base);

    while(!cur.test_ended())
    {
      auto&  nd = cur.get();

           if(nd == "~"        ){return UnaryOperator::bit_not    ;}
      else if(nd == "-"        ){return UnaryOperator::invrt      ;}
      else if(nd == "!"        ){return UnaryOperator::logical_not;}
      else if(nd == "new"      ){return UnaryOperator::new_       ;}
      else if(nd == "delete"   ){return UnaryOperator::delete_    ;}


      cur.advance();
    }


  return Element();
}


void
read_unary_operand(const mkf::Node&  base, Memory&  mem, ElementList&  ls)
{
  mkf::Cursor  cur(base);

    while(!cur.test_ended())
    {
      auto&  nd = cur.get();

        if(nd == "unary_operator")
        {
          ls.emplace_back(read_unary_operator(nd));
        }

      else
        if(nd == "operand")
        {
          auto  op = new Operand;

          op->read(nd,mem);

          ls.emplace_back(op);
        }

      else
        if(nd == "expression")
        {
          auto  expr = new Node;

          expr->read(nd,mem);

          ls.emplace_back(new Operand(expr));
        }


      cur.advance();
    }
}


void
read_binary_operand(const mkf::Node&  base, Memory&  mem, ElementList&  ls)
{
  mkf::Cursor  cur(base);

    while(!cur.test_ended())
    {
      auto&  nd = cur.get();

        if(nd == "binary_operator")
        {
          ls.emplace_back(read_binary_operator(nd));
        }

      else
        if(nd == "unary_operand")
        {
          read_unary_operand(nd,mem,ls);
        }


      cur.advance();
    }
}



}




void
Node::
read(const mkf::Node&  base, Memory&  mem)
{
  mkf::Cursor  cur(base);

  ElementList  ls;

    while(!cur.test_ended())
    {
      auto&  nd = cur.get();

        if(nd == "binary_operand")
        {
          read_binary_operand(nd,mem,ls);
        }

      else
        if(nd == "unary_operand")
        {
          read_unary_operand(nd,mem,ls);
        }


      cur.advance();
    }


  make(std::move(ls));
}


}





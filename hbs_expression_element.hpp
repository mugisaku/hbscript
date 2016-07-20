#ifndef HBS_EXPRESSION_ELEMENT_HPP_INCLUDED
#define HBS_EXPRESSION_ELEMENT_HPP_INCLUDED


#include"hbs_value.hpp"
#include"hbs_expression_operand.hpp"
#include<vector>


namespace expression{


struct Node;


enum class
ElementKind
{
  null,

  operand,

  unary_operator,
  binary_operator,
  assign_operator,

};


enum class
BinaryOperator
{
  nop,
  add,
  sub,
  mul,
  div,
  rem,
  bit_or,
  bit_and,
  bit_xor,
  shl,
  shr,
  logical_or,
  logical_and,

  eq,
  neq,
  lt,
  lteq,
  gt,
  gteq,

  memb,

};


enum class
UnaryOperator
{
  nop,
  invrt,
  bit_not,
  logical_not,
  new_,
  delete_,

};


struct
Element
{
  ElementKind  kind;

  union{
    UnaryOperator     unop;
    BinaryOperator   binop;

    Operand*   operand;

  } data;


  Element(ElementKind  k=ElementKind::null);
  Element(Operand*  operand);
  Element(UnaryOperator  unop);
  Element(BinaryOperator  binop, bool  assign=false);
  Element(const Element&   rhs);
  Element(      Element&&  rhs) noexcept;
 ~Element();


  Element&  operator=(const Element&   rhs);
  Element&  operator=(      Element&&  rhs);


  void  clear();

  bool  test(OperandKind  k) const;

  void  reset(ElementKind  k=ElementKind::null);
  void  reset(Operand*   operand);
  void  reset(UnaryOperator  unop);
  void  reset(BinaryOperator  binop, bool  assign=false);


  void  print(const Memory&  mem) const;

};


using ElementList = std::vector<Element>;


}


#endif





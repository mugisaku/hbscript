#ifndef HBS_EXPRESSION_OPERAND_HPP_INCLUDED
#define HBS_EXPRESSION_OPERAND_HPP_INCLUDED


#include"libmkf/mkf_node.hpp"
#include"libmkf/mkf_cursor.hpp"
#include"hbs_value.hpp"
#include"hbs_context.hpp"




struct Calling;
struct Accessing;


namespace expression{


struct Node;


enum class
OperandKind
{
  null,

  identifier,
  calling,
  tree,
  value,

};


struct
Operand
{
  OperandKind  kind;

  union{
    std::string*  str;
    Calling*      cal;
    Accessing*    acs;
    Node*         nod;
    Value*        val;

  } data;


  Operand();
  Operand(Calling*  cal);
  Operand(Node*  nod);
  Operand(std::string*  str);
  Operand(Value*        val);
  Operand(const Operand&   rhs);
  Operand(      Operand&&  rhs);
 ~Operand();


  Operand&  operator=(const Operand&   rhs);
  Operand&  operator=(      Operand&&  rhs);


  void  clear();

  bool  test(ValueKind  k) const;

  void  reset(Calling*  cal);
  void  reset(Node*  nod);
  void  reset(std::string*  str);
  void  reset(Value*  val);

  void  print(const Memory&  mem) const;


  Value  get_value(Context&  ctx) const;

  void  read(const mkf::Node&  src);

};


}


#endif





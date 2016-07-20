#ifndef HBSCRIPT_FORSTATEMENT_HPP_INCLUDED
#define HBSCRIPT_FORSTATEMENT_HPP_INCLUDED


#include"hbs_statement.hpp"
#include"hbs_conditionalblock.hpp"
#include"hbs_vardecl.hpp"


class
ForStatement: public  Block
{
  const VarDecl*  vardecl;

  const expression::Node*  iteration;

  const ConditionalBlock*  conditional_block;

public:
  bool  get_condition_value(Context&  ctx) const;
  void              iterate(Context&  ctx) const;

  void  print(const Memory&  mem);

  void  read(const mkf::Node&  src, Memory&  mem, int  depth);
  void  read_condition(const mkf::Node&  src);
  void  read_iteration(const mkf::Node&  src);

};




#endif





#ifndef HBSCRIPT_CONDITIONALBLOCK_HPP_INCLUDED
#define HBSCRIPT_CONDITIONALBLOCK_HPP_INCLUDED


#include"hbs_block.hpp"




class
ConditionalBlock: public  Block
{
  expression::Node  condition;

public:
  void  change_condition(expression::Node&&  cond);

  const expression::Node&  get_condition() const;

  bool  get_condition_value(Context&  ctx) const;

  void  print(const Memory&  mem) const;

  void  read(const mkf::Node&   src, Memory&  mem, int  depth);

};


#endif





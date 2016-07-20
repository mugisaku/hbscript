#ifndef HBSCRIPT_IFSTATEMENT_HPP_INCLUDED
#define HBSCRIPT_IFSTATEMENT_HPP_INCLUDED


#include"hbs_statement.hpp"
#include"hbs_conditionalblock.hpp"


struct
IfStatement
{
  ConditionalBlock  if_block;

  std::vector<ConditionalBlock>  elseif_block_list;

  Block  else_block;


  void  print(const Memory&  mem);

  void  read(const mkf::Node&  src, Memory&  mem, int  depth);
  void  read_conditional_block(ConditionalBlock&  blk, const mkf::Node&  src, Memory&  mem, int  depth);
  void  read_else_block(const mkf::Node&  src, Memory&  mem, int  depth);

};




#endif





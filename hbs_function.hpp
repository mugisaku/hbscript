#ifndef HBSCRIPT_FUNCTION_HPP_INCLUDED
#define HBSCRIPT_FUNCTION_HPP_INCLUDED


#include"hbs_block.hpp"
#include"hbs_calling.hpp"




using ParameterList = std::vector<Parameter>;


struct
Function: public Block
{
  ParameterList  parameters;

  bool  reference_sign;


  Function();

  Value  operator()(Context&  ctx) const;

  void  print(const Memory&  mem) const;


  void            read(const mkf::Node&  src, Memory&  mem, int  depth);
  void  read_parameter(const mkf::Node&  src);

};




#endif





#ifndef HBSCRIPT_VARDECL_HPP_INCLUDED
#define HBSCRIPT_VARDECL_HPP_INCLUDED


#include"hbs_parameter.hpp"
#include"hbs_statement.hpp"


struct
VarDecl: public Parameter
{
  expression::Node  initializer;

  void  print(const Memory&  mem) const;

  void  read(const mkf::Node&  src, Memory&  mem);

};




#endif





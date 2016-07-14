#ifndef HBSCRIPT_OBJECT_HPP_INCLUDED
#define HBSCRIPT_OBJECT_HPP_INCLUDED


#include"hbs_parameter.hpp"
#include"hbs_memory.hpp"
#include"hbs_value.hpp"




enum class
ObjectKind
{
  null,

  static_variable,
  auto_variable,
  reference,
  enumerator,

};


struct
Object: public Parameter
{
  ObjectKind  kind;

  int  value;


  Object(std::string&&  id, int  flags, ObjectKind  k, int  v=0);

  Value  get_value(Memory&  mem) const;

  void  print(const Memory&  mem) const;

};


using ObjectList = std::vector<Object>;


#endif





#ifndef HBSCRIPT_CALLING_HPP_INCLUDED
#define HBSCRIPT_CALLING_HPP_INCLUDED


#include<string>
#include<vector>
#include"libmkf/mkf_node.hpp"
#include"libmkf/mkf_cursor.hpp"
#include"hbs_expression_node.hpp"




using ArgumentList = std::vector<expression::Node>;


struct
Calling
{
  std::string  identifier;

  ArgumentList  arguments;

  Calling(const char*  id="", std::initializer_list<expression::Node>  args={});

  void  print(const Memory&  mem) const;

  void  read(const mkf::Node&  src, Memory&  mem);

};




#endif





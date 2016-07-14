#ifndef HBSCRIPT_BLOCK_HPP_INCLUDED
#define HBSCRIPT_BLOCK_HPP_INCLUDED


#include"libmkf/mkf_node.hpp"
#include"libmkf/mkf_cursor.hpp"
#include"libmkf/mkf_ctype.hpp"
#include"hbs_object.hpp"
#include"hbs_statement.hpp"
#include<list>




struct Context;


class
Block
{
protected:
  std::string  identifier;

  std::vector<Statement>  statement_list;

  ObjectList  static_object_list;

public:
  Pointer  make_static_object(Memory&  mem, std::string&&  id);

  const ObjectList&  get_static_object_list() const;

  void  append(Statement&&  stmt);

  void  change_identifier(std::string&&  id);

  void  print(const Memory&  mem) const;


  void  read(const mkf::Node&   src, Memory&  mem, int  depth);

};




#endif





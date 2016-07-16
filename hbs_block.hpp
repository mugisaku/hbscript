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
  StatementList  statement_list;

  ObjectList  static_object_list;

public:
  operator bool() const{return statement_list.size();}

  Pointer  make_static_object(Memory&  mem, std::string&&  id);

  const ObjectList&  get_static_object_list() const;

  const Object*  find_static_object(const std::string&  id) const;

  void  append(Statement&&  stmt);

  const StatementList&  get_statement_list() const;

  void  print(const Memory&  mem) const;


  void  read(const mkf::Node&   src, Memory&  mem, int  depth);

};


class
LabeledBlock: public Block
{
  std::string  label;

public:
  void  change_label(std::string&&  lb){label = std::move(lb);}

  const std::string&  get_label() const{return label;}

  void  print(const Memory&  mem) const
  {
    printf("%s:\n",label.data());

    Block::print(mem);
  }

};


#endif





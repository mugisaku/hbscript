#ifndef HBS_BLOCKFRAME_HPP_INCLUDED
#define HBS_BLOCKFRAME_HPP_INCLUDED


#include"hbs_block.hpp"


class
BlockFrame
{
  StatementList::const_iterator  current;
  StatementList::const_iterator      end;

  ObjectList  object_list;

public:
  const Block&  block;

  BlockFrame(const Block&  blk, ObjectList&&  objls);


  const Statement*  get_statement();

  void  make_auto_object(const std::string&  id, int  flags, const Value&  val);

        ObjectList&        get_object_list()      ;
  const ObjectList&  get_const_object_list() const;

  const Object*  find_object(const std::string&  id) const;

  void  print(const Memory&  mem) const;

};


#endif





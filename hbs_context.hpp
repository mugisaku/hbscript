#ifndef HBS_CONTEXT_HPP_INCLUDED
#define HBS_CONTEXT_HPP_INCLUDED


#include"hbs_functionframe.hpp"
#include"hbs_calling.hpp"


class
Context
{
  Memory&  memory;

  Block&  global_block;

  std::list<FunctionFrame>  functionframe_list;

  enum class LeaveStatus{
    returned,
    ended,
    broke,
    continued,
  };

public:
  Context(Memory&  mem, Block&  gblk);

  FunctionFrame&  get_top_frame();

  int  get_level() const;

        Memory&        get_memory()      ;
  const Memory&  get_const_memory() const;

  Value         call(const Function&  fn, const Calling&  cal);
  LeaveStatus  enter(const Block&  blk, ObjectList&&  objls, Value&  retval);

  void  make_auto_object(ObjectList&  buf, const std::string&  id, int  flags, const Value&  val);
  void  make_auto_object(const std::string&  id, int  flags, const Value&  val);

  void  release_auto_object(const ObjectList&  objls);

  const Object*  find_object(const std::string&  id) const;

  void  print() const;

};


#endif





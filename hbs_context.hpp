#ifndef HBS_CONTEXT_HPP_INCLUDED
#define HBS_CONTEXT_HPP_INCLUDED


#include"hbs_functionframe.hpp"
#include"hbs_calling.hpp"


struct
Context
{
  Memory&  memory;

  Block&  global_block;

  std::vector<FunctionFrame>  functionframe_list;

  Pointer  base_pointer;


  Context(Memory&  mem, Block&  gblk);

  FunctionFrame&  get_top_frame();

  int  get_level() const;

  Value   call(const Function&  fn, const Calling&  cal);
  Value  enter(const Block&  blk, ObjectList&&  objls, bool  return_reference);

  void  step();

  void  make_auto_object(ObjectList&  buf, const std::string&  id, int  flags, const Value&  val);
  void  make_auto_object(const std::string&  id, int  flags, const Value&  val);

  Object*  find_object(const std::string&  id);

  void  print() const;

};


#endif





#ifndef HBS_CONTEXT_HPP_INCLUDED
#define HBS_CONTEXT_HPP_INCLUDED


#include"hbs_object.hpp"


struct Block;
struct Function;
struct Calling;


struct
Frame
{
  const Calling&  calling;

  std::vector<ObjectList>  object_list_table;

  Frame(const Calling&  ca):
  calling(ca){}

};


struct
Context
{
  Memory&  memory;

  ObjectList  global_object_list;

  std::vector<Frame>  frame_list;

  Pointer  base_pointer;


  Context(Memory&  mem, const ObjectList&  gobj_list);

  void    push_object_list();
  size_t   pop_object_list();

  Frame&  get_top_frame();
  int  get_level() const;

  Value  call(const Function&  fn, const Calling&  cal);

  void  make_auto_object(ObjectList&  buf, const std::string&  id, int  flags, const Value&  val);
  void  make_auto_object(const std::string&  id, int  flags, const Value&  val);

  Object*  find_object(const std::string&  id);

  Value&  get_value(Pointer  ptr);

  void  print() const;

};


#endif





#ifndef HBS_FUNCTIONFRAME_HPP_INCLUDED
#define HBS_FUNCTIONFRAME_HPP_INCLUDED


#include"hbs_blockframe.hpp"




struct Calling;


class
FunctionFrame
{
  std::list<BlockFrame>  blockframe_list;

public:
  const Function&  function;

  const Calling&  calling;

  FunctionFrame(const Function&  fn, const Calling&  ca);


  void  enter_block(const Block&  blk, ObjectList&&  objls);
  void  leave_block(Context&  ctx);

  void  leave(Context&  ctx);

  const Object*  find_object(const std::string&  id) const;

  BlockFrame*  get_top_frame();


  void  print(const Memory&  mem) const;

};


#endif





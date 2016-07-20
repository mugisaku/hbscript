#include"hbs_functionframe.hpp"
#include"hbs_context.hpp"
#include"hbs_memory.hpp"
#include"hbs_expression_node.hpp"
#include"hbs_block.hpp"
#include"hbs_function.hpp"
#include"hbs_calling.hpp"




FunctionFrame::
FunctionFrame(const Function&  fn, const Calling&  ca):
function(fn),
calling(ca)
{
}




void
FunctionFrame::
enter_block(const Block&  blk, ObjectList&&  objls)
{
  blockframe_list.emplace_back(blk,std::move(objls));
}


void
FunctionFrame::
leave_block(Context&  ctx)
{
  ctx.release_auto_object(blockframe_list.back().get_const_object_list());

  blockframe_list.pop_back();
}


void
FunctionFrame::
leave(Context&  ctx)
{
    while(blockframe_list.size())
    {
      leave_block(ctx);
    }
}




const Object*
FunctionFrame::
find_object(const std::string&  id) const
{
  auto   it = blockframe_list.rbegin();
  auto  end = blockframe_list.rend();

    while(it != end)
    {
      auto  obj = it++->find_object(id);

        if(obj)
        {
          return obj;
        }
    }


  return nullptr;
}


BlockFrame*
FunctionFrame::
get_top_frame()
{
  return(blockframe_list.size()? &blockframe_list.back():nullptr);
}


void
FunctionFrame::
print(const Memory&  mem) const
{
    for(auto&  blkfrm: blockframe_list)
    {
      blkfrm.print(mem);
    }
}





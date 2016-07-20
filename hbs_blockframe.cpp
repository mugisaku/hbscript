#include"hbs_blockframe.hpp"
#include"hbs_memory.hpp"
#include"hbs_expression_node.hpp"
#include"hbs_block.hpp"
#include"hbs_function.hpp"
#include"hbs_calling.hpp"




BlockFrame::
BlockFrame(const Block&  blk, ObjectList&&  objls):
block(blk),
current(blk.get_statement_list().cbegin()),
end(    blk.get_statement_list().cend()),
object_list(std::move(objls))
{
}




const Statement*
BlockFrame::
get_statement()
{
    if(current != end)
    {
      return &*current++;
    }


  return nullptr;
}


ObjectList&
BlockFrame::
get_object_list()
{
  return object_list;
}


const ObjectList&
BlockFrame::
get_const_object_list() const
{
  return object_list;
}


const Object*
BlockFrame::
find_object(const std::string&  id) const
{
    for(auto&  obj: object_list)
    {
        if(obj.identifier == id)
        {
          return &obj;
        }
    }


  return block.find_static_object(id);
}


void
BlockFrame::
print(const Memory&  mem) const
{
    for(auto&  obj: object_list)
    {
      obj.print(mem);
    }
}





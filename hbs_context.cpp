#include"hbs_context.hpp"
#include"hbs_memory.hpp"
#include"hbs_expression_node.hpp"
#include"hbs_block.hpp"
#include"hbs_function.hpp"
#include"hbs_calling.hpp"




Context::
Context(Memory&  mem, Block&  gblk):
memory(mem),
global_block(gblk),
base_pointer(mem.get_size()-1)
{
}




FunctionFrame&
Context::
get_top_frame()
{
  return functionframe_list.back();
}


int
Context::
get_level() const
{
  return functionframe_list.size();
}


Value
Context::
call(const Function&  fn, const Calling&  cal)
{
    if(fn.parameters.size() != cal.arguments.size())
    {
      report;

      printf("仮引数に対して、実引数の数が一致しません\n");

      return Value::undefined;
    }


  int  n = fn.parameters.size();

  auto  arg_it = cal.arguments.cbegin();
  auto  prm_it = fn.parameters.cbegin();

  ObjectList  buf;

    while(n--)
    {
      auto&  prm = *prm_it++;
      auto&  arg = *arg_it++;

      auto  argval = arg.get_value(*this);

      make_auto_object(buf,prm.identifier,prm.flags,argval);
    }


/*
  functionframe_list.emplace_back(cal);

  auto  retval = enter(fn,std::move(buf),fn.reference_sign);

  functionframe_list.pop_back();
*/


//  return std::move(retval);
}


Value
Context::
enter(const Block&  blk, ObjectList&&  objls, bool  return_reference)
{
/*
  frame_list.back().object_list_table.emplace_back(blk.get_static_object_list());

  auto&  dst = frame_list.back().object_list_table.back();

    for(auto&  obj: objls)
    {
      dst.emplace_back(std::move(obj));
    }


  auto&  stmtls = blk.get_statement_list();

  current = 


  step(*this,return_reference);


    while(pop_object_list())
    {
    }


  return std::move(val);
*/
}


void
Context::
make_auto_object(ObjectList&  buf, const std::string&  id, int  flags, const Value&  val)
{
/*
    if(flags&Parameter::reference_flag)
    {
        if(val.kind != ValueKind::reference)
        {
          printf("式の値が参照型ではありません\n");
        }


      buf.emplace_back(std::string(id),flags,ObjectKind::reference,val.data.i);
    }

  else
    {
      Pointer  ptr(base_pointer);

      --base_pointer.value;

      buf.emplace_back(std::string(id),flags,ObjectKind::auto_variable,ptr);

      memory[ptr] = val.dereference(memory);
    }
*/
}


void
Context::
make_auto_object(const std::string&  id, int  flags, const Value&  val)
{
//  make_auto_object(frame_list.back().object_list_table.back(),id,flags,val);
}


Object*
Context::
find_object(const std::string&  id)
{
    if(functionframe_list.size())
    {
      auto  obj = functionframe_list.back().find_object(id);

        if(obj)
        {
          return obj;
        }
    }


  return global_block.find_static_object(id);
}


void
Context::
print() const
{
  printf("****\n");

  auto  n = functionframe_list.size();

  printf("context level is %3d\n",n);

    if(n)
    {
/*
      auto&  frame = functionframe_list.back();

      printf("%s\n",frame.calling.identifier.data());

      auto   it = frame.object_list_table.rbegin();
      auto  end = frame.object_list_table.rend();

        while(it != end)
        {
          auto&  ls = *it++;

            for(auto&  obj: ls)
            {
              obj.print(memory);

              printf("\n");
            }
        }
*/
    }


  global_block.print(memory);


  printf("****\n\n");
}





#include"hbs_context.hpp"
#include"hbs_memory.hpp"
#include"hbs_expression_node.hpp"
#include"hbs_block.hpp"
#include"hbs_function.hpp"
#include"hbs_calling.hpp"
#include"hbs_structure.hpp"




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


Memory&
Context::
get_memory()
{
  return memory;
}


const Memory&
Context::
get_const_memory() const
{
  return memory;
}


void
Context::
release_auto_object(const ObjectList&  objls)
{
    for(auto&  obj: objls)
    {
        if(obj.kind == ObjectKind::auto_variable)
        {
          memory[obj.value].clear();

          ++base_pointer.value;
        }
    }
}


Value
Context::
call(const Function&  fn, const Calling&  cal)
{
  const Pointer  src_ptr = base_pointer;

    if(fn.parameters.size() != cal.arguments.size())
    {
      report;

      printf("仮引数に対して、実引数の数が一致しません\n");

      return false;
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


  functionframe_list.emplace_back(fn,cal);


  Value  retval;

  enter(fn,std::move(buf),retval);

  functionframe_list.back().leave(*this);

  functionframe_list.pop_back();

//  printf("onstart    %8d\n",src_ptr.value);
//  printf("onfinished %8d\n",base_pointer.value);

  return std::move(retval);
}


void
Context::
make_auto_object(ObjectList&  buf, const std::string&  id, int  flags, const Value&  val)
{
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

        if(val.kind == ValueKind::expression)
        {
          memory[ptr] = val.data.expr->get_value(*this);
        }

      else
        if(val.kind == ValueKind::structure)
        {
          val.data.st->initialize(*this);

          memory[ptr] = val;
        }

      else
        {
          memory[ptr] = val;
        }
    }
}


void
Context::
make_auto_object(const std::string&  id, int  flags, const Value&  val)
{
  make_auto_object(get_top_frame().get_top_frame()->get_object_list(),id,flags,val);
}


const Object*
Context::
find_object(const std::string&  id) const
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
      functionframe_list.back().print(memory);
    }


  global_block.print(memory);


  printf("****\n\n");
}





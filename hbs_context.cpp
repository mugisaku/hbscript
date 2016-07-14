#include"hbs_context.hpp"
#include"hbs_memory.hpp"
#include"hbs_expression_node.hpp"
#include"hbs_block.hpp"
#include"hbs_function.hpp"
#include"hbs_calling.hpp"




Context::
Context(Memory&  mem, const ObjectList&  gobj_list):
memory(mem),
global_object_list(gobj_list),
base_pointer(mem.get_size()-1)
{
}




Frame&
Context::
get_top_frame()
{
  return frame_list.back();
}


int
Context::
get_level() const
{
  return frame_list.size();
}


void
Context::
push_object_list()
{
  auto&  frame = frame_list.back();

  frame.object_list_table.emplace_back();
}


size_t
Context::
pop_object_list()
{
  auto&  frame = frame_list.back();

    if(frame.object_list_table.size())
    {
        for(auto&  obj: frame.object_list_table.back())
        {
            if(obj.kind == ObjectKind::auto_variable)
            {
              memory[obj.value].clear();

              ++base_pointer.value;
            }
        }


      frame.object_list_table.pop_back();
    }


  return frame.object_list_table.size();
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


  frame_list.emplace_back(cal);

  frame_list.back().object_list_table.emplace_back(fn.get_static_object_list());

  auto&  dst = frame_list.back().object_list_table.back();

    for(auto&  obj: buf)
    {
      dst.emplace_back(std::move(obj));
    }


  auto  val = fn(*this);

    while(pop_object_list())
    {
    }


  frame_list.pop_back();


  return std::move(val);
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

      memory[ptr] = val.dereference(memory);
    }
}


void
Context::
make_auto_object(const std::string&  id, int  flags, const Value&  val)
{
  make_auto_object(frame_list.back().object_list_table.back(),id,flags,val);
}


Object*
Context::
find_object(const std::string&  id)
{
    if(frame_list.size())
    {
      auto&  frame = frame_list.back();

      auto   it = frame.object_list_table.rbegin();
      auto  end = frame.object_list_table.rend();

        while(it != end)
        {
          auto&  ls = *it++;

            for(auto&  obj: ls)
            {
                if(obj.identifier == id)
                {
                  return &obj;
                }
            }
        }
    }


    for(auto&  obj: global_object_list)
    {
        if(obj.identifier == id)
        {
          return &obj;
        }
    }


  return nullptr;
}


Value&
Context::
get_value(Pointer  ptr)
{
  return memory[ptr];
}


void
Context::
print() const
{
  printf("****\n");

  auto  n = frame_list.size();

  printf("context level is %3d\n",n);

    if(n)
    {
      auto&  frame = frame_list.back();

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
    }


    for(auto&  obj: global_object_list)
    {
      obj.print(memory);

      printf("\n");
    }


  printf("****\n\n");
}





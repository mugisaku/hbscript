#include"hbs_block.hpp"
#include"hbs_function.hpp"
#include"hbs_context.hpp"
#include<cstdlib>




Pointer
Block::
make_static_object(Memory&  mem, std::string&&  id)
{
  auto  ptr = mem.allocate();

    if(!ptr)
    {
      report;

      return 0;
    }


  static_object_list.emplace_back(std::move(id),0,ObjectKind::static_variable,ptr);

  return ptr;
}


const Object*
Block::
find_static_object(const std::string&  id) const
{
    for(auto&  obj: static_object_list)
    {
        if(obj.identifier == id)
        {
          return &obj;
        }
    }


  return nullptr;
}


const ObjectList&
Block::
get_static_object_list() const
{
  return static_object_list;
}


void
Block::
append(Statement&&  stmt)
{
  statement_list.emplace_back(std::move(stmt));
}


const StatementList&
Block::
get_statement_list() const
{
  return statement_list;
}


void
Block::
print(const Memory&  mem) const
{
    for(auto&  obj: static_object_list)
    {
      obj.print(mem);

      printf(" = ");

      mem[obj.value].print(mem);

      printf("\n");
    }


  printf("{\n");

    for(auto&  stmt: statement_list)
    {
      stmt.print(mem);

      printf(";\n");
    }


  printf("}\n\n\n");
}



void
Block::
read(const mkf::Node&  src, Memory&  mem, int  depth)
{
  mkf::Cursor  cur(src);

  ++depth;

    while(!cur.test_ended())
    {
      auto&  nd = cur.get();

        if(nd == "statement")
        {
          Statement  stmt(this);

          stmt.read(nd,mem,depth);

            if(stmt)
            {
              statement_list.emplace_back(std::move(stmt));
            }
        }


      cur.advance();
    }
}





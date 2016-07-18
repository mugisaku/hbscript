#include"hbs_structure.hpp"
#include"hbs_memory.hpp"
#include"hbs_context.hpp"




Structure::
Structure(Memory&  mem):
memory(mem)
{
}


Structure::
~Structure()
{
    for(auto&  memb: member_list)
    {
      memory.free(memb.pointer);
    }
}




StructureMember&
Structure::
get_member(const std::string&  id)
{
    for(auto&  memb: member_list)
    {
        if(memb.identifier == id)
        {
          return memb;
        }
    }


  member_list.emplace_back(std::string(id),memory.allocate());


  auto&  memb = member_list.back();

  memory[memb.pointer] = Value(0);

  return memb;
}


void
Structure::
remove_member(const std::string&  id)
{
    for(auto&  memb: member_list)
    {
        if(memb.identifier == id)
        {
          memory.free(memb.pointer);

          break;
        }
    }
}


void
Structure::
initialize(Context&  ctx)
{
    for(auto&  memb: member_list)
    {
      auto&  v = ctx.get_memory()[memb.pointer];

        if(v.kind == ValueKind::expression)
        {
          auto  tv = v.data.expr->get_value(ctx);

          v = std::move(tv);
        }
    }
}


void
Structure::
print() const
{
  printf("struct{\n");

    for(auto&  memb: member_list)
    {
      printf("  %s: ",memb.identifier.data());

      memory[memb.pointer].print(memory);

      printf(",\n");
    }


  printf("}\n");
}





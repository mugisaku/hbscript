#include"hbs_value.hpp"
#include"hbs_structure.hpp"
#include"hbs_expression_node.hpp"
#include"hbs_memory.hpp"
#include<cstdlib>




namespace{
void
read_struct_member(const mkf::Node&  base, Memory&  mem, Structure&  st)
{
  mkf::Cursor  cur(base);

  std::string  id;

    while(!cur.test_ended())
    {
      auto&  nd = cur.get();

        if(nd == "identifier")
        {
          id.clear();

          nd.collect_characters(id);
        }

      else
        if(nd == "expression")
        {
          auto&  memb = st.get_member(id);

          auto  expr = new expression::Node;

          expr->read(nd,mem);

          mem[memb.pointer].reset(expr);
        }


      cur.advance();
    }
}
}


void
Value::
read_struct_literal(const mkf::Node&  base, Memory&  mem)
{
  mkf::Cursor  cur(base);

  auto  st = new Structure(mem);

    while(!cur.test_ended())
    {
      auto&  nd = cur.get();

        if(nd == "struct_member")
        {
          read_struct_member(nd,mem,*st);
        }


      cur.advance();
    }


  reset(st);
}





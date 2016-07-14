#include"hbs_calling.hpp"
#include"hbs_expression_node.hpp"




Calling::
Calling(const char*  id, std::initializer_list<expression::Node>  args):
identifier(id),
arguments(args)
{
}




void
Calling::
print(const Memory&  mem) const
{
  printf("%s(",identifier.data());

    if(arguments.size())
    {
      auto  it = arguments.cbegin();

        for(;;)
        {
          it++->print(mem);

            if(it == arguments.cend())
            {
              break;
            }


          printf(",");
        }
    }


  printf(")");
}




void
Calling::
read(const mkf::Node&  base)
{
  mkf::Cursor  cur(base);

    while(!cur.test_ended())
    {
      auto&  nd = cur.get();

        if(nd == "identifier")
        {
          nd.collect_characters(identifier);
        }

      else
        if(nd == "expression")
        {
          arguments.emplace_back();
          arguments.back().read(nd);
        }


      cur.advance();
    }
}





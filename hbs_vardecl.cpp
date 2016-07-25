#include"hbs_vardecl.hpp"




void
VarDecl::
print(const Memory&  mem) const
{
  printf("var  %s",identifier.data());

    if(initializer)
    {
      printf(" = ");

      initializer.print(mem);
    }
}



void
VarDecl::
read(const mkf::Node&  base, Memory&  mem)
{
  mkf::Cursor  cur(base);

    while(!cur.test_ended())
    {	
      auto&  nd = cur.get();

        if(nd == "identifier")
        {
          minpp::String  s;

          nd.collect_characters(s);

          identifier = s.to_stdstring();
        }

      else
        if(nd == "const")
        {
          flags |= Parameter::const_flag;
        }

      else
        if(nd == "static")
        {
          flags = Parameter::static_flag;
        }

      else
        if(nd == "&")
        {
          flags |= Parameter::reference_flag;
        }

      else
        if(nd == "expression")
        {
          initializer.read(nd,mem);
        }


      cur.advance();
    }
}






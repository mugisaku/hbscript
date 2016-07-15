#include"hbs_function.hpp"




Function::
Function():
reference_sign(false)
{
}




void
Function::
print(const Memory&  mem) const
{
  printf("%s(",reference_sign? "&":"");

    if(parameters.size())
    {
      auto  it = parameters.cbegin();

        for(;;)
        {
          auto&  p = *it++;

          printf("%s%s%s",p.flags&Parameter::reference_flag? "&":"",
                          p.flags&Parameter::const_flag? "const ":"",p.identifier.data());

            if(it == parameters.cend())
            {
              break;
            }


          printf(",");
        }
    }


  printf(")\n");

  Block::print(mem);

  printf("\n");
}




void
Function::
read(const mkf::Node&  src, Memory&  mem, int  depth)
{
  mkf::Cursor  cur(src);

    while(!cur.test_ended())
    {
      auto&  nd = cur.get();

        if(nd == "parameter")
        {
          read_parameter(nd);
        }

      else
        if(nd == "&")
        {
          reference_sign = true;
        }

      else
        if(nd == "block")
        {
          Block::read(nd,mem,depth+1);
        }


      cur.advance();
    }
}


void
Function::
read_parameter(const mkf::Node&  src)
{
  mkf::Cursor  cur(src);

  int  flags = 0;

    while(!cur.test_ended())
    {
      auto&  nd = cur.get();

        if(nd == "&")
        {
          flags |= Parameter::reference_flag;
        }

      else
        if(nd == "const")
        {
          flags |= Parameter::const_flag;
        }

      else
        if(nd == "identifier")
        {
          std::string  s;

          nd.collect_characters(s);

          parameters.emplace_back(std::move(s),flags);
        }


      cur.advance();
    }
}






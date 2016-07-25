#include"hbs_value.hpp"
#include<cstdlib>




namespace{
int
read_decimal_literal(const mkf::Node&  base)
{
  minpp::String  s;

  base.collect_characters(s);

  return static_cast<int>(std::stoul(s.to_stdstring(),nullptr,10));
}


int
read_hex_literal(const mkf::Node&  base)
{
  minpp::String  s;

  base.collect_characters(s);

  return std::stoi(s.to_stdstring(),nullptr,16);
}


int
read_binary_literal(const mkf::Node&  base)
{
  int  i = 0;

  mkf::Cursor  cur(base);

    while(!cur.test_ended())
    {
      auto&  nd = cur.get();

        if(nd == "zero_or_one")
        {
          i <<=                                  1;
          i  |= (nd.character.unicode == '1')? 1:0;
        }


      cur.advance();
    }


  return i;
}



}



void
Value::
read_integer_literal(const mkf::Node&  base)
{
  mkf::Cursor  cur(base);

    while(!cur.test_ended())
    {
      auto&  nd = cur.get();

           if(nd == "decimal_literal"){reset(read_decimal_literal(nd));}
      else if(nd == "hex_literal"    ){reset(read_hex_literal(nd));}
      else if(nd == "binary_literal" ){reset(read_binary_literal(nd));}


      cur.advance();
    }
}





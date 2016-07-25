#include"hbs_value.hpp"
#include<cstdlib>




namespace{
int
read_character(const mkf::Node&  base)
{
  mkf::Cursor  cur(base);

    while(!cur.test_ended())
    {
      auto&  nd = cur.get();

           if(nd == "null_character"        ){return 0;}
      else if(nd == "newline_character"     ){return '\n';}
      else if(nd == "backslash_character"   ){return '\\';}
      else if(nd == "single_quote_character"){return '\'';}
      else if(nd == "double_quote_character"){return '\"';}
      else if(nd == "normal_character"      ){return nd.character.unicode;}


      cur.advance();
    }


  return 0;
}
}




void
Value::
read_character_literal(const mkf::Node&  base)
{
  mkf::Cursor  cur(base);

    while(!cur.test_ended())
    {
      auto&  nd = cur.get();

        if(nd == "character")
        {
          reset(read_character(nd));
        }


      cur.advance();
    }
}





#include"hbs_ifstatement.hpp"




void
IfStatement::
print(const Memory&  mem)
{
  printf("if");

  if_block.print(mem);

  printf("\n");

    for(auto&  cblk: elseif_block_list)
    {
      printf("else if");

      cblk.print(mem);
    }


    if(else_block.get_statement_list().size())
    {
      printf("\n");

      printf("else");

      else_block.print(mem);
    }
}


void
IfStatement::
read(const mkf::Node&  src, Memory&  mem, int  depth)
{
  mkf::Cursor  cur(src);

    while(!cur.test_ended())
    {
      auto&  nd = cur.get();

        if(nd == "if_block")
        {
          read_conditional_block(if_block,nd,mem,depth);
        }

      else
        if(nd == "elseif_block")
        {
          ConditionalBlock  condblk;

          read_conditional_block(condblk,nd,mem,depth);

          elseif_block_list.emplace_back(std::move(condblk));
        }

      else
        if(nd == "else_block")
        {
          read_else_block(nd,mem,depth);
        }


      cur.advance();
    }
}


void
IfStatement::
read_conditional_block(ConditionalBlock&  blk, const mkf::Node&  src, Memory&  mem, int  depth)
{
  mkf::Cursor  cur(src);

    while(!cur.test_ended())
    {
      auto&  nd = cur.get();

        if(nd == "conditional_block")
        {
          blk.read(nd,mem,depth);
        }


      cur.advance();
    }
}


void
IfStatement::
read_else_block(const mkf::Node&  src, Memory&  mem, int  depth)
{
  mkf::Cursor  cur(src);

    while(!cur.test_ended())
    {
      auto&  nd = cur.get();

        if(nd == "block")
        {
          else_block.read(nd,mem,depth);
        }


      cur.advance();
    }
}





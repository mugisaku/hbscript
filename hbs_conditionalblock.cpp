#include"hbs_conditionalblock.hpp"
#include"hbs_context.hpp"




void
ConditionalBlock::
change_condition(expression::Node&&  cond)
{
  condition = std::move(cond);
}


const expression::Node&
ConditionalBlock::
get_condition() const
{
  return condition;
}


bool
ConditionalBlock::
get_condition_value(Context&  ctx) const
{
    if(!condition)
    {
      return true;
    }


  auto  val = condition.get_value(ctx);

  return val.dereference(ctx.get_memory()).data.i;
}


void
ConditionalBlock::
print(const Memory&  mem) const
{
  printf("(");

  condition.print(mem);

  printf(")\n");

  Block::print(mem);
}


void
ConditionalBlock::
read(const mkf::Node&   src, Memory&  mem, int  depth)
{
  mkf::Cursor  cur(src);

    while(!cur.test_ended())
    {
      auto&  nd = cur.get();

        if(nd == "expression")
        {
          condition.read(nd,mem);
        }

      else
        if(nd == "block")
        {
          Block::read(nd,mem,depth);
        }


      cur.advance();
    }
}





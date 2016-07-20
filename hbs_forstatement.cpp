#include"hbs_forstatement.hpp"




bool
ForStatement::
get_condition_value(Context&  ctx) const
{
}


void
ForStatement::
iterate(Context&  ctx) const
{
}


void
ForStatement::
print(const Memory&  mem)
{
  printf("for(");

  vardecl->print(mem);

  printf(";  ");

  conditional_block->get_condition().print(mem);

  printf(";  ");

  iteration->print(mem);

  printf(")\n");

  conditional_block->Block::print(mem);
}


void
ForStatement::
read(const mkf::Node&  src, Memory&  mem, int  depth)
{
  mkf::Cursor  cur(src);

  expression::Node*  it = nullptr;

  auto  condblk = new ConditionalBlock;

    while(!cur.test_ended())
    {
      auto&  nd = cur.get();

        if(nd == "var_declaration")
        {
          Statement  stmt;

          auto  vardecl_ = new VarDecl;

          vardecl_->read(nd,mem);

          stmt.reset(vardecl_);

          vardecl = vardecl_;

          Block::append(std::move(stmt));
        }

      else
        if(nd == "for_condition")
        {
          expression::Node  cond;

          cond.read(*nd.children.front(),mem);

          condblk->change_condition(std::move(cond));
        }

      else
        if(nd == "for_iteration")
        {
          it = new expression::Node;

          it->read(*nd.children.front(),mem);

          iteration = it;
        }

      else
        if(nd == "block")
        {
          condblk->Block::read(nd,mem,depth);

            if(it)
            {
              Statement  stmt;

              stmt.reset(it,true);

              condblk->append(std::move(stmt));
            }


          conditional_block = condblk;

          Statement  stmt;

          stmt.reset(condblk);

          append(std::move(stmt));
        }


      cur.advance();
    }
}





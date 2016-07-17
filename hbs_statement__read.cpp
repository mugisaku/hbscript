#include"hbs_statement.hpp"
#include"hbs_block.hpp"
#include"hbs_conditionalblock.hpp"
#include"hbs_function.hpp"
#include"hbs_expression_node.hpp"
#include"hbs_ifstatement.hpp"
#include"hbs_forstatement.hpp"
#include"hbs_vardecl.hpp"




void
Statement::
read(const mkf::Node&  src, Memory&  mem, int  depth)
{
  mkf::Cursor  cur(src);

    while(!cur.test_ended())
    {
      auto&  nd = cur.get();

        if(nd == "declaration_statement")
        {
          read_declaration(nd,mem,depth);
        }

      else
        if(nd == "control_statement")
        {
          read_control_statement(nd,mem,depth);
        }

      else
        if(nd == "debug")
        {
          read_debug_statement(nd);
        }

      else
        if(nd == "block")
        {
          auto  blk = new Block;

          blk->read(nd,mem,depth);

          reset(blk);
        }

      else
        if(nd == "expression")
        {
          auto  expr = new expression::Node;

          expr->read(nd);

          reset(expr);
        }


      cur.advance();
    }
}


void
Statement::
read_control_statement(const mkf::Node&  src, Memory&  mem, int  depth)
{
  mkf::Cursor  cur(src);

    while(!cur.test_ended())
    {
      auto&  nd = cur.get();

        if(nd == "if_statement")
        {
          auto  ifstmt = new IfStatement;

          ifstmt->read(nd,mem,depth);

          reset(ifstmt);
        }

      else
        if(nd == "while_statement")
        {
          read_while_statement(nd,mem,depth);
        }

      else
        if(nd == "for_statement")
        {
          auto  forstmt = new ForStatement;

          forstmt->read(nd,mem,depth);

          reset(forstmt);
        }

      else
        if(nd == "break_statement")
        {
          read_break_statement(nd);
        }

      else
        if(nd == "continue_statement")
        {
          read_continue_statement(nd);
        }

      else
        if(nd == "return_statement")
        {
          read_return_statement(nd);
        }


      cur.advance();
    }
}


void
Statement::
read_while_statement(const mkf::Node&  src, Memory&  mem, int  depth)
{
  mkf::Cursor  cur(src);

    while(!cur.test_ended())
    {
      auto&  nd = cur.get();

        if(nd == "conditional_block")
        {
          auto  condblk = new ConditionalBlock;

          condblk->read(nd,mem,depth);

          reset(condblk);
        }


      cur.advance();
    }
}


void
Statement::
read_debug_statement(const mkf::Node&  src)
{
  mkf::Cursor  cur(src);

    while(!cur.test_ended())
    {
      auto&  nd = cur.get();

        if(nd == "expression")
        {
          auto  expr = new expression::Node;

          expr->read(nd);

          reset(Debug(expr));
        }


      cur.advance();
    }
}


void
Statement::
read_continue_statement(const mkf::Node&  src)
{
  mkf::Cursor  cur(src);

  std::string*  id = new std::string;

    while(!cur.test_ended())
    {
      auto&  nd = cur.get();

        if(nd == "identifier")
        {
          nd.collect_characters(*id);
        }


      cur.advance();
    }


  reset(Continue(id));
}


void
Statement::
read_break_statement(const mkf::Node&  src)
{
  mkf::Cursor  cur(src);

  std::string*  id = new std::string;

    while(!cur.test_ended())
    {
      auto&  nd = cur.get();

        if(nd == "identifier")
        {
          nd.collect_characters(*id);
        }


      cur.advance();
    }


  reset(Break(id));
}


void
Statement::
read_return_statement(const mkf::Node&  src)
{
  mkf::Cursor  cur(src);

  kind = StatementKind::return_;

    while(!cur.test_ended())
    {
      auto&  nd = cur.get();

        if(nd == "expression")
        {
          data.expr = new expression::Node;

          data.expr->read(nd);

          kind = StatementKind::return_;
        }


      cur.advance();
    }
}




void
Statement::
read_declaration(const mkf::Node&  src, Memory&  mem, int  depth)
{
  mkf::Cursor  cur(src);

    while(!cur.test_ended())
    {
      auto&  nd = cur.get();

        if(nd == "var_declaration")
        {
          auto  vardecl = new VarDecl;

          vardecl->read(nd);

            if(depth == 1)
            {
              vardecl->flags |= Parameter::static_flag;
            }


          reset(vardecl);

            if(vardecl->flags&Parameter::static_flag)
            {
              auto  ptr = parent->make_static_object(mem,std::string(vardecl->identifier));

//              mem[ptr].reset(expr);
            }
        }

      else
        if(nd == "function_declaration")
        {
          read_function_declaration(nd,mem,depth);
        }

      else
        if(nd == "enum_declaration")
        {
          read_enum_declaration(nd);
        }


      cur.advance();
    }
}




void
Statement::
read_function_declaration(const mkf::Node&  base, Memory&  mem, int  depth)
{
  mkf::Cursor  cur(base);

  std::string  id;

  auto  fn = new Function;

    while(!cur.test_ended())
    {
      auto&  nd = cur.get();

        if(nd == "identifier")
        {
          nd.collect_characters(id);
        }

      else
        if(nd == "function_definition")
        {
          fn->read(nd,mem,depth);
        }


      cur.advance();
    }


  auto  ptr = parent->make_static_object(mem,std::move(id));

  mem[ptr].reset(fn);
}




namespace{


void
read_enumerator(const mkf::Node&  base, int  v)
{
  mkf::Cursor  cur(base);

  std::string  id;

    while(!cur.test_ended())
    {
      auto&  nd = cur.get();

        if(nd == "identifier")
        {
          nd.collect_characters(id);
        }

      else
        if(nd == "expression")
        {
          auto  tree = new expression::Node;

//          tree->read(nd);
        }


      cur.advance();
    }
}
}


void
Statement::
read_enum_declaration(const mkf::Node&  base)
{
  mkf::Cursor  cur(base);

  int  v = 0;

    while(!cur.test_ended())
    {
      auto&  nd = cur.get();

        if(nd == "enumerator")
        {
//          v = parent->append_enumerator(read_enumerator(nd,v));
        }


      cur.advance();
    }
}





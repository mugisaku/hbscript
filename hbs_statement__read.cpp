#include"hbs_statement.hpp"
#include"hbs_block.hpp"
#include"hbs_function.hpp"
#include"hbs_expression_node.hpp"




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

    while(!cur.test_ended())
    {
      auto&  nd = cur.get();

        if(nd == "identifier")
        {
        }


      cur.advance();
    }
}


void
Statement::
read_break_statement(const mkf::Node&  src)
{
  mkf::Cursor  cur(src);

    while(!cur.test_ended())
    {
      auto&  nd = cur.get();

        if(nd == "identifier")
        {
        }


      cur.advance();
    }
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
          read_var_declaration(nd,mem,depth);
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




void
Statement::
read_var_declaration(const mkf::Node&  base, Memory&  mem, int  depth)
{
  const bool  global_flag = !depth;
        bool  static_flag = global_flag;

  std::string  id;

  int  flags = 0;

  Pointer  ptr;

  mkf::Cursor  cur(base);

    while(!cur.test_ended())
    {	
      auto&  nd = cur.get();

        if(nd == "identifier")
        {
          nd.collect_characters(id);

          reset(new VarDecl(std::string(id),flags));

            if(static_flag)
            {
              ptr = parent->make_static_object(mem,std::string(id));
            }
        }

      else
        if(nd == "const")
        {
          flags |= Parameter::const_flag;
        }

      else
        if(nd == "static")
        {
          static_flag = true;
        }

      else
        if(nd == "&")
        {
          flags |= Parameter::reference_flag;
        }

      else
        if(nd == "expression")
        {
            if(static_flag)
            {
              auto  expr = new expression::Node;

              expr->read(nd);

              mem[ptr].reset(expr);
            }

          else
            {
              expression::Node  expr;

              expr.read(nd);

              data.vardecl->initializer = std::move(expr);
            }
        }


      cur.advance();
    }
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





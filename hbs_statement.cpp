#include"hbs_statement.hpp"
#include"hbs_block.hpp"
#include"hbs_conditionalblock.hpp"
#include"hbs_ifstatement.hpp"




Statement::
Statement(Block*  parent_):
parent(parent_),
kind(StatementKind::null)
{
}


Statement::
Statement(const Statement&  rhs):
kind(StatementKind::null)
{
  *this = rhs;
}


Statement::
Statement(Statement&&  rhs):
kind(StatementKind::null)
{
  *this = std::move(rhs);
}


Statement::
~Statement()
{
  clear();
}




Statement&
Statement::
operator=(const Statement&  rhs)
{
  clear();

  parent = rhs.parent;

  kind = rhs.kind;

    switch(kind)
    {
      case(StatementKind::null):
        break;
      case(StatementKind::return_):
      case(StatementKind::expression):
      case(StatementKind::debug):
        data.expr = new expression::Node(*rhs.data.expr);
        break;
      case(StatementKind::vardecl):
        data.vardecl = new VarDecl(*rhs.data.vardecl);
        break;
      case(StatementKind::break_):
      case(StatementKind::continue_):
        data.id = new std::string(*rhs.data.id);
        break;
      case(StatementKind::ifstmt):
        data.ifstmt = new IfStatement(*rhs.data.ifstmt);
        break;
      default:
        report;
    }


  return *this;
}


Statement&
Statement::
operator=(Statement&&  rhs)
{
  clear();

  parent = rhs.parent;

  kind = rhs.kind                      ;
         rhs.kind = StatementKind::null;

  data = rhs.data;

  return *this;
}


Statement::
operator bool() const
{
  return(kind != StatementKind::null);
}


void
Statement::
clear()
{
    switch(kind)
    {
      case(StatementKind::null):
        break;
      case(StatementKind::return_):
      case(StatementKind::expression):
      case(StatementKind::debug):
        delete data.expr;
        break;
      case(StatementKind::vardecl):
        delete data.vardecl;
        break;
      case(StatementKind::break_):
      case(StatementKind::continue_):
        delete data.id;
        break;
      case(StatementKind::ifstmt):
        delete data.ifstmt;
        break;
      default:
        report;
    }


  kind = StatementKind::null;
}


void
Statement::
reset(expression::Node*  expr)
{
  clear();

  kind = StatementKind::expression;

  data.expr = expr;
}


void
Statement::
reset(VarDecl*  vardecl)
{
  clear();

  kind = StatementKind::vardecl;

  data.vardecl = vardecl;
}


void
Statement::
reset(const Debug&  dbg)
{
  clear();

  kind = StatementKind::debug;

  data.expr = dbg.expr;
}


void
Statement::
reset(IfStatement*  ifstmt)
{
  clear();

  kind = StatementKind::ifstmt;

  data.ifstmt = ifstmt;
}


void
Statement::
print(const Memory&  mem) const
{
    switch(kind)
    {
      case(StatementKind::null):
        printf("(null)");
        break;
      case(StatementKind::vardecl):
        printf("var  %s",data.vardecl->identifier.data());

          if(data.vardecl->initializer)
          {
            printf(" = ");

            data.vardecl->initializer.print(mem);
          }
        break;
      case(StatementKind::debug):
        printf("debug");
        data.expr->print(mem);
        break;
      case(StatementKind::break_):
        printf("break %s",data.id->data());
        break;
      case(StatementKind::continue_):
        printf("continue %s",data.id->data());
        break;
      case(StatementKind::return_):
        printf("return ");
        data.expr->print(mem);
        break;
      case(StatementKind::expression):
        data.expr->print(mem);
        break;
      case(StatementKind::ifstmt):
        data.ifstmt->print(mem);
        break;
      default:
        report;
    }
}





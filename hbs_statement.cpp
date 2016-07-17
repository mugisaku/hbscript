#include"hbs_statement.hpp"
#include"hbs_block.hpp"
#include"hbs_conditionalblock.hpp"
#include"hbs_ifstatement.hpp"
#include"hbs_forstatement.hpp"
#include"hbs_vardecl.hpp"




Statement::
Statement(Block*  parent_):
parent(parent_),
kind(StatementKind::null)
{
}


Statement::
Statement(Statement&&  rhs) noexcept:
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
      case(StatementKind::hidden_expression):
      case(StatementKind::debug):
        delete data.expr;
        break;
      case(StatementKind::vardecl):
        delete data.vardecl;
        break;
      case(StatementKind::block):
        delete data.blk;
        break;
      case(StatementKind::break_):
      case(StatementKind::continue_):
        delete data.id;
        break;
      case(StatementKind::ifstmt):
        delete data.ifstmt;
        break;
      case(StatementKind::forstmt):
        delete data.forstmt;
        break;
      case(StatementKind::whilestmt):
        delete data.condblk;
        break;
      default:
        report;
    }


  kind = StatementKind::null;
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
      case(StatementKind::block):
        data.blk->print(mem);
        break;
      case(StatementKind::vardecl):
        data.vardecl->print(mem);
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
      case(StatementKind::hidden_expression):
        break;
      case(StatementKind::ifstmt):
        data.ifstmt->print(mem);
        break;
      case(StatementKind::forstmt):
        data.forstmt->print(mem);
        break;
      case(StatementKind::whilestmt):
        printf("while");
        data.condblk->print(mem);
        break;
      default:
        report;
    }
}





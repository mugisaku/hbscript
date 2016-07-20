#include"hbs_statement.hpp"
#include"hbs_block.hpp"
#include"hbs_conditionalblock.hpp"
#include"hbs_ifstatement.hpp"
#include"hbs_forstatement.hpp"
#include"hbs_vardecl.hpp"




void
Statement::
reset(expression::Node*  expr, bool  hidden)
{
  clear();

  kind = hidden? StatementKind::hidden_expression
               : StatementKind::expression;

  data.expr = expr;
}


void
Statement::
reset(Block*  blk)
{
  clear();

  kind = StatementKind::block;

  data.blk = blk;
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
reset(ForStatement*  forstmt)
{
  clear();

  kind = StatementKind::forstmt;

  data.forstmt = forstmt;
}


void
Statement::
reset(ConditionalBlock*  condblk)
{
  clear();

  kind = StatementKind::whilestmt;

  data.condblk = condblk;
}


void
Statement::
reset(const Break&  brk)
{
  clear();

  kind = StatementKind::break_;

  data.id = brk.id;
}


void
Statement::
reset(const Continue&  con)
{
  clear();

  kind = StatementKind::continue_;

  data.id = con.id;
}





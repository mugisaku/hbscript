#ifndef HBSCRIPT_STATEMENT_HPP_INCLUDED
#define HBSCRIPT_STATEMENT_HPP_INCLUDED


#include<cstddef>
#include"libmkf/mkf_node.hpp"
#include"libmkf/mkf_cursor.hpp"
#include"hbs_expression_node.hpp"
#include"hbs_parameter.hpp"


#ifndef report
#define report  printf("[report in %s] %d %s\n",__FILE__,__LINE__,__func__);
#endif


struct Block;
struct ConditionalBlock;
struct LabeledBlock;
struct IfStatement;


enum class
StatementKind
{
  null,

  debug,

  block,
  expression,
  vardecl,
  break_,
  continue_,
  label_,
  return_,
  ifstmt,
  forstmt,

};


struct
Debug
{
  expression::Node*  expr;

  Debug(expression::Node*  expr_): expr(expr_){}

};


struct
VarDecl: public Parameter
{
  expression::Node  initializer;

  VarDecl(std::string&&  id, int  flags_):
  Parameter(std::move(id),flags_)
  {}

};


struct
Statement
{
  Block*  parent;

  StatementKind  kind;

  union{
    VarDecl*             vardecl;
    std::string*         id;
    Block*              blk;
    expression::Node*  expr;
    IfStatement*     ifstmt;

  } data;


   Statement(Block*  parent_=nullptr);
   Statement(const Statement&   rhs);
   Statement(      Statement&&  rhs);
  ~Statement();


  Statement&  operator=(const Statement&   rhs);
  Statement&  operator=(      Statement&&  rhs);

  operator bool() const;

  void  clear();

  void  reset(expression::Node*  expr);
  void  reset(VarDecl*  vardecl);
  void  reset(const Debug&  dbg);
  void  reset(IfStatement*  ifstmt);

  void  print(const Memory&  mem) const;


  void  read(const mkf::Node&  src, Memory&  mem, int  depth);
  void  read_debug_statement(const mkf::Node&  src);
  void  read_control_statement( const mkf::Node&  src, Memory&  mem, int  depth);
  void  read_break_statement(   const mkf::Node&  src);
  void  read_continue_statement(const mkf::Node&  src);
  void  read_return_statement(  const mkf::Node&  src);

  void           read_declaration(const mkf::Node&  base, Memory&  mem, int  depth);
  void      read_enum_declaration(const mkf::Node&  base);
  void  read_function_declaration(const mkf::Node&  base, Memory&  mem, int  depth);

  void  read_var_declaration(const mkf::Node&  base, Memory&  mem, int  depth);
};


using StatementList = std::vector<Statement>;




#endif





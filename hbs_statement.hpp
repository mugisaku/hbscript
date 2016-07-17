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
struct ForStatement;
struct VarDecl;


enum class
StatementKind
{
  null,

  debug,

  block,
  expression,
  hidden_expression,
  vardecl,
  break_,
  continue_,
  label_,
  return_,
  ifstmt,
  forstmt,
  whilestmt,

};


struct
Debug
{
  expression::Node*  expr;

  Debug(expression::Node*  expr_): expr(expr_){}

};


struct
Continue
{
  std::string*  id;

  Continue(std::string*  id_=nullptr): id(id_){}

};


struct
Break
{
  std::string*  id;

  Break(std::string*  id_=nullptr): id(id_){}

};


struct
Statement
{
  Block*  parent;

  StatementKind  kind;

  union{
    VarDecl*           vardecl;
    std::string*            id;
    Block*                 blk;
    ConditionalBlock*  condblk;
    expression::Node*     expr;
    IfStatement*        ifstmt;
    ForStatement*      forstmt;

  } data;


   Statement(Block*  parent_=nullptr);
   Statement(const Statement&)=delete;
   Statement(      Statement&&  rhs) noexcept;
  ~Statement();


  Statement&  operator=(Statement&&  rhs);

  operator bool() const;

  void  clear();

  void  reset(expression::Node*  expr, bool  hidden=false);
  void  reset(Block*  blk);
  void  reset(VarDecl*  vardecl);
  void  reset(const Debug&  dbg);
  void  reset(IfStatement*  ifstmt);
  void  reset(ForStatement*  forstmt);
  void  reset(ConditionalBlock*  condblk);
  void  reset(const Break&     brk);
  void  reset(const Continue&  con);

  void  print(const Memory&  mem) const;


  void  read(const mkf::Node&  src, Memory&  mem, int  depth);
  void  read_debug_statement(const mkf::Node&  src);
  void  read_control_statement(const mkf::Node&  src, Memory&  mem, int  depth);
  void  read_while_statement(  const mkf::Node&  src, Memory&  mem, int  depth);
  void  read_break_statement(   const mkf::Node&  src);
  void  read_continue_statement(const mkf::Node&  src);
  void  read_return_statement(  const mkf::Node&  src);

  void           read_declaration(const mkf::Node&  base, Memory&  mem, int  depth);
  void      read_enum_declaration(const mkf::Node&  base);
  void  read_function_declaration(const mkf::Node&  base, Memory&  mem, int  depth);

};


using StatementList = std::vector<Statement>;




#endif





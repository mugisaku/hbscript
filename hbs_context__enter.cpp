#include"hbs_context.hpp"
#include"hbs_memory.hpp"
#include"hbs_expression_node.hpp"
#include"hbs_block.hpp"
#include"hbs_function.hpp"
#include"hbs_calling.hpp"
#include"hbs_ifstatement.hpp"
#include"hbs_forstatement.hpp"
#include"hbs_vardecl.hpp"




Context::LeaveStatus
Context::
enter(const Block&  blk, ObjectList&&  objls, Value&  retval)
{
  auto&  fnfrm = functionframe_list.back();

  fnfrm.enter_block(blk,std::move(objls));

    for(;;)
    {
      auto  blkfrm = fnfrm.get_top_frame();

        if(!blkfrm)
        {
          break;
        }


      auto  stmtptr = blkfrm->get_statement();

        if(!stmtptr)
        {
          fnfrm.leave_block(*this);

          break;
        }


      auto&  stmt = *stmtptr;

        switch(stmt.kind)
        {
          case(StatementKind::expression):
          case(StatementKind::hidden_expression):
            {
              stmt.data.expr->get_value(*this);
            }
            break;
          case(StatementKind::break_):
            {
              fnfrm.leave_block(*this);

              return LeaveStatus::broke;
            }
            break;
          case(StatementKind::continue_):
            {
              fnfrm.leave_block(*this);

              return LeaveStatus::continued;
            }
            break;
          case(StatementKind::forstmt):
            {
              auto&  forstmt = *stmt.data.forstmt;

              auto  lvst = enter(forstmt,{},retval);

                if(lvst == LeaveStatus::returned)
                {
                  return LeaveStatus::returned;
                }
            }
            break;
          case(StatementKind::whilestmt):
            {
              auto&  condblk = *stmt.data.condblk;

                for(;;)
                {
                  auto  v = condblk.get_condition_value(*this);

                    if(!v)
                    {
                      break;
                    }


                  auto  lvst = enter(condblk,{},retval);

                    if(lvst == LeaveStatus::returned)
                    {
                      return LeaveStatus::returned;
                    }

                  else
                    if(lvst == LeaveStatus::broke)
                    {
                      fnfrm.leave_block(*this);

                      break;
                    }

                  else
                    if(lvst == LeaveStatus::continued)
                    {
                      fnfrm.leave_block(*this);

                      continue;
                    }

                  else
                    {
                      continue;
                    }
                }
            }
            break;
          case(StatementKind::ifstmt):
            {
              auto&  ifstmt = *stmt.data.ifstmt;

                if(ifstmt.if_block.get_condition_value(*this))
                {
                  auto  lvst = enter(ifstmt.if_block,{},retval);

                    if(lvst != LeaveStatus::ended)
                    {
                      return lvst;
                    }
                }

              else
                {
                  bool  flag = false;

                    for(auto&  condblk: ifstmt.elseif_block_list)
                    {
                        if(condblk.get_condition_value(*this))
                        {
                          flag = true;

                          auto  lvst = enter(condblk,{},retval);

                            if(lvst != LeaveStatus::ended)
                            {
                              return lvst;
                            }


                          break;
                        }
                    }


                    if(!flag)
                    {
                      auto  lvst = enter(ifstmt.else_block,{},retval);

                        if(lvst != LeaveStatus::ended)
                        {
                          return lvst;
                        }
                    }
                }
            }
            break;
          case(StatementKind::vardecl):
            {
              auto  val = stmt.data.vardecl->initializer.get_value(*this);

              auto&  para = *stmt.data.vardecl;

              make_auto_object(para.identifier,para.flags,val);
            }
            break;
          case(StatementKind::debug):
            {
              auto  val = stmt.data.expr->get_value(*this);

              printf("[debug in %s -- level %3d] ",get_top_frame().calling.identifier.data(),get_level());

              stmt.data.expr->print(memory);

              printf(" = ");

              val.print(memory);

              printf("\n");
            }
            break;
          case(StatementKind::return_):
            {
              auto  expr = stmt.data.expr;

              retval = Value(ValueKind::void_);

                if(expr)
                {
                  retval = expr->get_value(*this);

                    if(!functionframe_list.back().function.reference_sign)
                    {
                      auto  tmpval = retval.dereference(memory);

                      retval = tmpval;
                    }
                }


              return LeaveStatus::returned;
            }
            break;
        }
    }


  return LeaveStatus::ended;
}





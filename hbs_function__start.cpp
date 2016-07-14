#include"hbs_function.hpp"




Value
Function::
operator()(Context&  ctx) const
{
    for(auto&  stmt: statement_list)
    {
        switch(stmt.kind)
        {
          case(StatementKind::expression):
            {
              auto  val = stmt.data.expr->get_value(ctx);
            }
            break;
          case(StatementKind::vardecl):
            {
              auto  val = stmt.data.vardecl->initializer.get_value(ctx);

              auto&  para = *stmt.data.vardecl;

              ctx.make_auto_object(para.identifier,para.flags,val);
            }
            break;
          case(StatementKind::debug):
            {
              auto  val = stmt.data.expr->get_value(ctx);

              printf("[debug in %s -- level %3d] ",ctx.get_top_frame().calling.identifier.data(),ctx.get_level());

              stmt.data.expr->print(ctx.memory);

              printf(" = ");

              val.print(ctx.memory);

              printf("(");

              val.dereference(ctx.memory).print(ctx.memory);

              printf(")\n");
            }
            break;
          case(StatementKind::return_):
            {
              auto  expr = stmt.data.expr;

              Value  retval(ValueKind::void_);

                if(expr)
                {
                  retval = expr->get_value(ctx);

                    if(!reference_sign)
                    {
                      auto  tmpval = retval.dereference(ctx.memory);

                      retval = tmpval;
                    }
                }

              return std::move(retval);
            }
            break;
        }
    }


  return Value(ValueKind::void_);
}





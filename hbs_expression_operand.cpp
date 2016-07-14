#include"hbs_expression_operand.hpp"
#include"hbs_expression_node.hpp"
#include"hbs_calling.hpp"
#include"hbs_function.hpp"
#include"hbs_block.hpp"




namespace expression{




Operand::Operand(): kind(OperandKind::null){}
Operand::Operand(Calling*  cal): kind(OperandKind::null){reset(cal);}
Operand::Operand(Node*  nod): kind(OperandKind::null){reset(nod);}
Operand::Operand(std::string*  str): kind(OperandKind::null){reset(str);}
Operand::Operand(Value*  val): kind(OperandKind::null){reset(val);}
Operand::Operand(const Operand&   rhs): kind(OperandKind::null){*this =          (rhs);}
Operand::Operand(      Operand&&  rhs): kind(OperandKind::null){*this = std::move(rhs);}


Operand::
~Operand()
{
  clear();
}




Operand&
Operand::
operator=(const Operand&   rhs)
{
  clear();

  kind = rhs.kind;

    switch(kind)
    {
      case(OperandKind::value):
        data.val = new Value(*rhs.data.val);
        break;
      case(OperandKind::identifier):
        data.str = new std::string(*rhs.data.str);
        break;
      case(OperandKind::calling):
        data.cal = new Calling(*rhs.data.cal);
        break;
      case(OperandKind::tree):
        data.nod = new Node(*rhs.data.nod);
        break;
      default:;
    }


  return *this;
}


Operand&
Operand::
operator=(Operand&&  rhs)
{
  clear();

  kind = rhs.kind                    ;
         rhs.kind = OperandKind::null;

  data = rhs.data;

  return *this;
}




void
Operand::
clear()
{
    switch(kind)
    {
      case(OperandKind::value):
        delete data.val;
        break;
      case(OperandKind::identifier):
        delete data.str;
        break;
      case(OperandKind::calling):
        delete data.cal;
        break;
      case(OperandKind::tree):
        delete data.nod;
        break;
      default:;
    }


  kind = OperandKind::null;
}




void
Operand::
reset(Calling*  cal)
{
  clear();

  kind = OperandKind::calling;

  data.cal = cal;
}


void
Operand::
reset(Node*  nod)
{
  clear();

  kind = OperandKind::tree;

  data.nod = nod;
}


void
Operand::
reset(std::string*  str)
{
  clear();

  kind = OperandKind::identifier;

  data.str = str;
}


void
Operand::
reset(Value*  val)
{
  clear();

  kind = OperandKind::value;

  data.val = val;
}


Value
Operand::
get_value(Context&  ctx) const
{
    switch(kind)
    {
      case(OperandKind::value):
        return Value(*data.val);
        break;
      case(OperandKind::tree):
        return data.nod->get_value(ctx);
        break;
      case(OperandKind::identifier):
        {
          auto&  id = *data.str;

          auto  obj = ctx.find_object(id);

            if(obj)
            {
              return obj->get_value(ctx.memory);
            }

          else
            {
              printf("%sという名前の変数が見つかりません\n",id.data());
            }


          ctx.print();

          throw id;
        }
        break;
      case(OperandKind::calling):
        {
          auto&  id = *data.str;

          auto  obj = ctx.find_object(id);

            if(obj)
            {
              auto&  val = ctx.memory[obj->value];

                if(val.kind == ValueKind::function)
                {
                  return ctx.call(*val.data.fn,*data.cal);
                }

              else
                {
                  printf("%sは関数ではありません\n",id.data());
                }
            }

          else
            {
              printf("%sという名前の関数が見つかりません\n",id.data());
            }


          ctx.print();

          throw id;
        }
        break;
    }


  return Value(ValueKind::undefined);
}


void
Operand::
print(const Memory&  mem) const
{
    switch(kind)
    {
      case(OperandKind::null):
        printf("null");
        break;
      case(OperandKind::value):
        data.val->print(mem);
        break;
      case(OperandKind::identifier):
        printf("%s",data.str->data());
        break;
      case(OperandKind::calling):
        data.cal->print(mem);
        break;
      case(OperandKind::tree):
        printf("(");
        data.nod->print(mem);
        printf(")");
        break;
      default:;
    }
}




void
Operand::
read(const mkf::Node&  base)
{
  mkf::Cursor  cur(base);

    while(!cur.test_ended())
    {
      auto&  nd = cur.get();

        if(nd == "identifier")
        {
          auto  s = new std::string;

          nd.collect_characters(*s);

          reset(s);
        }

      else
        if(nd == "integer_literal")
        {
          auto  val = new Value;

          val->read_integer_literal(nd);

          reset(val);
        }

      else
        if(nd == "string_literal")
        {
          auto  s = new std::string;

          nd.collect_characters(*s);

          reset(new Value(s));
        }

      else
        if(nd == "character_literal")
        {
          auto  val = new Value;

          val->read_character_literal(nd);

          reset(val);
        }

      else
        if(nd == "function_literal")
        {
/*
          auto  v = new Value(read_function_literal(nd));

          ls.emplace_back(new Operand(v));
*/
        }

      else
        if(nd == "calling")
        {
          auto  ca = new Calling;

          ca->read(nd);

          reset(ca);
        }

      else
        if(nd == "null")
        {
          clear();
        }

      else
        if(nd == "true")
        {
          reset(new Value(true));
        }

      else
        if(nd == "false")
        {
          reset(new Value(false));
        }

      else
        if(nd == "undefined")
        {
          reset(new Value(ValueKind::undefined));
        }


      cur.advance();
    }
}




}






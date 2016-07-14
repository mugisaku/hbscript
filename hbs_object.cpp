#include"hbs_object.hpp"




Object::
Object(std::string&&  id, int  flags_, ObjectKind  k, int  v):
Parameter(std::move(id),flags),
kind(k),
value(v)
{
}




Value
Object::
get_value(Memory&  mem) const
{
    switch(kind)
    {
      case(ObjectKind::auto_variable):
      case(ObjectKind::static_variable):
      case(ObjectKind::reference):
        return Value(Reference(Pointer(value)));
        break;
      case(ObjectKind::enumerator):
        break;
    }


  return Value::undefined;
}


void
Object::
print(const Memory&  mem) const
{
    switch(kind)
    {
      case(ObjectKind::auto_variable):
        printf("auto var ");
        break;
      case(ObjectKind::static_variable):
        printf("static var ");
        break;
      case(ObjectKind::enumerator):
        printf("enumerator ");
        break;
    }


  Parameter::print();

  printf("(%d)",value);
}





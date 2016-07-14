#include"hbs_parameter.hpp"




Parameter::
Parameter(std::string&&  id, int  flags_):
identifier(std::move(id)),
flags(flags_)
{
}




void
Parameter::
print() const
{
  printf("%s",identifier.data());
}





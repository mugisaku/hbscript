#ifndef HBSCRIPT_PARAMETER_HPP_INCLUDED
#define HBSCRIPT_PARAMETER_HPP_INCLUDED


#include<string>




struct
Parameter
{
  static constexpr int      const_flag = 1;
  static constexpr int  reference_flag = 2;
  static constexpr int     static_flag = 4;

  std::string  identifier;

  int  flags;

  Parameter();
  Parameter(std::string&&  id, int  flags_=0);

  void  print() const;

};




#endif





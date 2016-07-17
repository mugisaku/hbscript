#ifndef HBSCRIPT_STRUCTURE_HPP_INCLUDED
#define HBSCRIPT_STRUCTURE_HPP_INCLUDED


#include"hbs_value.hpp"
#include<list>




struct Memory;


struct
StructureMember
{
  const std::string  identifier;

  Pointer  pointer;

  StructureMember(std::string&&  id, Pointer  ptr):
  identifier(std::move(id)),
  pointer(ptr){}

};


struct
Structure
{
  Memory&  memory;

  std::list<StructureMember>  member_list;

   Structure(Memory&  mem);
  ~Structure(            );

  StructureMember&  get_member(const std::string&  id);

  void  remove_member(const std::string&  id);

  void  print() const;

};




#endif





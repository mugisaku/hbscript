#ifndef HBSCRIPT_STRUCTURE_HPP_INCLUDED
#define HBSCRIPT_STRUCTURE_HPP_INCLUDED

#include"hbs_object.hpp"



struct
StructureMemberDefinition
{
  std::string  identifier;

  ObjectKind  kind;

};


using StructureDefinition = std::vector<StructureMemberDefinition>;


struct
Structure
{
  const StructureDefinition&  definition;

  std::vector<Object>  members;

};


#endif





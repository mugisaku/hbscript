#ifndef HBSCRIPT_MEMORY_HPP_INCLUDED
#define HBSCRIPT_MEMORY_HPP_INCLUDED


#include"hbs_value.hpp"
#include<vector>




class
Memory
{
  size_t  size;

  Value*  table;

  size_t  allocate_size;

  std::vector<Pointer>  freed_pointer_list;

public:
   Memory(size_t  size_);
  ~Memory();


  void  clear();

  void  resize(size_t  new_size);

  size_t  get_size() const;

  Value&  derefer(Pointer  ptr) const;

  Value&  operator[](Pointer  ptr) const;

  Pointer  allocate();

  void  free(Pointer  ptr);
 
};




#endif





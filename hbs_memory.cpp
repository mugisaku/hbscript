#include"hbs_memory.hpp"




Memory::
Memory(size_t  size_):
size(0),
table(nullptr),
allocate_size(1)
{
  resize(size_);
}


Memory::
~Memory()
{
  clear();
}




void
Memory::
clear()
{
  delete[] table          ;
           table = nullptr;

  size = 0;

  allocate_size = 1;

  freed_pointer_list.clear();
}


void
Memory::
resize(size_t  new_size)
{
  clear();


  table = new Value[new_size];

  size = new_size;
}


size_t
Memory::
get_size() const
{
  return size;
}


Value&
Memory::
derefer(Pointer  ptr) const
{
    if(ptr && (ptr < size))
    {
      return table[ptr];
    }


  throw;
}


Value&
Memory::
operator[](Pointer  ptr) const
{
  return derefer(ptr);
}


Pointer
Memory::
allocate()
{
  Pointer  ptr;

    if(freed_pointer_list.size())
    {
      ptr.value = freed_pointer_list.back();

      freed_pointer_list.pop_back();
    }

  else
    {
      ptr.value = allocate_size++;
    }


  return ptr;
}


void
Memory::
free(Pointer  ptr)
{
  freed_pointer_list.emplace_back(ptr);
}





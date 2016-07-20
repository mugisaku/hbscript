#include"hbs_memory.hpp"
#include<new>




Memory::
Memory(size_t  size_):
table(nullptr),
allocated_size(1)
{
    if(!size_)
    {
      size_ = 1024;
    }


  table = static_cast<Value*>(malloc(sizeof(Value)*size_));

  new(table) Value[size_];

  table_size = size_;
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
    for(int  i = 0;  i < allocated_size;  ++i)
    {
      table[i].~Value();
    }


  ::free(table);

      table_size = 0;
  allocated_size = 0;

  freed_pointer_list.clear();
}


size_t
Memory::
get_size() const
{
  return allocated_size;
}


Value&
Memory::
get_value(Pointer  ptr) const
{
    if(ptr && (ptr < allocated_size))
    {
      return table[ptr];
    }


  throw;
}


Value&
Memory::
operator[](Pointer  ptr) const
{
  return get_value(ptr);
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
    if(allocated_size >= table_size)
    {
      size_t  new_size = table_size*2;

      auto  new_table = static_cast<Value*>(malloc(sizeof(Value)*new_size));

      new(new_table) Value[new_size];

        for(int  i = 0;  i < allocated_size;  ++i)
        {
          new_table[i] = std::move(table[i])        ;
                                   table[i].~Value();
        }


      ::free(table)           ;
             table = new_table;

      table_size = new_size;
    }


  ptr.value = allocated_size++;

  return ptr;
}


void
Memory::
free(Pointer  ptr)
{
  freed_pointer_list.emplace_back(ptr);
}





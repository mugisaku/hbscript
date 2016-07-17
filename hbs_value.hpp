#ifndef HBS_VALUE_HPP_INCLUDED
#define HBS_VALUE_HPP_INCLUDED


#include<string>
#include"libmkf/mkf_node.hpp"
#include"libmkf/mkf_cursor.hpp"


#ifndef report
#define report  printf("[report in %s] %d %s\n",__FILE__,__LINE__,__func__);
#endif


struct Function;
struct Variable;
struct Memory;


namespace expression{
struct Node;
struct Element;
}


struct
Pointer
{
  int32_t  value;

  constexpr Pointer(int32_t  val=0): value(val){};

  constexpr operator int32_t() const{return value;}

  constexpr Pointer  operator+(const Pointer&  rhs) const
  {
    return Pointer(value+rhs.value);
  }

};


struct
Reference
{
  Pointer  pointer;

  explicit constexpr Reference(const Pointer&  ptr): pointer(ptr){};

};




enum class
ValueKind
{
  null,

  void_,
  undefined,
  reference,
  
  pointer,
  integer,
  boolean,
  string,
  function,
  structure,
  array,

};


struct
Value
{
  ValueKind  kind;

  union{
    int             i;
    std::string*    s;
    Function*      fn;

  } data;


  Value(ValueKind  k=ValueKind::null);
  Value(int  i);
  Value(bool  b);
  Value(std::string*  s_);
  Value(Function*  fn);
  Value(const Pointer&  ptr);
  Value(const Reference&  ref);
  Value(const Value&   rhs);
  Value(      Value&&  rhs) noexcept;
 ~Value();


  Value&  operator=(const Value&   rhs);
  Value&  operator=(      Value&&  rhs);


  void  clear();

  void  reset(ValueKind  k=ValueKind::null);
  void  reset(int  i);
  void  reset(bool  b);
  void  reset(std::string*  s_);
  void  reset(Function*  fn);
  void  reset(const Pointer&  ptr);
  void  reset(const Reference&  ref);

        Value&  dereference(Memory&  mem)      ;
  const Value&  dereference(Memory&  mem) const;

  const int&   get_integer() const;
  int&         get_integer()      ;

  void  print(const Memory&  mem) const;

  void  read(const mkf::Node&  src);
  void  read_integer_literal(const mkf::Node&  src);
  void  read_character_literal(const mkf::Node&  src);


  Value     indirect(Memory&  mem) const;
  Value  get_address(Memory&  mem) const;
  Value       invert(Memory&  mem) const;
  Value      bit_not(Memory&  mem) const;
  Value  logical_not(Memory&  mem) const;

  Value  operate_add(Memory&  mem, const Value&  rhs) const;
  Value  operate_sub(Memory&  mem, const Value&  rhs) const;
  Value  operate_mul(Memory&  mem, const Value&  rhs) const;
  Value  operate_div(Memory&  mem, const Value&  rhs) const;
  Value  operate_rem(Memory&  mem, const Value&  rhs) const;
  Value  operate_bit_or(Memory&  mem, const Value&  rhs) const;
  Value  operate_bit_and(Memory&  mem, const Value&  rhs) const;
  Value  operate_bit_xor(Memory&  mem, const Value&  rhs) const;
  Value  operate_shl(Memory&  mem, const Value&  rhs) const;
  Value  operate_shr(Memory&  mem, const Value&  rhs) const;

  Value  operate_add_assign(Memory&  mem, const Value&  rhs);
  Value  operate_sub_assign(Memory&  mem, const Value&  rhs);
  Value  operate_mul_assign(Memory&  mem, const Value&  rhs);
  Value  operate_div_assign(Memory&  mem, const Value&  rhs);
  Value  operate_rem_assign(Memory&  mem, const Value&  rhs);
  Value  operate_bit_or_assign(Memory&  mem, const Value&  rhs);
  Value  operate_bit_and_assign(Memory&  mem, const Value&  rhs);
  Value  operate_bit_xor_assign(Memory&  mem, const Value&  rhs);
  Value  operate_shl_assign(Memory&  mem, const Value&  rhs);
  Value  operate_shr_assign(Memory&  mem, const Value&  rhs);
  Value  operate_assign(Memory&  mem, const Value&  rhs);

  Value  operate_eq(Memory&  mem, const Value&  rhs) const;
  Value  operate_neq(Memory&  mem, const Value&  rhs) const;
  Value  operate_lt(Memory&  mem, const Value&  rhs) const;
  Value  operate_lteq(Memory&  mem, const Value&  rhs) const;
  Value  operate_gt(Memory&  mem, const Value&  rhs) const;
  Value  operate_gteq(Memory&  mem, const Value&  rhs) const;
  Value  operate_logical_or(Memory&  mem, const Value&  rhs) const;
  Value  operate_logical_and(Memory&  mem, const Value&  rhs) const;

  static const Value  undefined;

};




#endif





#ifndef HBS_EXPRESSION_NODE_HPP_INCLUDED
#define HBS_EXPRESSION_NODE_HPP_INCLUDED


#include"hbs_expression_element.hpp"




namespace expression{


struct
Node
{
  Element  element;

  Node*   left;
  Node*  right;

   Node();
   Node(const Element&   el);
   Node(      Element&&  el);
   Node(const Node&   rhs);
   Node(      Node&&  rhs) noexcept;
  ~Node();


  Node&  operator=(const Node&   rhs);
  Node&  operator=(      Node&&  rhs);
  Node&  operator=(const Element&   el);
  Node&  operator=(      Element&&  el);

  operator bool() const;

  void  clear();

  bool  test_leaf() const;

  Value  get_value(Context&  ctx) const;

  void  make(ElementList&&  ls);

  void  print(const Memory&  mem) const;

  void  read(const mkf::Node&  src, Memory&  mem);

};


}


#endif





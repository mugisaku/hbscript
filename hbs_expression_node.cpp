#include"hbs_expression_node.hpp"
#include"hbs_block.hpp"
#include"hbs_context.hpp"
#include"hbs_structure.hpp"




namespace expression{


Node::
Node():
left(nullptr),
right(nullptr)
{
}


Node::
Node(const Element&  el):
left(nullptr),
right(nullptr)
{
  *this = el;
}


Node::
Node(Element&&  el):
left(nullptr),
right(nullptr)
{
  *this = std::move(el);
}


Node::
Node(Node&&  rhs) noexcept:
left(nullptr),
right(nullptr)
{
  *this = std::move(rhs);
}


Node::
Node(const Node&  rhs):
left(nullptr),
right(nullptr)
{
  *this = rhs;
}


Node::
~Node()
{
  clear();
}




Node&
Node::
operator=(const Node&  rhs)
{
  clear();

  element = rhs.element;

   left = rhs.left ? new Node(*rhs.left ):nullptr;
  right = rhs.right? new Node(*rhs.right):nullptr;

  return *this;
}


Node&
Node::
operator=(Node&&  rhs)
{
  clear();

  element = std::move(rhs.element);

  std::swap( left, rhs.left);
  std::swap(right,rhs.right);

  return *this;
}


Node&
Node::
operator=(const Element&  el)
{
  clear();

  element = el;

  return *this;
}


Node&
Node::
operator=(Element&&  el)
{
  clear();

  element = std::move(el);

  return *this;
}


Node::
operator bool() const
{
  return(element.kind != ElementKind::null);
}


void
Node::
clear()
{
  element.clear();

  delete left          ;
         left = nullptr;

  delete right          ;
         right = nullptr;
}


bool
Node::
test_leaf() const
{
  return(!left && !right);
}


void
Node::
print(const Memory&  mem) const
{
    if(element.kind == ElementKind::null)
    {
      return;
    }


    if(element.kind == ElementKind::operand)
    {
      element.print(mem);

      return;
    }


    if(element.kind == ElementKind::unary_operator)
    {
      element.print(mem);
    }


    if(left)
    {
        if(!left->test_leaf())
        {
          printf("(");
        }


      left->print(mem);

        if(!left->test_leaf())
        {
          printf(")");
        }
    }


    if((element.kind == ElementKind::binary_operator) ||
       (element.kind == ElementKind::assign_operator))
    {
      element.print(mem);
    }


    if(right)
    {
        if(!right->test_leaf())
        {
          printf("(");
        }


      right->print(mem);

        if(!right->test_leaf())
        {
          printf(")");
        }
    }
}


}






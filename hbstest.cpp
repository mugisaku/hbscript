#include"hbs_block.hpp"
#include"hbs_function.hpp"
#include"hbs_context.hpp"
#include"libmkf/mkf_book.hpp"
#include"libmkf/mkf_file.hpp"
#include"libmkf/mkf_parsecontext.hpp"
#include<cstdlib>




int
xorshift32(int&  y)
{
  y = y ^ (y << 13);
  y = y ^ (y >> 17);

  return y = y ^ (y << 5);
}


int
main(int  argc, char**  argv)
{
  Memory  mem(800);

  Block  globblk;

  mkf::Book  book;

  auto  def = load_file("hbsdef.txt");
  auto  txt = load_file("test.hbs");

    if(!book.make(def))
    {
      return -1;
    }


  book.print();

  mkf::ParseContext  ctx(book);

  auto  root = ctx(txt);

    if(root)
    {
      root->print();

      globblk.read(*root,mem,0);

      globblk.print(mem);

      Context  ctx(mem,globblk);

      auto  obj = ctx.find_object("main");

        if(obj)
        {
          auto&  fn = *mem[obj->value].data.fn;

          Calling  ca = {"main",{}};

          auto  retval = ctx.call(fn,ca);

          retval.print(mem);

          printf("\n");
        }
    }


  int  seed = 123456789;

    for(int  i = 0;  i <= 80;  i += 1)
    {
      printf("%d\n",xorshift32(seed));
    }


  return 0;
}





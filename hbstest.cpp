#include"hbs_block.hpp"
#include"hbs_function.hpp"
#include"libmkf/mkf_book.hpp"
#include"libmkf/mkf_file.hpp"
#include"libmkf/mkf_parsecontext.hpp"
#include<cstdlib>




int
main(int  argc, char**  argv)
{
  Memory  mem(800);

  Function  globblk;

  mkf::Book  book;

  auto  def = load_file("hbsdef.txt");
  auto  txt = load_file("test.hbs");

    if(!book.make(def))
    {
      return -1;
    }


//  book.print();

  mkf::ParseContext  ctx(book);

  auto  root = ctx(txt);

    if(root)
    {
      root->print();

      globblk.Block::read(*root,mem,0);

      globblk.print(mem);

      Context  ctx(mem,globblk.get_static_object_list());

      auto  obj = ctx.find_object("main");

        if(obj)
        {
          auto&  fn = *mem[obj->value].data.fn;

          Calling  ca = {"main",{}};

          auto  retval = ctx.call(fn,ca);

          retval.print(mem);

          printf("\n");

          ctx.print();
        }
    }


  return 0;
}





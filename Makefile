BASE_DIR = /usr/local




CXXFLAGS = -std=gnu++11 -I. -Werror -Wno-unused-result


ifeq ($(opt),1)
  CXXFLAGS += -Os -march=i686 -fomit-frame-pointer
  LDFLAGS  += -s
else
  CXXFLAGS += -g
endif


COMMON_LDFLAGS = -lstdc++


ifeq ($(mingw),1)
  EXE_EXT = .exe
  DIR_PREFIX = i686-w64-mingw32
  CMD_PREFIX = $(DIR_PREFIX)-
  LDFLAGS = $(COMMON_LDFLAGS) -lmingw32 -static
else
  LDFLAGS = $(COMMON_LDFLAGS)
endif




ifeq ($(ccache),1)
  CXX = CCACHE_DIR=/tmp/ccachedir ccache $(CMD_PREFIX)g++
else
  CXX = $(CMD_PREFIX)g++
endif



STRIP = $(CMD_PREFIX)strip
AR    = $(CMD_PREFIX)ar

CXXFLAGS += -I$(BASE_DIR)/$(DIR_PREFIX)/include
LDFLAGS  += -L$(BASE_DIR)/$(DIR_PREFIX)/lib


ifeq ($(delay),1)
%.o : %.cpp
	$(CXX) -c $(CXXFLAGS)  $< -o $@
	sleep 1
endif


BIN = hbs$(EXE_EXT)


OBJ +=                         \
  hbs_statement.o              \
  hbs_statement__read.o        \
  hbs_parameter.o              \
  hbs_object.o                 \
  hbs_value.o                  \
  hbs_value__read_integer.o    \
  hbs_value__read_character.o  \
  hbs_value__reset.o           \
  hbs_value__unop.o            \
  hbs_value__binop.o           \
  hbs_memory.o                 \
  hbs_calling.o                \
  hbs_context.o                \
  hbs_expression_node.o        \
  hbs_expression_node__make.o  \
  hbs_expression_node__read.o  \
  hbs_expression_operand.o     \
  hbs_expression_element.o     \
  hbs_function.o               \
  hbs_function__start.o        \
  hbs_block.o                  \


all: $(BIN)


clean:
	make -C libmkf clean
	rm -f $(OBJ) $(BIN) hbstest.o


objects:
	make -C libmkf objects


archive: clean
	tar -cJ ../hbscript-git > ../hbscript-git.tar.xz


$(BIN): $(OBJ) objects hbstest.o
	$(CXX) -o $@ *.o libmkf/*.o $(CXXFLAGS) $(LDFLAGS)
ifeq ($(opt),1)
	$(STRIP) --strip-unneeded  $(BIN)
endif





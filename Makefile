# Specify the target file and the install directory
SRC         = src
INC         = include
LIB 				= lib

CLEANEXTS   = o a gcno
CC					= g++
CFLAGS			= -Wall -fexceptions -g -I$(INC) -I/usr/include -fprofile-arcs -ftest-coverage
LIBS				= -L$(LIB) -lgcov

_DEPS = utils.h c_tree_node.h c_tikz_obj.h c_scene_manager.h c_polygon.h c_point.h common.h c_node.h c_line.h c_camera.h catch.hpp
DEPS = $(patsubst %,$(INC)/%,$(_DEPS))

_OBJ = c_camera.o c_line.o c_node.o c_point.o c_polygon.o c_scene_manager.o c_tests.o c_tikz_obj.o c_tree_node.o utils.o
OBJ = $(patsubst %,%,$(_OBJ))

OUTPUTFILE = tikz3d

# Default target
.PHONY: all
all: $(OUTPUTFILE)

$(OUTPUTFILE): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean
clean:
	rm -f *.o *~ core $(INC)/*~
	rm -f *.gcno *~ core $(INC)/*~
	rm -f *.gcda *~ core $(INC)/*~
	rm $(OUTPUTFILE)

# Dependencies

%.o: $(SRC)/%.cpp $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $< $(LIBS)

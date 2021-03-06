CC=clang
LINKER=g++
SRC=$(shell ls *.cc)
OBJ=$(SRC:%.cc=%.o)
CORE=rtr
INC=
SDLCONFIG_LIBS=$(shell sdl-config --libs)
SDLCONFIG_CFLAGS=$(shell sdl-config --cflags)
LIB=$(SDLCONFIG_LIBS) -lSDL_image -lSDL_ttf -lpng
CFLAGS=$(SDLCONFIG_CFLAGS) -g -O3 -Wall

$(CORE): $(OBJ)
	$(LINKER) $(OBJ) $(LIB) -o $(CORE)

$(OBJ): %.o: %.cc
	$(CC) $(INC) $(CFLAGS) -c $<

clean:
	rm -rf $(CORE) $(OBJ) *.o

new: clean $(CORE)

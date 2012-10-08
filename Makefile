CC=g++
SRC=$(shell ls *.cc)
OBJ=$(SRC:%.cc=%.o)
CORE=rtr
INC=
CFLAGS=-Wall -g

$(CORE): $(OBJ)
	$(CC) $(OBJ) $(LIB) -o $(CORE)

$(OBJ): %.o: %.cc
	$(CC) $(INC) $(CFLAGS) -c $<

clean:
	rm -rf $(CORE) $(OBJ) *.o

new: clean $(CORE)

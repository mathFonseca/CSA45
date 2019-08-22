# ##################################################### #
# Compiler
# ##################################################### #
CC = g++


# ##################################################### #
# Paths
# ##################################################### #
LIB = ./lib
INCLUDE = ./include
SRC = ./src
OBJ = ./obj

VPATH = $(SRC) $(INCLUDE)


# ##################################################### #
# Object files
# ##################################################### #
OBJ1 = cgTypes.o
OBJ2 = cgPrimitives.o
OBJ3 = cgImage.o

OBJS = $(OBJ)/$(OBJ1) $(OBJ)/$(OBJ2) $(OBJ)/$(OBJ3) 


# ##################################################### #
# Program flags
# ##################################################### #
PFLAGS = -Wall -W -Wpointer-arith -Wcast-qual \
         -Wcast-align -Wmissing-declarations \
         -Winline -O3 -g


# ##################################################### #
# Rules
# ##################################################### #
libgeo: $(LIB)/libcg.a

$(LIB)/libcg.a: $(OBJS)
	ar csr $@ $^

$(OBJ)/$(OBJ1): $(OBJ1:.o=.c) $(OBJ1:.o=.h)
	$(CC) $(PFLAGS) -c $< -I$(INCLUDE) -o $@

$(OBJ)/$(OBJ2): $(OBJ2:.o=.c) $(OBJ2:.o=.h)
	$(CC) $(PFLAGS) -c $< -I$(INCLUDE) -o $@

$(OBJ)/$(OBJ3): $(OBJ3:.o=.c) $(OBJ3:.o=.h)
	$(CC) $(PFLAGS) -c $< -I$(INCLUDE) -o $@

.PHONY: oclean clean

oclean: 
	rm -f $(OBJS)

clean: oclean
	rm -f $(LIB)/libcg.a

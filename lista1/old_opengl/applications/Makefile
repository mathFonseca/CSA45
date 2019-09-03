CC = g++

INC  = ../include
LIB  = ../lib
OBJ  = ../obj
BIN  = .

PFLAGS = -Wall -W -Wpointer-arith -Wcast-qual \
         -Wcast-align -Wmissing-declarations \
         -Winline -O3 -g

GLLIBS = -lglut -lGL -lGLU -lm

$(LIB)/libcg.a:
	cd ..; make; cd applications
        
appWindow: $(LIB)/libcg.a appWindow.cpp
	$(CC) $(PFLAGS) appWindow.cpp -o $(BIN)/appWindow -I$(INC) -L$(LIB) -lcg $(GLLIBS)

appTriangles: $(LIB)/libcg.a appTriangles.cpp
	$(CC) $(PFLAGS) appTriangles.cpp -o $(BIN)/appTriangles -I$(INC) -L$(LIB) -lcg $(GLLIBS)

appColoredTriangle: $(LIB)/libcg.a appColoredTriangle.cpp
	$(CC) $(PFLAGS) appColoredTriangle.cpp -o $(BIN)/appColoredTriangle -I$(INC) -L$(LIB) -lcg $(GLLIBS)

appPoints: $(LIB)/libcg.a appPoints.cpp
	$(CC) $(PFLAGS) appPoints.cpp -o $(BIN)/appPoints -I$(INC) -L$(LIB) -lcg $(GLLIBS)

appImage: $(LIB)/libcg.a appImage.cpp
	$(CC) $(PFLAGS) appImage.cpp -o $(BIN)/appImage -I$(INC) -L$(LIB) -lcg

exercicio_1: $(LIB)/libcg.a exercicio1.cpp
	$(CC) $(PFLAGS) exercicio1.cpp geo.cpp -o $(BIN)/exercicio1 -I$(INC) -L$(LIB) -lcg $(GLLIBS) 

exercicio_2: $(LIB)/libcg.a exercicio2.cpp
	$(CC) $(PFLAGS) exercicio2.cpp geo.cpp -o $(BIN)/exercicio2 -I$(INC) -L$(LIB) -lcg $(GLLIBS) 


.PHONY: clean

clean:
	cd ../; make clean; cd applications
	rm -f appWindow appTriangles appColoredTriangle \
	      appImage appPoints

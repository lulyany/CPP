CXX = g++ -std=c++11
CXXFLAGS =  -Werror -Wpedantic -Wall -Wextra 
LBLIBS = -lm -lGL -lGLU -lglut -lpthread

SRC1 =demo.cpp Ticket.cpp Vehicle.cpp 
OBJ1 = $(SRC1:.cc=.o)
EXEC1 = p3_part1

SRC2=drawcar.cpp
OBJ2 = $(SRC2:.cc=.o)
EXEC2 = p3_part2


all: $(EXEC1) $(EXEC2)

$(EXEC1): $(OBJ1)
	$(CXX) -o $@ $(OBJ1)

$(EXEC2): $(OBJ2)
	$(CXX) -o $@ $(OBJ2) $(LBLIBS)

clean:
	rm -rf $(OBJ1)$(OBJ2) $(EXEC1) $(EXEC2)
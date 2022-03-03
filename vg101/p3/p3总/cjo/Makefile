CXX = g++ -std=c++11
CXXFLAGS =  -Werror -Wpedantic -Wall -Wextra 

SRC =demo.cpp Ticket.cpp Vehicle.cpp 
OBJ = $(SRC:.cc=.o)
EXEC = demo

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CXX) $(LDFLAGS) -o $@ $(OBJ) $(LBLIBS)

clean:
	rm -rf $(OBJ) $(EXEC)
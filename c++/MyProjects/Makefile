TARGET = PlayChess
CXX = g++

PREF_SRC = ./chess/src/
PREF_OBJ = ./chess/obj/

SRC = $(wildcard $(PREF_SRC)*.cpp)
OBJ = $(patsubst $(PREF_SRC)%.cpp, $(PREF_OBJ)%.o, $(SRC))

$(TARGET) : $(OBJ)
	$(CXX) -g -std=c++17 $(OBJ) -o $(TARGET) -lX11 -lGL -lpng -lpthread

$(PREF_OBJ)%.o : $(PREF_SRC)%.cpp
	$(CXX) -g -std=c++17 -c $< -o $@
	
clean :
	rm $(TARGET) $(PREF_OBJ)*.o

TARGET = PlayChess
CXX = g++

PREF_SRC = ./chess/src/
PREF_OBJ = ./chess/obj/

SRC = $(wildcard $(PREF_SRC)*.cpp)
OBJ = $(patsubst $(PREF_SRC)%.cpp, $(PREF_OBJ)%.o, $(SRC))

$(TARGET) : $(OBJ) ./ChessGUI/main.o
	$(CXX) -std=c++17 ./ChessGUI/main.o $(OBJ) -o $(TARGET) -lX11 -lGL -lpng -lpthread

./ChessGUI/main.o : ./ChessGUI/main.cpp
	$(CXX) -std=c++17 -c ./ChessGUI/main.cpp -o ./ChessGUI/main.o

$(PREF_OBJ)%.o : $(PREF_SRC)%.cpp
	$(CXX) -std=c++17 -c $< -o $@

clean :
	rm $(TARGET) $(PREF_OBJ)*.o
	rm ./ChessGUI/main.o

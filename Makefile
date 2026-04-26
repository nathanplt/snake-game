CXX = clang++
CXXFLAGS = -std=c++17 -O3
TARGET = game

HEADERS = src/app.hpp src/game.hpp src/utils.hpp src/types.hpp
SRC = main.cpp src/app.cpp src/game.cpp src/utils.cpp

all: $(TARGET)

$(TARGET): $(SRC) $(HEADERS)
	$(CXX) $(CXXFLAGS) -o $@ $(SRC)


clean:
	@rm -f src/*.o *.o $(TARGET) 2>/dev/null

run:
	@./game

.PHONY: clean run all

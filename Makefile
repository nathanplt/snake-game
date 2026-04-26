CXX = clang++
CXXFLAGS = -std=c++17
TARGET = game

SRC = main.cpp src/app.cpp src/game.cpp src/utils.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	@rm src/*.o *.o $(TARGET) 2>/dev/null

run:
	@./game

PHONY: clean run

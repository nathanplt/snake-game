CXX = clang++
CXXFLAGS =
TARGET = app

all: $(TARGET)

$(TARGET): src/app.cpp src/game.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm src/*.o *.o $(TARGET)

run:
	@./app

PHONY: clean run

CXX = clang++
CXXFLAGS =
TARGET = app

all: $(TARGET)

$(TARGET): src/app.o
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm src/*.o $(TARGET)

run:
	@./app

PHONY: clean run

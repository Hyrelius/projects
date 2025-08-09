#done by ai because again i have no idea how to makefile
# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -O2

# Find all .cpp files recursively starting from current directory
SRC := $(shell find . -name '*.cpp')

# Create object files list (.o files replacing .cpp)
OBJ := $(SRC:.cpp=.o)

# Output executable
OUT = main

# Default build target
all: $(OUT)

# Link all object files into executable
$(OUT): $(OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Compile .cpp files into .o files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build files
clean:
	rm -f $(OBJ) $(OUT)

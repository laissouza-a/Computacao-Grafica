# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -std=c++11

# Libraries
LIBS = -lglfw -lGL -lGLEW

# Executable name
TARGET = flor

# Source files
SRCS = florDeAbril.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Build target
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) $(LIBS)

# Clean up build files
clean:
	rm -f $(OBJS) $(TARGET)

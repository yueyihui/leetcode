# Define the compilers
CC := gcc
CXX := g++

# Define the compiler flags
CFLAGS += -g -O0 -I./uthash/include -std=c11
CXXFLAGS += -g -O0

# Define the linker flags
LDFLAGS += -lm

# Define the source files
C_SRCS := $(wildcard *.c)
CXX_SRCS := $(wildcard *.cpp)

# Define the object files
C_OBJS := $(C_SRCS:.c=.o)
CXX_OBJS := $(CXX_SRCS:.cpp=.o)
OBJS := $(C_OBJS) $(CXX_OBJS)

# Define the target executables
C_TARGETS := $(C_SRCS:.c=)
CXX_TARGETS := $(CXX_SRCS:.cpp=)
TARGETS := $(C_TARGETS) $(CXX_TARGETS)

# Default target
all: $(TARGETS)

# Rule to link the object files into the final executables
$(C_TARGETS): %: %.o
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)

$(CXX_TARGETS): %: %.o
	$(CXX) $(CXXFLAGS) -o $@ $< $(LDFLAGS)

# Rule to compile C source files into object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to compile C++ source files into object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up the build files
clean:
	@rm -f $(OBJS) $(TARGETS)

# Phony targets
.PHONY: all clean


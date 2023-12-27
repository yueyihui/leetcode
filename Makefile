CFLAGS+= -g -O3
CC:=gcc
CXXFLAGS+= -g -O3

TARGET:= $(basename $(wildcard *.c), $(wildcard *.cpp))

all: $(TARGET)

clean:
	rm -f $(TARGET)

#.DEFAULT_GOAL=all

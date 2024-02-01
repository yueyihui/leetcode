CFLAGS+= -g -O0 -I./uthash/include
CC:=gcc
CXXFLAGS+= -g -O0

TARGET:= $(basename $(wildcard *.c), $(wildcard *.cpp))

all: $(TARGET)

clean:
	rm -f $(TARGET)

#.DEFAULT_GOAL=all

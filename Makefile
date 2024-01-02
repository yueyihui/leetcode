CFLAGS+= -g -O3 -I./uthash/include
CC:=gcc
CXXFLAGS+= -g -O3

TARGET:= $(basename $(wildcard *.c), $(wildcard *.cpp))

all: $(TARGET)

clean:
	rm -f $(TARGET)

#.DEFAULT_GOAL=all

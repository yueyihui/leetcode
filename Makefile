CFLAGS+= -g -O3

a:a.c
b:b.c
c:c.c
d:d.c
e:e.c

all: a b c d e

clean:
	rm -f a b c d e

.DEFAULT_GOAL=all

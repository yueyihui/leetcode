b:b.c
c:c.c
d:d.c
e:e.c

all: b c d e

clean:
	rm b c d e

.DEFAULT_GOAL=all

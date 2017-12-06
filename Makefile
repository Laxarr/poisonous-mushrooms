
FILES= parser.c parser.h string.c string.h scanner.c scanner.h debug.h debug.c expr.c expr.h stack.c stack.h symtable.c symtable.h codegenerator.c codegenerator.h
CFLAGS = -Wextra -pedantic 

# CFLAGS = -Wall -Wextra -std=c99 -pedantic 

all: ifj17

ifj17: $(FILES)
	gcc $(CFLAGS) -o ifj17 $(FILES)
clean:
	rm -f *.o *.out ifj17


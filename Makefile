
FILES= parser.c string.c string.h scanner.c
CFLAGS = -Wextra -pedantic 

# CFLAGS = -Wall -Wextra -std=c99 -pedantic 
# nwm jestli neprejmenovat vystupni soubor

all: ifj17

ifj17: $(FILES)
  gcc $(CFLAGS) -o ifj17 $(FILES)
clean:
	rm -f *.o *.out ifj17


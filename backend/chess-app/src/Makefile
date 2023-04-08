CC=gcc 
CFLAGS=-Wall -Wextra -pedantic -std=c99
DEPS=table.h
OBJ=table.o main.o

%.o: %.c $(DEPS)
	$(CC) -c -shared -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

run: $(OBJ)
	@./main

clean:
	rm -f $(OBJ) main
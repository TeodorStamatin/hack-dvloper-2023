CC=gcc 
CFLAGS=-Wall -Wextra -pedantic -std=c99
DEPS=table.h
OBJ=table.o main.o

HEADERS = $(wildcard ./${HEADERS_PATH}/*.h)
SRC = $(wildcard $(SRC_PATH)/*.c)
EXEC = $(patsubst ${SRC_PATH}/%.c,%,$(SRC))

%.so: %.c $(DEPS)
	$(CC) -c -shared -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

run: $(OBJ)
	@./main

clean:
	rm -f $(OBJ) main
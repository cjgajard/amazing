CC=gcc
CFLAGS=-Wall -g
CLIBS=

OUT=amazing.out
OBJ=main.o maze.o stack.o

.PHONY: auto clean build run
auto: $(OUT)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	-rm -f *.o
	-rm -f $(OUT)

$(OUT): $(OBJ)
	$(CC) -o $(OUT) $^ $(LIBS)

build: $(OUT)

run: $(OUT)
	./$(OUT)

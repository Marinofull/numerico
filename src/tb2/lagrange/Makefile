SOURCE = lagrange.c
CC = gcc
CFLAGS = -c
LFLAGS =
BIN = main

all: $(SOURCE)
	$(CC) -o $(BIN) $(SOURCE)

clean:
	\rm $(BIN)

$(BIN): all
	echo "done"

run: $(BIN)
	./$(BIN) < tests/input/in1

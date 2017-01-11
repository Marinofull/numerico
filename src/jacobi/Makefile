OBJS = Sistemalinear.o Main.o
CC = gcc
CFLAGS = -c
LFLAGS =
BIN = jacobi

Main : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o $(BIN)

Sistemalinear : Sistemalinear.h Sistemalinear.c
	$(CC) $(CFLAGS) Sistemalinear.c

run:
	./$(BIN) ma mb mx 0.3 5 # lancamento

clean:
	rm -f $(BIN) *.o

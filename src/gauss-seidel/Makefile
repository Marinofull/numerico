OBJS = Sistemalinear.o Main.o
CC = gcc
CFLAGS = -c
LFLAGS = 

Main : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o Main

Sistemalinear : Sistemalinear.h Sistemalinear.c
	$(CC) $(CFLAGS) Sistemalinear.c
	
clean:
	\rm *.o Main

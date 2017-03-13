OBJS = Polinomio.o Main.o
CC = gcc
CFLAGS = -c
LFLAGS =

Main : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o Main

Polinomio : Polinomio.h Polinomio.c
	$(CC) $(CFLAGS) Polinomio.c
	
clean:
	\rm *.o
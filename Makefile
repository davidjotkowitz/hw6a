CC=gcc
CCLINK=$(CC) # Read variable CC using $(CC)
CFLAGS=-g -Wall -std=c99
OBJS=ransom.o
EXEC=prog.exe
RM=rm -rf *.o *.exe


all: $(OBJS)
	$(CCLINK) $(OBJS) -o $(EXEC)

ransom.o: ransom.c
	$(CC) $(CFLAGS) -c ransom.c


clean:
	$(RM)

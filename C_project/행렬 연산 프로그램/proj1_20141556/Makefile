CC = gcc
CFLAGS = -W -Wall
TARGET = 20141556.out
SRCS = 20141556.h 20141556.c
OBJECTS = 20141556.o

$(TARGET):$(OBJECTS)
	$(CC) -o $(TARGET) $(OBJECTS) $(CFLAGS)

$(OBJECTS): 20141556.c
	$(CC) -c 20141556.c $(CFLAGS)

clean:
	rm -rf *.o *.out

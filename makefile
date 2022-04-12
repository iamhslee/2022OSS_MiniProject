CC = gcc
CFLAGS = -W -Wall

TARGET = shop
DTARGET = shop_debug
OBJECTS = main.c manager.c

all : $(TARGET)

$(TARGET) : $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

$(DTARGET) : $(OBJECTS)
	$(CC) $(CFLAGS) -DDEBUG -o $@ $^

clean :
	rm shop shop_debug *.o

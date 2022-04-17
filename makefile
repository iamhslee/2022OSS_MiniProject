CC = gcc
CFLAGS = -W -Wall

TARGET = shop
DTARGET = shop_debug
OBJECTS = main.c manager.c

all : $(TARGET)

$(TARGET) : $(OBJECTS)
	echo "Build target : $(TARGET)"
	$(CC) $(CFLAGS) -o $@ $^

$(DTARGET) : $(OBJECTS)
	echo "Build target : $(DTARGET)"
	$(CC) $(CFLAGS) -DDEBUG -o $@ $^

clean :
	rm shop shop_debug *.o

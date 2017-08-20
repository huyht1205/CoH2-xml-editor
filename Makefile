CFLAGS=-Wall
LIBS=-lxml2 -I$(INCLUDE_PATH)
CC=gcc
TARGET=main.c

all:
	$(CC) $(CFLAGS) main.c $(LIBS) -I$(INCLUDE_PATH) -o coh2-xml	

clean:
	rm coh2-xml

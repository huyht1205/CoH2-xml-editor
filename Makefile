CFLAGS = -Wall
INCLUDE_PATH ?= /usr/include/libxml2
LIBS = -lxml2 -I$(INCLUDE_PATH)
CC = gcc

all:
	$(CC) $(CFLAGS) main.c utils.c $(LIBS) -I$(INCLUDE_PATH) -o coh2-xml	
	$(CC) $(CFLAGS) list_value.c utils.c $(LIBS) -I$(INCLUDE_PATH) -o list_value	
clean:
	rm coh2-xml

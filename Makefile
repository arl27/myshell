CFLAGS = -g -Wall 
CC = gcc

objects = shell.o parse.o

shell: $(objects)
	$(CC) -o shell $(objects)




shell.o: shell.c parse.h
parse.o: parse.c parse.h

.PHONY : clean
clean: 
	rm $(objects)
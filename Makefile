CFLAGS = -g -Wall 
CC = gcc

objects = myshell.o parse.o

myshell: $(objects)
	$(CC) -o myshell $(objects)




myshell.o: myshell.c parse.h
parse.o: parse.c parse.h

.PHONY : clean
clean: 
	rm $(objects) myshell
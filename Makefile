INCLUDE=-I debugmalloc

default: main

main:
	gcc -Wall -pedantic *.c $(INCLUDE) -o main

clean:
	rm -f main
	

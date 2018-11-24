INCLUDE=-I debugmalloc

default: main

main:
	gcc -Wall *.c $(INCLUDE) -o main

clean:
	rm -f main
	

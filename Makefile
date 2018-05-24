
CFLAGS =-Wall -g -std=c99

kwic1 : kwic1.c 
	gcc $< $(CFLAGS) -o kwic1.out

clean : rm -f kwic1.out

CC=gcc

CFLAGS=-Wall -Wextra -pedantic -std=c23

PRODUCT=getpagesize

all: $(PRODUCT)

getpagesize: getpagesize.c
	$(CC) $(CFLAGS) -o getpagesize getpagesize.c

clean:
	rm -f $(PRODUCT)
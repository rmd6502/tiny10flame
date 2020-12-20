CC=avr-gcc
SIZE=avr-size
CFLAGS=-Os -mmcu=attiny10

all: tiny10flame

tiny10flame: main.o rand31.o
	$(CC) $(CFLAGS) $^ -o $@

main.o: main.c

rand31.o: rand31.S

#avr-gcc -mmcu=attiny10 -DF_CPU=1000000 -g -Os rand31.S main.c -o main.elf

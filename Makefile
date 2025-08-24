flags=-O2 -Wall -std=c2x


.PHONY: all clean

all: clean ping

ping: ping.o
	cc $(flags) $^ -o $@ $(ldflags)

ping.o: ping.c ping.h
	cc $(flags) -c $<

clean:
	rm -f *.o ping
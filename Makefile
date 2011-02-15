CC        := gcc
CXX       := g++
LD        := g++

CFLAGS    := -c -g -Wall -m32
CXXFLAGS  := -c -g -Wall -m32
LDFLAGS   := -m32 -g

all: getting_started v8c.o

getting_started: getting_started.o v8c.o
	$(LD) $(LDFLAGS) getting_started.o v8c.o -L../v8/ -lv8 -o getting_started
	
getting_started.o: ./test/getting_started.c
	$(CC) $(CFLAGS) ./test/getting_started.c -o getting_started.o
	
v8c.o: ./v8-bindings/v8c.cc
	$(CXX) $(CXXFLAGS) ./v8-bindings/v8c.cc -I../v8/include/ -o v8c.o
	
clean:
	rm -rf *.o getting_started
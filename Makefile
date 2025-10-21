# Compiler and flags
CC = cc
CFLAGS = -O2 -Wall -std=c2x -Iinclude
LDFLAGS = -Llib -lbu -Wl,-rpath,'$ORIGIN/lib'
SHARED_FLAGS = -O3 -Wall -std=c2x -fPIC -shared -Iinclude

# Source files
PING_SRC = src/ping.c
PING_OBJ = $(PING_SRC:.c=.o)

LIB_SRC = src/birchutils.c
LIB_OBJ = $(LIB_SRC:.c=.o)
LIB = lib/libbu.so

.PHONY: all clean

all: $(LIB) ping

# Build ping executable
ping: $(PING_OBJ) $(LIB_OBJ)
	$(CC) $(PING_OBJ) $(LIB_OBJ) -o $@ $(LDFLAGS)

# Compile ping.c
src/ping.o: src/ping.c include/birchutils.h
	$(CC) $(CFLAGS) -c $< -o $@

# Build shared library
$(LIB): $(LIB_OBJ)
	mkdir -p lib
	$(CC) $(SHARED_FLAGS) $(LIB_OBJ) -o $@

# Compile birchutils.c
src/birchutils.o: src/birchutils.c include/birchutils.h
	$(CC) $(CFLAGS) -O3 -fPIC -c $< -o $@

clean:
	rm -f src/*.o ping lib/*.so


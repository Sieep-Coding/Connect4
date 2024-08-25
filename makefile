CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -Iinclude
LDFLAGS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

# Targets
all: connect4

connect4: src/main.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

test: src/test.o include/unity.o
	$(CC) $(CFLAGS) -o test $^ $(LDFLAGS)

src/main.o: src/main.c
	$(CC) $(CFLAGS) -c $< -o $@

include/unity.o: include/unity.c
	$(CC) $(CFLAGS) -c $< -o $@

src/test.o: src/test.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f src/*.o include/*.o connect4 test

CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -Iinclude
LDFLAGS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
SRCS = src/main.c
OBJS = $(SRCS:.c=.o)
TARGET = connect4

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS)

src/%.o: src/%.c
	$(CC) $(CFLAGS) -Iinclude -c $< -o $@

test: $(OBJS)
	$(CC) $(CFLAGS) -o test_executable src/unity.c $(OBJS) $(LDFLAGS)
	./test_executable

clean:
	rm -f $(OBJS) $(TARGET) test_executable

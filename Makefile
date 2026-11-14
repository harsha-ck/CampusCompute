CC = gcc
CFLAGS = -Wall -Wextra -Iinclude
LDFLAGS = -pthread

SRC = src/main.c src/job.c src/scheduler.c \
      src/producer_consumer.c src/ipc.c \
      src/banker.c src/process.c src/resource.c

TARGET = campus

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) $(LDFLAGS) -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET) campus_test

.PHONY: all run clean

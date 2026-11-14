CC = gcc
CFLAGS = -Wall -Wextra -Iinclude
LDFLAGS = -pthread

TARGET = campus

SRC = src/main.c \
      src/job.c \
      src/scheduler.c \
      src/producer_consumer.c \
      src/ipc.c \
      src/banker.c \
      src/process.c \
      src/resource.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) $(LDFLAGS) -o $(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all clean

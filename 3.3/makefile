
CC := gcc
CLIENT_TARGET := endian_conv inet_addr
CLIENT_SRC := endian_conv.c inet_addr.c

all: $(SERVER_TARGET) $(CLIENT_TARGET)

$(SERVER_TARGET): $(SERVER_SRC:.c=.o)
	$(CC) $^ -o $@
$(CLIENT_TARGET): $(CLIENT_SRC:.c=.o)
	$(CC) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c -g $< -o $@

clean:
	rm -f $(SERVER_TARGET) $(CLIENT_TARGET) *.o
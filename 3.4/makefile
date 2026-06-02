
CC := gcc
# CLIENT_TARGET := inet_addr
# CLIENT_SRC := inet_addr.c

# CLIENT_TARGET := inet_aton
# CLIENT_SRC := inet_aton.c

CLIENT_TARGET := inet_ntoa
CLIENT_SRC := inet_ntoa.c

all: $(SERVER_TARGET) $(CLIENT_TARGET)

$(SERVER_TARGET): $(SERVER_SRC:.c=.o)
	$(CC) $^ -o $@
$(CLIENT_TARGET): $(CLIENT_SRC:.c=.o)
	$(CC) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c -g $< -o $@

clean:
	rm -f $(SERVER_TARGET) $(CLIENT_TARGET) *.o
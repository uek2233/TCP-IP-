
CC := gcc
SERVER_TARGET := tcp_server
CLIENT_TARGET := tcp_client

SERVER_SRC := tcp_server.c
CLIENT_SRC := tcp_client.c

all: $(SERVER_TARGET) $(CLIENT_TARGET)

$(SERVER_TARGET): $(SERVER_SRC:.c=.o)
	$(CC) $^ -o $@
$(CLIENT_TARGET): $(CLIENT_SRC:.c=.o)
	$(CC) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c -g $< -o $@
	
test: $(SERVER_TARGET) $(CLIENT_TARGET)
	@echo "启动服务器..."
	@./$(SERVER_TARGET) 9100 & SERVER_PID=$$!; \
	echo "服务器进程ID: $$SERVER_PID"; \
	sleep 2; \
	echo "启动客户端..."; \
	if ./$(CLIENT_TARGET) 127.0.0.1 9100; then \
		echo "客户端执行成功"; \ 
	else \
		echo "客户端执行失败"; \
	fi; \
	echo "终止服务器进程 $$SERVER_PID"; \
	kill $$SERVER_PID || true

clean:
	rm -f $(SERVER_TARGET) $(CLIENT_TARGET) *.o
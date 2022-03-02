all: server client

server: client.c server.c utils.c minitalk.h
	cc -Wall -Wextra -Werror server.c utils.c -o server

client: client.c server.c utils.c minitalk.h
	cc -Wall -Wextra -Werror client.c utils.c -o client

clean:
	rm -f server client

fclean: clean

re: fclean all

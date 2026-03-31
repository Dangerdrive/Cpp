#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/select.h>


typedef struct s_client {
	int id;
	char *msg;
} t_client;

t_client clients[1024];
fd_set read_fds, write_fds, active_fds;
int max_fd = 0; next_id = 0;
char read_buf[4200 * 42], send_buf[4200 *43];

void fatal(){
	write(2, "Fatal error\n", strlen("Fatal error\n"));
	exit(1);
}

send_all(int senderfd){
	for (int fd = 0; fd <= max_fd; fd++)
	{
		if (FD_ISSET(fd, &write_fds) && fd != senderfd)
			send(fd, send_buf, strlen(send_buf), 0);
	}
}

int extract_message(char **buf, char **msg)
{
	char	*newbuf;
	int	i;

	*msg = 0;
	if (*buf == 0)
		return (0);
	i = 0;
	while ((*buf)[i])
	{
		if ((*buf)[i] == '\n')
		{
			newbuf = calloc(1, sizeof(*newbuf) * (strlen(*buf + i + 1) + 1));
			if (newbuf < 0)
				fatal();
			strcpy(newbuf, *buf + i + 1);
			*msg = *buf;
			(*msg)[i + 1] = 0;
			*buf = newbuf;
			return (1);
		}
		i++;
	}
	return (0);
}

char *str_join(char *buf, char *add)
{
	char	*newbuf;
	int		len;
	if (buf == 0)
		len = 0;
	else
		len = strlen(buf);
	newbuf = malloc(sizeof(*newbuf) * (len + strlen(add) + 1));
	if (newbuf < 0)
		fatal();
	newbuf[0] = 0;
	if (buf != 0)
		strcat(newbuf, buf);
	free(buf);
	strcat(newbuf, add);
	return (newbuf);
}


int main(int argc, char** argv) {
	if (argc != 2)
	{
		write(2, "Wrong number of arguments\n", strlen("Wrong number of arguments\n"));
		exit(1);
	}

	memset(clients, 0, sizeof(clients));

	int server_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (server_fd < 0) fatal();

	max_fd = server_fd;
	FD_ZERO(&active_fds);
	FD_SET(server_fd; &active_fds);

	struct sockaddr_in servaddr;
	bzero(&servaddr, sizeof(servaddr)); 
	servaddr.sin_family = AF_INET; 
	servaddr.sin_addr.s_addr = htonl(2130706433); //127.0.0.1
	servaddr.sin_port = htons(8081);
  

	// Binding newly created socket to given IP and verification 
	if ((bind(server_fd, (const struct sockaddr *)&servaddr, sizeof(servaddr))) < 0) { 

	} 
	if (listen(server_fd, 100) < 0) {
		fatal();
	}

	while(1)
	{
		read_fds = write_fds = active_fds;

		if (select(max_fd + 1, &read_fds, &write_fds, NULL, NULL) < 0) continue;

		for (int fd = 0; fd <= max_fd; fd++)
		{
			if (FD_ISSET(fd, &read_fds))
			{
				if (fd == server_fd)
				{
					struct sockaddr_in cli_addr;
					socklen_t len = sizeof(cli_addr);
					int client_fd  = accept(server_fd, (struct sockaddr *)&cli_addr, &len);
					if (client_fd < 0) continue;

					if (max_fd < client_fd) max_fd = client_fd;
					clients[client_fd].id = next_id++;
					clients[client_fd].msg = NULL;
					FD_SET(client_fd, &active_fds);

					sprintf(send_buf, "server: client %d just arrived\n", clients[client_fd].id);
					send_all(client_fd);
					break;
				}
				else
				{
					ssize_t buff_len = recv(fd, read_buf, sizeof(read_buf) - 1, 0);
					if ( buff_len <= 0){
						sprintf(send_buf, "server: client %d just left\n", clients[fd].id);
						send_all(fd);
						free(clients[fd].msg);
						FD_CLR(fd, &active_fds);
						close(fd);
						break;
					}
					read_buf[buff_len] = 0;
					clients[fd].msg = str_join(clients[fd].msg, &read_buf);
					
					char* msg_to_send;
					while (extract_message(&(clients[fd].msg), read_buf))
					{
						sprintf(send_buf, "client %d: %s", clients[fd].id, clients[fd].msg);
						send_all(fd);
						free(msg_to_send);
					}
				}
			}
		}
	}

	
	return 0;
}


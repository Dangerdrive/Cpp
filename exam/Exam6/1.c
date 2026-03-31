#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/select.h>

typedef struct s_clients {
    int id;
    char *msg;
} t_client;

t_client clients[1024];
fd_set write_fds, read_fds, active_fds;
int max_fd = 0, next_id = 0;
char read_buffer[4200 * 42], send_buffer[4200 * 43];

fatal(char *msg) {
    if (!msg)
    {
    write(2, "Fatal error", strlen("Fatal error"));
    }
    if (msg)
        write(2, msg, strlen(msg));
    write(2, "\n", 1);
    exit(1);
}

send_all(int sender_fd)
{
    for (int fd = 0; fd <= max_fd; fd++)
    {
        if (FD_ISSET(fd, &write_fds) && fd != sender_fd)
            send(fd, send_buffer, sizeof(send_buffer), 0);
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
			if (newbuf == 0)
				return (-1);
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
	if (newbuf == 0)
		return (0);
	newbuf[0] = 0;
	if (buf != 0)
		strcat(newbuf, buf);
	free(buf);
	strcat(newbuf, add);
	return (newbuf);
}


int main(int argc, char **argv) {
    if (argc != 2)
        fatal("Wrong number of arguments");
    
    memset(clients, 0, sizeof(clients));

    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) fatal(NULL);

    struct sockaddr_in servaddr;
    bzero(&servaddr, sizeof(servaddr));
    FD_ZERO(&active_fds);
    FD_SET(server_fd, &active_fds);
    max_fd = server_fd;

	servaddr.sin_family = AF_INET; 
	servaddr.sin_addr.s_addr = htonl(2130706433); //127.0.0.1
	servaddr.sin_port = htons(8081);

    if (bind(server_fd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) fatal(NULL);
    if (listen(server_fd, 100) < 0) fatal(NULL);

    while(42)
    {
        read_fds = write_fds = active_fds;

        if (select(server_fd, &read_fds, &write_fds, 0, 0) < 0) continue;

        for(int fd = 0; fd<=max_fd; fd++){
            if (FD_ISSET(fd, &read_fds))
                if (fd == server_fd)
                {
                    struct sockaddr cli;
                    socklen_t len;
                    int cli_fd = accept(server_fd, (struct sockaddr *)&cli, &len);
                    if (cli_fd < 0) continue;
                    
                    if (cli_fd > max_fd) max_fd = cli_fd;
                    clients[cli_fd].id = next_id++;
                    clients[cli_fd].msg = NULL;
                    FD_SET(cli_fd, &active_fds);
                                                                               
                    sprintf(send_buffer, "%d", clients[cli_fd].id);
                    send_all(cli_fd);
                    break;
                }
                else {
                    ssize_t buff_len = recv(fd, &read_buffer, sizeof(read_buffer), 0);
                    if (buff_len <= 0)
                    {                    
                    sprintf(send_buffer, "%d", clients[fd].id);
                    send_all(server_fd);
                    free(clients[fd].msg);
                    FD_CLR(fd, &active_fds);
                    close(fd);
                    break;
                    }
                    read_buffer[buff_len];
                    clients[fd].msg = str_join(clients[fd].msg, send_buffer);

                    char *to_send;
                    while (extract_message(clients[fd].msg, to_send))
                    {
                        sprintf(send_buffer, "" );
                        send_all(fd);
                        free(to_send);
                    }
                }
        }
    }












	int sockfd, connfd, len;
	struct sockaddr_in servaddr, cli; 

	// socket create and verification 
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1) { 
		printf("socket creation failed...\n"); 
		exit(0); 
	} 
	else
		printf("Socket successfully created..\n"); 
	bzero(&servaddr, sizeof(servaddr)); 

	// assign IP, PORT 
	servaddr.sin_family = AF_INET; 
	servaddr.sin_addr.s_addr = htonl(2130706433); //127.0.0.1
	servaddr.sin_port = htons(8081);
  
	// Binding newly created socket to given IP and verification 
	if ((bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr))) != 0) { 
		printf("socket bind failed...\n"); 
		exit(0); 
	} 
	else
		printf("Socket successfully binded..\n");
	if (listen(sockfd, 10) != 0) {
		printf("cannot listen\n"); 
		exit(0); 
	}
	len = sizeof(cli);
	connfd = accept(sockfd, (struct sockaddr *)&cli, &len);
	if (connfd < 0) { 
		printf("server acccept failed...\n"); 
		exit(0); 
	} 
	else
		printf("server acccept the client...\n");
}


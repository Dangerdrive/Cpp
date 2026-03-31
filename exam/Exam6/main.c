#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>

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


int main() {
	int sockfd, connfd, len;
	struct sockaddr_in servaddr, cli; 

	// socket create and verification 
	sockfd = socket(AF_INET, SOCK_STREAM, 0); // mudar pra server_fd
	
	if (server_fd < 0) fatal_error();
	// if (sockfd == -1) { 
	// 	printf("socket creation failed...\n"); 
	// 	exit(0); 
	// } 
	// else
	// 	printf("Socket successfully created..\n"); 
	bzero(&servaddr, sizeof(servaddr)); //ok


	max_fd = server_fd; // O server vai ser tipo o fd 3 a gente seta ele como o maior
    FD_ZERO(&active_fds); // limpa o conjunto de descritores ativos
    FD_SET(server_fd, &active_fds);  // inicializa o descritor do servidor

	// assign IP, PORT // ok
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
	if (listen(sockfd, 10) != 0) { //100 // <0
		printf("cannot listen\n"); //fatal error
		exit(0); 
	}
	// len = sizeof(cli);
	// connfd = accept(sockfd, (struct sockaddr *)&cli, &len);
	// if (connfd < 0) { 
	// 	printf("server acccept failed...\n"); 
	// 	exit(0); 
	// } 
	// else
	// 	printf("server acccept the client...\n");
	    while (1) {
        read_fds = write_fds = active_fds;
        if (select(max_fd + 1, &read_fds, &write_fds, NULL, NULL) < 0) continue;
//Quando o select acorda o programa, ele avisa "tem dados novos na rede", mas ele não te diz quem mandou.
        for (int fd = 0; fd <= max_fd; fd++) {
            if (FD_ISSET(fd, &read_fds)) { //checar individualmente qual cliente mandou a mensagem ou se é um novo cliente se conectando

                // Novo cliente conectando
                if (fd == server_fd) {
                    struct sockaddr_in cli;
                    socklen_t len = sizeof(cli);
                    int client_fd = accept(server_fd, (struct sockaddr *)&cli, &len); //aceita a conexão
                    if (client_fd < 0) continue; //Se deu erro durante (comum de o servidor cair) apenas continua
                    
                    max_fd = (client_fd > max_fd) ? client_fd : max_fd;
                    clients[client_fd].id = next_id++;
                    clients[client_fd].msg = NULL;
                    FD_SET(client_fd, &active_fds); //inclui o novo client na lista de ativos
                    
                    sprintf(buffer_send, "server: client %d just arrived\n", clients[client_fd].id);
                    send_all(client_fd);
                    break;
                } 
                // Mensagem de cliente existente
                else {
                    ssize_t buff_len = recv(fd, buffer_read, sizeof(buffer_read) - 1, 0); //lê a msg que o cliente enviou
                    if (buff_len <= 0) { //Se não tem msg nenhuma, significa que o cliente desconectou
                        sprintf(buffer_send, "server: client %d just left\n", clients[fd].id);
                        send_all(fd);
                        free(clients[fd].msg);
                        FD_CLR(fd, &active_fds); //apaga o cliente dos descritores ativos
                        close(fd);
                        break;
                    }
                    
                    buffer_read[buff_len] = 0;
                    clients[fd].msg = str_join(clients[fd].msg, buffer_read);
                    
                    char *msg_to_send;
                    while (extract_message(&(clients[fd].msg), &msg_to_send)) { //como msgs podem ter quebras de linha, lê 1 por vez e printa colocando o id do cliente na frente
                        sprintf(buffer_send, "client %d: %s", clients[fd].id, msg_to_send);
                        send_all(fd);
                        free(msg_to_send);
                    }
                }
            }
        }
    }
    return 0;
}


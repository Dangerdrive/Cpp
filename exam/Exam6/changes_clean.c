typedef struct s_client {
    int id;
    char *msg;
} t_client;

t_client clients[1024];
fd_set read_fds, write_fds, active_fds;
int max_fd = 0, next_id = 0;
char buffer_read[4200 * 42], buffer_send[4200 * 43]; 

void fatal_error() {
    write(2, "Fatal error\n", 12); 
    exit(1);
}

void send_all(int sender_fd) {
    for (int fd = 0; fd <= max_fd; fd++) {
        if (FD_ISSET(fd, &write_fds) && fd != sender_fd) {
            send(fd, buffer_send, strlen(buffer_send), 0);
        }
    }
}


int extract_message ...
    
    if (newbuf == 0) fatal_error();

char *str_join ...
    
    if (newbuf == 0) fatal_error();

    int main(int argc, char **argv) {
    if (argc != 2) {
        write(2, "Wrong number of arguments\n", 26);
        exit(1);
    }

    memset(clients, 0, sizeof(clients)); 

    int server_fd = socket(AF_INET, SOCK_STREAM, 0); 
    if (server_fd < 0) fatal_error();

    max_fd = server_fd; 
    FD_ZERO(&active_fds); 
    FD_SET(server_fd, &active_fds);  

    struct sockaddr_in servaddr; 
    bzero(&servaddr, sizeof(servaddr)); 
    servaddr.sin_family = AF_INET; 
    servaddr.sin_addr.s_addr = htonl(2130706433); 
    servaddr.sin_port = htons(atoi(argv[1])); 

    if (bind(server_fd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) 
        fatal_error(); 
    if (listen(server_fd, 128) < 0) fatal_error();



    while (1) {
        read_fds = write_fds = active_fds;
        if (select(max_fd + 1, &read_fds, &write_fds, NULL, NULL) < 0) continue;

        for (int fd = 0; fd <= max_fd; fd++) {
            if (FD_ISSET(fd, &read_fds)) {              
                if (fd == server_fd) {
                    struct sockaddr_in cli;
                    socklen_t len = sizeof(cli);
                    int client_fd = accept(server_fd, (struct sockaddr *)&cli, &len); 
                    if (client_fd < 0) continue; 
                    
                    max_fd = (client_fd > max_fd) ? client_fd : max_fd;
                    clients[client_fd].id = next_id++;
                    clients[client_fd].msg = NULL;
                    FD_SET(client_fd, &active_fds); 
                    
                    sprintf(buffer_send, "server: client %d just arrived\n", clients[client_fd].id);
                    send_all(client_fd);
                    break;
                } 
                
                else {
                    ssize_t buff_len = recv(fd, buffer_read, sizeof(buffer_read) - 1, 0); 
                    if (buff_len <= 0) { 
                        sprintf(buffer_send, "server: client %d just left\n", clients[fd].id);
                        send_all(fd);
                        free(clients[fd].msg);
                        FD_CLR(fd, &active_fds); 
                        close(fd);
                        break;
                    }
                    
                    buffer_read[buff_len] = 0;
                    clients[fd].msg = str_join(clients[fd].msg, buffer_read);
                    
                    char *msg_to_send;
                    while (extract_message(&(clients[fd].msg), &msg_to_send)) { 
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
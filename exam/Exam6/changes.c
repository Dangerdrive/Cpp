typedef struct s_client {
    int id;
    char *msg;
} t_client;

t_client clients[1024];
fd_set read_fds, write_fds, active_fds;
int max_fd = 0, next_id = 0;
char buffer_read[4200 * 42], buffer_send[4200 * 43]; // Margem para "client %d: "

void fatal_error() {
    write(2, "Fatal error\n", 12); // lembrar de conferir se está a qtd correta de caracteres
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
    // if (newbuf == 0)
    if (newbuf == 0) fatal_error();

char *str_join ...
    // if (newbuf == 0)
    if (newbuf == 0) fatal_error();

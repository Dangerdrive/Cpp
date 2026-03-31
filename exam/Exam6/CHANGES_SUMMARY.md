# Transformation Summary: change_me.c → exam.c

## Overview
Transformed change_me.c from a basic blocking TCP server (accepts only one client) into a non-blocking multiplexed server that handles multiple concurrent clients using `select()` and broadcasts messages between them.

## Key Changes Made

### 1. **Added Headers**
**What:** `#include <stdlib.h>` and `#include <stdio.h>`
**Why:** Required for `malloc()`, `free()`, `calloc()`, and `sprintf()` functions used in the new implementation.

### 2. **Added Client Structure**
```c
typedef struct s_client {
    int id;
    char *msg;
} t_client;
```
**Why:** Needed to track individual client data (unique ID and their message buffer).

### 3. **Added Global Variables**
- `t_client clients[1024]`: Array to store up to 1024 client structures
- `fd_set read_fds, write_fds, active_fds`: File descriptor sets for `select()` multiplexing
- `int max_fd = 0, next_id = 0`: Track the highest fd and next client ID to assign
- `char buffer_read[4200 * 42], buffer_send[4200 * 43]`: Global buffers for I/O operations

**Why:** Required for non-blocking multiplexing of multiple concurrent clients.

### 4. **Added `fatal_error()` Function**
```c
void fatal_error() {
    write(2, "Fatal error\n", 12);
    exit(1);
}
```
**Why:** Centralized error handling that outputs to stderr using `write()` (required by subject) and exits with status 1.

### 5. **Added `send_all()` Function**
```c
void send_all(int sender_fd) {
    for (int fd = 0; fd <= max_fd; fd++) {
        if (FD_ISSET(fd, &write_fds) && fd != sender_fd) {
            send(fd, buffer_send, strlen(buffer_send), 0);
        }
    }
}
```
**Why:** Broadcasts a message in `buffer_send` to all connected clients except the sender. Required for client-to-client communication.

### 6. **Modified `extract_message()` Function**
**Changes:**
- Reformatted code style for consistency
- Changed error handling: `return (-1)` → `fatal_error()`

**Why:** The subject requires the program to exit with "Fatal error" on memory allocation failures, not silently return an error code.

### 7. **Modified `str_join()` Function**
**Changes:**
- Reformatted code style
- Simplified variable initialization: multi-line if/else → ternary operator
- Changed error handling: `return (0)` → `fatal_error()`

**Why:** Same as extract_message - consistent error handling and code style.

### 8. **Completely Rewrote `main()` Function**

#### Old main() (Blocking, Single Client):
- Accepted one client connection and then blocked
- Used `printf()` for debug output
- No argument processing
- No message handling

#### New main() (Non-blocking, Multiple Clients):

**Argument Processing:**
```c
if (argc != 2) {
    write(2, "Wrong number of arguments\n", 26);
    exit(1);
}
```
- Validates command-line arguments (port number required)
- Outputs errors to stderr using `write()`

**Initialization:**
```c
memset(clients, 0, sizeof(clients));
```
- Clears the client array

**File Descriptor Set Operations:**
```c
FD_ZERO(&active_fds);
FD_SET(server_fd, &active_fds);
```
- Initializes and registers server socket for monitoring

**Main Loop with select():**
```c
read_fds = write_fds = active_fds;
if (select(max_fd + 1, &read_fds, &write_fds, NULL, NULL) < 0) continue;
```
- Uses `select()` to monitor all registered file descriptors
- Non-blocking operation - doesn't wait for a specific client

**Handle New Connections:**
```c
if (fd == server_fd) {
    // accept() new client
    // assign unique ID (next_id++)
    // broadcast "server: client %d just arrived\n"
    // add to active_fds
}
```

**Handle Client Messages:**
```c
ssize_t buff_len = recv(fd, buffer_read, sizeof(buffer_read) - 1, 0);
// extract_message() for each newline
// broadcast "client %d: %s" to all other clients
```

**Handle Client Disconnections:**
```c
if (buff_len <= 0) {
    // broadcast "server: client %d just left\n"
    // free message buffer
    // remove from active_fds
    // close socket
}
```

## Function Logic

| Aspect | Old | New |
|--------|-----|-----|
| **Concurrency** | Single client (blocking) | Multiple clients (non-blocking with select) |
| **Message Handling** | None | Multi-line message extraction & broadcast |
| **Port** | Hardcoded (8081) | Command-line argument |
| **Error Handling** | printf() exit | write() to stderr + fatal_error() |
| **Client Tracking** | None | ID-based with structure array |
| **Communication** | One-way | Broadcast to all except sender |

## Subject Compliance Check ✓

- ✓ Takes port as first argument
- ✓ Outputs "Wrong number of arguments\n" to stderr if argc != 2
- ✓ Outputs "Fatal error\n" to stderr for system/memory failures
- ✓ Non-blocking server using select()
- ✓ Clients don't disconnect if they don't read messages
- ✓ No #define preprocessor directives
- ✓ Listens only to 127.0.0.1
- ✓ Clients receive unique IDs (0, 1, 2, ...)
- ✓ Broadcasts "server: client %d just arrived\n" on connection
- ✓ Broadcasts "server: client %d just left\n" on disconnection
- ✓ Broadcasts "client %d: %s" for messages with proper formatting
- ✓ Handles multi-line messages (multiple \n per message)
- ✓ Uses only allowed functions per subject
- ✓ No memory leaks (free() called appropriately)
- ✓ No fd leaks (FD_CLR and close() used)
- ✓ Sends messages as fast as possible (no unnecessary buffering)

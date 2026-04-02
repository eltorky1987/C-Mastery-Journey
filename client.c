#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int server_fd, client_fd;
    struct sockaddr_in addr;
    char buffer[1024] = {0};

    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(4444);

    bind(server_fd, (struct sockaddr*)&addr, sizeof(addr));
    listen(server_fd, 1);

    printf("Server listening on port 4444...\n");

    client_fd = accept(server_fd, NULL, NULL);

    while (1) {
        memset(buffer, 0, sizeof(buffer));
        read(client_fd, buffer, 1024);

        printf("Received: %s\n", buffer);

        if (strncmp(buffer, "scan", 4) == 0) {
            send(client_fd, "Open port: 22\n", 14, 0);
        }
        else if (strncmp(buffer, "getflag", 7) == 0) {
            send(client_fd, "FLAG{real_lab_flag}\n", 21, 0);
        }
        else {
            send(client_fd, "Unknown command\n", 17, 0);
        }
    }

    return 0;
}

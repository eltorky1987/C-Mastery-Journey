#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int server_fd, client_fd;
    struct sockaddr_in addr;
    char buffer[1024];

    // إنشاء Socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (server_fd == -1) {
        perror("Socket failed");
        return 1;
    }

    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(4444);

    // ربط البورت
    if (bind(server_fd, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        perror("Bind failed");
        return 1;
    }

    // الاستماع
    if (listen(server_fd, 1) < 0) {
        perror("Listen failed");
        return 1;
    }

    printf("Server listening on port 4444...\n");

    client_fd = accept(server_fd, NULL, NULL);

    printf("Client connected!\n");

    while (1) {
        memset(buffer, 0, sizeof(buffer));

        int bytes = read(client_fd, buffer, sizeof(buffer));
        if (bytes <= 0) {
            printf("Client disconnected\n");
            break;
        }

        printf("Received: %s\n", buffer);

        // أوامر اللعبة
        if (strncmp(buffer, "scan", 4) == 0) {
            send(client_fd, "Open port: 22\n", 14, 0);
        }
        else if (strncmp(buffer, "connect", 7) == 0) {
            send(client_fd, "Connecting...\nSuccess! System accessed.\n", 41, 0);
        }
        else if (strncmp(buffer, "getflag", 7) == 0) {
            send(client_fd, "FLAG{real_lab_mode}\n", 20, 0);
        }
        else if (strncmp(buffer, "help", 4) == 0) {
            send(client_fd, "Commands: scan | connect | getflag | help\n", 44, 0);
        }
        else {
            send(client_fd, "Unknown command\n", 17, 0);
        }
    }

    close(client_fd);
    close(server_fd);

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

void handle_client(int client_fd) {
    char buffer[1024];
    int level = 0;

    send(client_fd, "Welcome to AGINA CTF Platform!\nEnter password to start:\n", 56, 0);

    while (1) {
        memset(buffer, 0, sizeof(buffer));

        int valread = read(client_fd, buffer, sizeof(buffer) - 1);
        if (valread <= 0) break;

        buffer[strcspn(buffer, "\r\n")] = 0;

        // 🔐 LEVEL 0 - AUTH
        if (level == 0) {
            if (strcmp(buffer, "admin123") == 0) {
                send(client_fd, "Access Granted! Welcome Hacker!\nType 'help'\n", 50, 0);
                level = 1;
            } else {
                send(client_fd, "Wrong password! Try again:\n", 28, 0);
            }
        }

        // 🟢 LEVEL 1
        else if (level == 1) {
            if (strcmp(buffer, "help") == 0) {
                send(client_fd, "Commands: scan | exploit 1337\n", 32, 0);
            } 
            else if (strcmp(buffer, "scan") == 0) {
                send(client_fd, "Found hidden service on port 1337\n", 36, 0);
            } 
            else if (strcmp(buffer, "exploit 1337") == 0) {
                send(client_fd, "Exploitation success!\nLevel 2 unlocked\n", 40, 0);
                level = 2;
            } 
            else {
                send(client_fd, "Unknown command\n", 17, 0);
            }
        }

        // 🟡 LEVEL 2
        else if (level == 2) {
            if (strcmp(buffer, "decrypt") == 0) {
                send(client_fd, "Encrypted: U2VjcmV0\n", 22, 0);
            } 
            else if (strcmp(buffer, "solve Secret") == 0) {
                send(client_fd, "Correct!\nLevel 3 unlocked\n", 30, 0);
                level = 3;
            } 
            else {
                send(client_fd, "Hint: decrypt or solve Secret\n", 32, 0);
            }
        }

        // 🔴 LEVEL 3
        else if (level == 3) {
            if (strcmp(buffer, "getflag") == 0) {
                send(client_fd, "FLAG{real_ctf_master}\n", 24, 0);
            } 
            else {
                send(client_fd, "Try: getflag\n", 14, 0);
            }
        }
    }
}

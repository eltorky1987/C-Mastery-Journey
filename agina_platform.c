#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <arpa/inet.h>

// دالة التشفير (بتحول الباسورد لأرقام صعبة)
unsigned long hash_password(char *str) {
    unsigned long hash = 5381;
    int c;
    while ((c = *str++)) hash = ((hash << 5) + hash) + c;
    return hash;
}

// دالة التحقق من الدخول
int check_login(char *user, char *pass) {
    FILE *file = fopen("hackers.txt", "r");
    if (!file) return 0;
    char line[150], f_user[50];
    unsigned long f_hash, input_hash = hash_password(pass);
    while (fgets(line, sizeof(line), file)) {
        if (sscanf(line, "%[^:]:%lu", f_user, &f_hash) == 2) {
            if (strcmp(user, f_user) == 0 && input_hash == f_hash) {
                fclose(file); return 1;
            }
        }
    }
    fclose(file); return 0;
}

void handle_client(int client_fd) {
    char buffer[1024], user[50], pass[50];
    send(client_fd, "--- Welcome to AGINA Platform ---\nUsername: ", 44, 0);
    
    read(client_fd, user, 50);
    user[strcspn(user, "\r\n")] = 0;

    send(client_fd, "Password: ", 10, 0);
    read(client_fd, pass, 50);
    pass[strcspn(pass, "\r\n")] = 0;

    if (check_login(user, pass)) {
        send(client_fd, "\n[✔] Access Granted! Level 1 Unlocked.\n>> ", 42, 0);
        // هنا ممكن تضيف أوامر اللعبة التانية زي getflag
    } else {
        send(client_fd, "\n[✘] Wrong Username or Password!\n", 33, 0);
    }
    close(client_fd);
    exit(0);
}

int main() {
    int server_fd, client_fd;
    struct sockaddr_in addr;
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(4444);
    bind(server_fd, (struct sockaddr*)&addr, sizeof(addr));
    listen(server_fd, 5);
    printf("Server is Running on port 4444...\n");
    while (1) {
        client_fd = accept(server_fd, NULL, NULL);
        if (fork() == 0) handle_client(client_fd);
        close(client_fd);
    }
    return 0;
}

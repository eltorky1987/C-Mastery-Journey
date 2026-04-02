#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    int sock;
    struct sockaddr_in server;
    char message[1024], server_reply[2048];

    sock = socket(AF_INET, SOCK_STREAM, 0);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_family = AF_INET;
    server.sin_port = htons(4444);

    if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0) {
        printf("Connect failed. Is the server running?\n");
        return 1;
    }

    printf("Connected to Lab Server. Type 'help' for commands.\n");

    while(1) {
        printf(">> ");
        // استخدام fgets بدل scanf لقراءة الأوامر المركبة
        fgets(message, sizeof(message), stdin);
        message[strcspn(message, "\n")] = 0; // مسح السطر الجديد

        if (send(sock, message, strlen(message), 0) < 0) break;
        
        memset(server_reply, 0, sizeof(server_reply));
        if (recv(sock, server_reply, sizeof(server_reply), 0) <= 0) break;
        
        printf("%s\n", server_reply);
    }
    close(sock);
    return 0;
}

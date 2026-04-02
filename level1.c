#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int mission1 = 0; // حالة مهمة الفحص
int mission2 = 0; // حالة مهمة الاتصال

// دالة تأثير الكتابة التدريجية
void type(const char *text) {
    for (int i = 0; text[i] != '\0'; i++) {
        printf("%c", text[i]);
        fflush(stdout);
        usleep(30000); 
    }
    printf("\n");
}

void banner() {
    printf("\033[1;32m"); // لون أخضر
    type("Initializing system...");
    type("Connecting to secure server...");
    printf("\033[0m");
}

int main() {
    char username[20], password[20], cmd[50];

    printf("\033[2J\033[H"); // مسح الشاشة
    banner();

    // نظام الدخول
    printf("login: ");
    scanf("%s", username);
    printf("password: ");
    scanf("%s", password);

    if (strcmp(username, "admin") != 0 || strcmp(password, "1234") != 0) {
        printf("\033[1;31mAccess Denied!\033[0m\n");
        return 0;
    }

    printf("\033[1;32mAccess Granted. Welcome, Admin.\033[0m\n");

    while (1) {
        printf("\n>> ");
        scanf("%s", cmd);

        if (strcmp(cmd, "help") == 0) {
            printf("Commands: help | scan | connect | getflag | exit\n");
        } 
        else if (strcmp(cmd, "scan") == 0) {
            printf("Scanning network...\n");
            sleep(1);
            printf("Found Open Port: 22 (SSH)\n");
            mission1 = 1;
        } 
        else if (strcmp(cmd, "connect") == 0) {
            char arg[10];
            scanf("%s", arg); // يقرأ رقم البورت
            if (strcmp(arg, "22") == 0) {
                if (mission1) {
                    printf("Connecting to SSH on port 22...\n");
                    sleep(1);
                    printf("Success! System compromised.\n");
                    mission2 = 1;
                } else {
                    printf("Error: Scan the network first!\n");
                }
            } else {
                printf("Error: Wrong port.\n");
            }
        } 
        else if (strcmp(cmd, "getflag") == 0) {
            if (mission1 && mission2) {
                printf("\033[1;33mFLAG{you_are_now_level_1_hacker}\033[0m\n");
            } else {
                printf("Mission incomplete! (Hint: scan -> connect 22)\n");
            }
        } 
        else if (strcmp(cmd, "exit") == 0) {
            printf("Goodbye!\n");
            break;
        } 
        else {
            printf("Unknown command: %s\n", cmd);
        }
    }

    return 0;
}

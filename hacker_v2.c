#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int mission1 = 0;
int mission2 = 0;
int mission3 = 0;
int level = 1;

// تأثير الكتابة
void type(const char *text) {
    for (int i = 0; text[i] != '\0'; i++) {
        printf("%c", text[i]);
        fflush(stdout);
        usleep(30000);
    }
    printf("\n");
}

// بانر البداية
void banner() {
    printf("\033[1;32m");
    type("Initializing system...");
    type("Connecting to secure server...");
    printf("\033[0m");
}

int main() {
    char username[20];
    char password[20];
    char cmd[50];

    printf("\033[2J\033[H");
    banner();

    // Login
    printf("login: ");
    scanf("%19s", username);
    printf("password: ");
    scanf("%19s", password);

    if (strcmp(username, "admin") != 0 || strcmp(password, "1234") != 0) {
        printf("\033[1;31mAccess Denied!\033[0m\n");
        return 0;
    }

    printf("\033[1;32mAccess Granted. Welcome, Admin.\033[0m\n");

    while (1) {
        printf("\n>> ");
        scanf("%49s", cmd);

        // HELP
        if (strcmp(cmd, "help") == 0) {
            printf("Commands:\n");
            printf("help | scan | connect | brute | decrypt | getflag | clear | exit\n");
        }

        // SCAN
        else if (strcmp(cmd, "scan") == 0) {
            printf("Scanning network...\n");
            sleep(1);
            printf("Found Open Port: 22 (SSH)\n");
            mission1 = 1;
        }

        // CONNECT
        else if (strcmp(cmd, "connect") == 0) {
            int port;
            if (scanf("%d", &port) != 1) {
                printf("Invalid input! Use: connect <port>\n");
                continue;
            }

            if (port == 22) {
                if (mission1) {
                    printf("Connecting to SSH...\n");
                    sleep(1);
                    printf("Access to system gained.\n");
                    mission2 = 1;
                } else {
                    printf("Scan the network first!\n");
                }
            } else {
                printf("Wrong port!\n");
            }
        }

        // BRUTE
        else if (strcmp(cmd, "brute") == 0) {
            if (level < 2) {
                printf("Command locked. Complete Level 1 first.\n");
                continue;
            }

            char pass[20];
            printf("Enter password attempt: ");
            scanf("%19s", pass);

            if (strcmp(pass, "letmein") == 0) {
                printf("Password cracked! 🔓\n");
            } else {
                printf("Wrong password.\n");
            }
        }

        // DECRYPT
        else if (strcmp(cmd, "decrypt") == 0) {
            if (level < 2) {
                printf("Command locked. Complete Level 1 first.\n");
                continue;
            }

            char input[50];
            printf("Enter encrypted code: ");
            scanf("%49s", input);

            if (strcmp(input, "KHOOR") == 0) {
                printf("Decrypted: HELLO\n");
                mission3 = 1;
            } else {
                printf("Decryption failed.\n");
            }
        }

        // GETFLAG
        else if (strcmp(cmd, "getflag") == 0) {
            if (level == 1) {
                if (mission1 && mission2) {
                    printf("\033[1;33mFLAG{level_1_complete}\033[0m\n");
                    printf("🚀 Level 2 unlocked!\n");
                    level = 2;
                } else {
                    printf("Complete scan + connect first!\n");
                }
            } 
            else if (level == 2) {
                if (mission3) {
                    printf("\033[1;35mFLAG{you_are_level_2_master}\033[0m\n");
                } else {
                    printf("Complete brute + decrypt first!\n");
                }
            }
        }

        // CLEAR
        else if (strcmp(cmd, "clear") == 0) {
            printf("\033[2J\033[H");
        }

        // EXIT
        else if (strcmp(cmd, "exit") == 0) {
            printf("Goodbye!\n");
            break;
        }

        // UNKNOWN
        else {
            printf("Unknown command: %s\n", cmd);
        }
    }

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int main() {
    // مصفوفة من الحروف والأرقام اللي هتظهر على الشاشة
    char chars[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int i;

    // كود اللون الأخضر (ANSI Escape Code)
    printf("\033[0;32m"); 
    
    // تهيئة الأرقام العشوائية بناءً على وقت الجهاز
    srand(time(NULL)); 

    while(1) {
        for(i = 0; i < 80; i++) {
            // طباعة حرف عشوائي بنسبة معينة لعمل شكل المطر
            if(rand() % 10 > 7) 
                printf("%c ", chars[rand() % 36]);
            else 
                printf("  ");
        }
        printf("\n");
        // سرعة الهبوط بالمايكرو ثانية
        usleep(50000); 
    }

    return 0;
}

# 🟢 Matrix Rain Effect in C 
> مشروع يحاكي تأثير "مطر الماتريكس" الشهير باستخدام لغة C والتعامل المباشر مع شاشة الطرفية (Terminal).

---

### 🛠️ عن المشروع (About)
هذا المشروع هو جزء من رحلتي لإتقان لغة **C** وفهم كيفية التعامل مع:
* الذاكرة وإدارة الموارد.
* الحلقات التكرارية اللانهائية (Infinite Loops).
* رموز الألوان ANSI للتحكم في شكل المخرجات.

### 🚀 المميزات (Features)
* **خفيف جداً:** لا يستهلك موارد الجهاز.
* **تفاعلي:** يعمل على أي Terminal يدعم الألوان (Termux, Linux, VS Code).
* **تعليقات عربية:** الكود مشروح بالكامل باللغة العربية لتبسيط المفاهيم.

### 💻 كيف تشغل المشروع؟
```bash
# ترجمة الكود
gcc matrix.c -o matrix

# تشغيل الأداة
./matrix
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int main() {
    char chars[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    srand(time(NULL));

    printf("\033[2J"); // مسح الشاشة

    while (1) {
        printf("\033[H"); // رجوع للأعلى

        for (int i = 0; i < 20; i++) {
            for (int j = 0; j < 80; j++) {
                if (rand() % 10 > 7) {
                    printf("\033[0;32m%c", chars[rand() % 36]);
                } else {
                    printf(" ");
                }
            }
            printf("\n");
        }

        usleep(80000);
    }

    return 0;
}

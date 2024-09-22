#include <stdio.h>

#include "dump.h"

void dump(void *p, size_t n) {
    char *s = p;
    ssize_t sz = n;

    printf("%p", s);
    while (sz > 0) {
        printf("  ");
        int i = 0;
        int target = 16;
        int left = sz >= 16 ? 16 : sz;
        char signature[16];
        while (left > 0) {
            printf("%02x ", s[i]);
            signature[i] = s[i] >= 32 && s[i] < 127 ? s[i] : '.';
            ++i;
            --target;
            --left;
        }
        if (target == 0)      printf("%.16s\n", signature);
        else if (target < 16) printf("%*.*s%.*s\n", 3*target, 3*target, "",
                                                    16 - target, signature);
        sz -= 16;
        s += 16;
        printf("%p", s);
    }
    printf("\n");
}

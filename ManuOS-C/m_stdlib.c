#include "kernel.h"
#include "m_stdlib.h"

/* Custom standard library for ManuOS */

short m_strcmp(char *str1, char *str2) { // string compare
    while (*str1 && (*str1 == *str2)) {
        str1++;
        str2++;
    }
    return *(unsigned char *)str1 - *(unsigned char *)str2;
}

void m_strcpy(char *dest, char *src) {
    while (*src) {
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0';
}

void m_strcat(char *dest, char *src) {
    while (*dest) {
        dest++;
    }
    m_strcpy(dest, src);
}

short m_strlen(char *str) {
    unsigned int i = 0;
    while (str[i]) {
        i++;
    }
    return i;
}

short m_startsWith(char *str1, char *str2) {
    while (*str2 != '\0') {
        if (*str1 != *str2) {
            return 0;
        }
        str1++;
        str2++;
    }
    return 1;
}
    
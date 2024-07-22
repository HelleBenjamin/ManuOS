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

short m_findstr(char *str1, char *str2) {
    unsigned int i = 0;
    unsigned int j = 0;
    while (str1[i]) {
        if (str1[i] == str2[j]) {
            i++;
            j++;
        } else {
            i = 0;  
            j = 0;
        }
        if (str2[j] == '\0') {
            return 0;
        }
    }
    return 1;
}
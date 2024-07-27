#include "kernel.h"
#include "m_stdlib.h"

/* Custom standard library for ManuOS */

short m_strcmp(const char *str1, const char *str2) { // string compare
    int i = 0;
    while (str1[i] != '\0') {
        if (str1[i] != str2[i]) {
            return 1;
        }
        i++;
    }
    return 0;
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
            return 1;
        }
        str1++;
        str2++;
    }
    return 0;
}

char *strncpy(char *dest, const char *src, int n) {
    int i = 0;
    while (src[i] && i < n) {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    return dest;
}

void* memset(void* s, int c, size_t n) {
    for (size_t i = 0; i < n; i++) {
        ((char*)s)[i] = c;
    }
    return s;
}

void* memcpy(void* dest, const void* src, size_t n) {
    for (size_t i = 0; i < n; i++) {
        ((char*)dest)[i] = ((char*)src)[i];
    }
    return dest;
}

int strncmp(const char *str1, const char *str2, size_t n) {
    for (size_t i = 0; i < n; i++) {
        if (str1[i] != str2[i]) {
            return 1;
        }
    }
    return 0;
}
#include "kernel.h"
#include "m_stdlib.h"

/* Custom standard library for ManuOS */

static char *heap = (char*)0x500;

short strcmp(const char *str1, const char *str2) { // string compare
    int i = 0;
    while (str1[i] != '\0') {
        if (str1[i] != str2[i]) {
            return 1;
        }
        i++;
    }
    return 0;
}

void strcpy(char *dest, char *src) {
    while (*src) {
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0';
}

void strcat(char *dest, char *src) {
    while (*dest) {
        dest++;
    }
    strcpy(dest, src);
}

short strlen(char *str) {
    unsigned int i = 0;
    while (str[i]) {
        i++;
    }
    return i;
}

short startsWith(char *str1, char *str2) {
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


void* malloc(size_t size) {
    char *p = heap;
    heap += size;
    return p;
}

void free(void *ptr) {
    heap = heap - (int)ptr * sizeof(char);
    return;
}

char *strchr(const char *str, int c) {
    while (*str) {
        if (*str == c) {
            return (char*)str;
        }
        str++;
    }
    return NULL;
}

int atoi(const char *str) {
    int num = 0;
    while (*str) {
        num = num * 10 + (*str - '0');
        str++;
    }
    return num;
}

long int strtol(const char *str, char **endptr, int base) {
    long int num = 0;
    int sign = 1;
    if (*str == '+' || *str == '-') {
        if (*str == '-') {
            sign = -1;
        }
        str++;
    }
    while (*str) {
        int digit;
        if (*str >= '0' && *str <= '9') {
            digit = *str - '0';
        } else if (*str >= 'a' && *str <= 'z') {
            digit = *str - 'a' + 10;
        } else if (*str >= 'A' && *str <= 'Z') {
            digit = *str - 'A' + 10;
        } else {
            break;
        }
        if (digit >= base) {
            break;
        }
        num = num * base + digit;
        str++;
    }
    if (endptr) {
        *endptr = (char*)str;
    }
    return sign * num;
}

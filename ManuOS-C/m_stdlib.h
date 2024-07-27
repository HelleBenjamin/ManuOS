#ifndef M_STDLIB_H
#define M_STDLIB_H

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long long uint64_t;
typedef signed char int8_t;
typedef signed short int16_t;
typedef signed int int32_t;
typedef signed long long int64_t;
typedef unsigned char bool;
typedef unsigned long size_t;
#define NULL 0
#define true 1
#define false 0

short m_strcmp(const char *str1, const char *str2); 
void m_strcpy(char *dest, char *src);
void m_strcat(char *dest, char *src);
short m_strlen(char *str);
short m_startsWith(char *str1, char *str2);
char *strncpy(char *dest, const char *src, int n);
void* memset(void* s, int c, size_t n);
void* memcpy(void* dest, const void* src, size_t n);
int strncmp(const char *str1, const char *str2, size_t n);

#endif
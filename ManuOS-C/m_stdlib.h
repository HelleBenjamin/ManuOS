#ifndef M_STDLIB_H
#define M_STDLIB_H

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
#define NULL 0

short m_strcmp(char *str1, char *str2); 
void m_strcpy(char *dest, char *src);
void m_strcat(char *dest, char *src);
short m_strlen(char *str);
short m_startsWith(char *str1, char *str2);

#endif
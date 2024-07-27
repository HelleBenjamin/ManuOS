#include "kernel.h"
#include "m_stdlib.h"

extern void os_main(); // defined in manuos.c

/* Copyright (C) 2024 Benjamin H. All rights reserved. */

/** Kernel functions and syscalls ***/

/* ManuOS filesystem, SBF, Sector Based Filesystem
Filename, 16 bytes, example: text.txt
Extension, 3 bytes
Directory, 2 bytes, example: A

*/

#define SECTOR_SIZE 512
#define FS_START_SECTOR 60
#define MAX_FILES 100
#define MAX_FILENAME_LENGTH 16
#define MAX_EXTENSION_LENGTH 4
#define MAX_DIRECTORIES 10
#define MAX_DIRECTORY_NAME_LENGTH 16

typedef struct {
    char filename[MAX_FILENAME_LENGTH];
    char extension[MAX_EXTENSION_LENGTH];
    char directory[MAX_DIRECTORY_NAME_LENGTH];
    uint32_t sector;
    uint32_t size;
} FileSystemEntry;

typedef struct {
    char name[MAX_DIRECTORY_NAME_LENGTH];
    char parent[MAX_DIRECTORY_NAME_LENGTH];
} DirectoryEntry;

FileSystemEntry fileSystem[MAX_FILES];
DirectoryEntry directories[MAX_DIRECTORIES];
uint8_t fileSystemEntries = 0;
uint8_t directoryEntries = 0;

char currentDirectory[MAX_DIRECTORY_NAME_LENGTH];


char* getCurrentDir() {
    return currentDirectory;
}


void fs_initialize() {
    if (fs_load() != 0) {
        fileSystemEntries = 0;
        directoryEntries = 0;
        m_strcpy(directories[directoryEntries].name, "/");
        m_strcpy(directories[directoryEntries].parent, "/");
        directoryEntries++;
    }

}

int save_file_system() {
    char buffer[SECTOR_SIZE];
    int sector = FS_START_SECTOR;
    int offset = 0;

    memset(buffer, 0, SECTOR_SIZE);
    for (int i = 0; i < directoryEntries; i++) {
        if (offset + MAX_DIRECTORY_NAME_LENGTH * 2 > SECTOR_SIZE) {
            if (disk_write(buffer, sector++, 1) != 0) {
                return -1; // Error writing to disk
            }
            offset = 0;
            memset(buffer, 0, SECTOR_SIZE);
        }
        memcpy(buffer + offset, directories[i].name, MAX_DIRECTORY_NAME_LENGTH);
        offset += MAX_DIRECTORY_NAME_LENGTH;
        memcpy(buffer + offset, directories[i].parent, MAX_DIRECTORY_NAME_LENGTH);
        offset += MAX_DIRECTORY_NAME_LENGTH;
    }
    if (offset > 0) {
        if (disk_write(buffer, sector++, 1) != 0) {
            return -1; // Error writing to disk
        }
    }

    offset = 0;
    memset(buffer, 0, SECTOR_SIZE);
    for (int i = 0; i < fileSystemEntries; i++) {
        if (offset + MAX_FILENAME_LENGTH + MAX_EXTENSION_LENGTH + MAX_DIRECTORY_NAME_LENGTH + 2 * sizeof(uint32_t) > SECTOR_SIZE) {
            if (disk_write(buffer, sector++, 1) != 0) {
                return -1; // Error writing to disk
            }
            offset = 0;
            memset(buffer, 0, SECTOR_SIZE);
        }
        memcpy(buffer + offset, fileSystem[i].filename, MAX_FILENAME_LENGTH);
        offset += MAX_FILENAME_LENGTH;
        memcpy(buffer + offset, fileSystem[i].extension, MAX_EXTENSION_LENGTH);
        offset += MAX_EXTENSION_LENGTH;
        memcpy(buffer + offset, fileSystem[i].directory, MAX_DIRECTORY_NAME_LENGTH);
        offset += MAX_DIRECTORY_NAME_LENGTH;
        memcpy(buffer + offset, &fileSystem[i].sector, sizeof(uint32_t));
        offset += sizeof(uint32_t);
        memcpy(buffer + offset, &fileSystem[i].size, sizeof(uint32_t));
        offset += sizeof(uint32_t);
    }
    if (offset > 0) {
        if (disk_write(buffer, sector++, 1) != 0) {
            return -1; // Error writing to disk
        }
    }

    return 0;
}

int load_file_system() {
    char buffer[SECTOR_SIZE];
    int sector = FS_START_SECTOR;
    int offset = 0;

    directoryEntries = 0;
    while (directoryEntries < MAX_DIRECTORIES) {
        if (disk_read(buffer, sector++, 1) != 0) {
            return -1; // Error reading from disk
        }
        offset = 0;
        while (offset < SECTOR_SIZE && directoryEntries < MAX_DIRECTORIES) {
            if (buffer[offset] == 0) {
                break; // End of valid entries
            }
            memcpy(directories[directoryEntries].name, buffer + offset, MAX_DIRECTORY_NAME_LENGTH);
            offset += MAX_DIRECTORY_NAME_LENGTH;
            memcpy(directories[directoryEntries].parent, buffer + offset, MAX_DIRECTORY_NAME_LENGTH);
            offset += MAX_DIRECTORY_NAME_LENGTH;
            directoryEntries++;
        }
        if (buffer[offset] == 0) {
            break; // End of valid entries
        }
    }

    fileSystemEntries = 0;
    while (fileSystemEntries < MAX_FILES) {
        if (disk_read(buffer, sector++, 1) != 0) {
            return -1; // Error reading from disk
        }
        offset = 0;
        while (offset < SECTOR_SIZE && fileSystemEntries < MAX_FILES) {
            if (buffer[offset] == 0) {
                break; // End of valid entries
            }
            memcpy(fileSystem[fileSystemEntries].filename, buffer + offset, MAX_FILENAME_LENGTH);
            offset += MAX_FILENAME_LENGTH;
            memcpy(fileSystem[fileSystemEntries].extension, buffer + offset, MAX_EXTENSION_LENGTH);
            offset += MAX_EXTENSION_LENGTH;
            memcpy(fileSystem[fileSystemEntries].directory, buffer + offset, MAX_DIRECTORY_NAME_LENGTH);
            offset += MAX_DIRECTORY_NAME_LENGTH;
            memcpy(&fileSystem[fileSystemEntries].sector, buffer + offset, sizeof(uint32_t));
            offset += sizeof(uint32_t);
            memcpy(&fileSystem[fileSystemEntries].size, buffer + offset, sizeof(uint32_t));
            offset += sizeof(uint32_t);
            fileSystemEntries++;
        }
        if (buffer[offset] == 0) {
            break; // End of valid entries
        }
    }

    return 0;
}


int fs_mkdir(const char* name) {
    if (directoryEntries >= MAX_DIRECTORIES) {
        return -1; // Directory limit reached
    }

    for (int i = 0; i < directoryEntries; i++) {
        if (m_strcmp(directories[i].name, name) == 0 && m_strcmp(directories[i].parent, currentDirectory) == 0) {
            return -2; // Directory already exists
        }
    }

    m_strcpy(directories[directoryEntries].name, name);
    m_strcpy(directories[directoryEntries].parent, currentDirectory);
    directoryEntries++;
    return 0; // Success
}

int fs_chdir(const char* name) {
    if (m_strcmp(name, "/") == 0) {
        m_strcpy(currentDirectory, "/");
        return 0; // Success
    }

    if (m_strcmp(name, "..") == 0) {
        if (m_strcmp(currentDirectory, "/") == 0) {
            return 0; // Already at root
        }

        for (int i = 0; i < directoryEntries; i++) {
            if (m_strcmp(directories[i].name, currentDirectory) == 0) {
                m_strcpy(currentDirectory, directories[i].parent);
                return 0; // Success
            }
        }
        return -1; // Parent directory not found
    }

    for (int i = 0; i < directoryEntries; i++) {
        if (m_strcmp(directories[i].name, name) == 0 && m_strcmp(directories[i].parent, currentDirectory) == 0) {
            m_strcpy(currentDirectory, directories[i].name);
            return 0; // Success
        }
    }
    return -1; // Directory not found
}



int fs_create(const char *filename, const char *extension, const char *directory, uint32_t size) {
    if (fileSystemEntries >= MAX_FILES) {
        return -1; // No space for new files
    }
    for (int i = 0; i < fileSystemEntries; i++) {
        if (strncmp(fileSystem[i].filename, filename, MAX_FILENAME_LENGTH) == 0 &&
            strncmp(fileSystem[i].extension, extension, MAX_EXTENSION_LENGTH) == 0 &&
            strncmp(fileSystem[i].directory, directory, MAX_DIRECTORY_NAME_LENGTH) == 0) {
            return -1; // File already exists
        }
    }

    uint32_t sectors_needed = (size + SECTOR_SIZE - 1) / SECTOR_SIZE;
    uint32_t start_sector = FS_START_SECTOR + 10; // Skip 10 sectors for file system metadata

    for (uint32_t sector = start_sector; sector < start_sector + sectors_needed; sector++) {
        // Check if the sector is free
        int sector_in_use = 0;
        for (int i = 0; i < fileSystemEntries; i++) {
            uint32_t file_sectors = (fileSystem[i].size + SECTOR_SIZE - 1) / SECTOR_SIZE;
            if (sector >= fileSystem[i].sector && sector < fileSystem[i].sector + file_sectors) {
                sector_in_use = 1;
                break;
            }
        }
        if (!sector_in_use) {
            // Allocate this sector to the new file
            fileSystem[fileSystemEntries].sector = sector;
            break;
        }
    }

    strncpy(fileSystem[fileSystemEntries].filename, filename, MAX_FILENAME_LENGTH);
    strncpy(fileSystem[fileSystemEntries].extension, extension, MAX_EXTENSION_LENGTH);
    strncpy(fileSystem[fileSystemEntries].directory, directory, MAX_DIRECTORY_NAME_LENGTH);
    fileSystem[fileSystemEntries].size = size;

    fileSystemEntries++;
    return 0; // File created successfully
}

FileSystemEntry* fs_find(const char* filename, const char* extension) {
    for (int i = 0; i < fileSystemEntries; i++) {
        if (m_strcmp(fileSystem[i].filename, filename) == 0 &&
            m_strcmp(fileSystem[i].extension, extension) == 0 &&
            m_strcmp(fileSystem[i].directory, currentDirectory) == 0) {
            return &fileSystem[i];
        }
    }
    return NULL; // File not found
}


int fs_write(const char *filename, const char *extension, const char *content, uint32_t size) {
    for (int i = 0; i < fileSystemEntries; i++) {
        if (strncmp(fileSystem[i].filename, filename, MAX_FILENAME_LENGTH) == 0 &&
            strncmp(fileSystem[i].extension, extension, MAX_EXTENSION_LENGTH) == 0) {
            
            uint32_t num_sectors = (size + SECTOR_SIZE - 1) / SECTOR_SIZE; // Calculate needed sectors
            for (uint32_t j = 0; j < num_sectors; j++) {
                if (disk_write((char *)(content + j * SECTOR_SIZE), fileSystem[i].sector + j, 1) != 0) {
                    prints("-1");
                    return -1; // Error writing to disk
                }
            }
            fileSystem[i].size = size;
            return 0; // Successfully written
        }
    }
    prints("-2");
    return -2; // File not found
}

int fs_read(const char *filename, const char *extension, char *buffer, uint32_t size) {
    for (int i = 0; i < fileSystemEntries; i++) {
        if (strncmp(fileSystem[i].filename, filename, MAX_FILENAME_LENGTH) == 0 &&
            strncmp(fileSystem[i].extension, extension, MAX_EXTENSION_LENGTH) == 0) {
            
            uint32_t num_sectors = (size + SECTOR_SIZE - 1) / SECTOR_SIZE; // Calculate needed sectors
            for (uint32_t j = 0; j < num_sectors; j++) {
                if (disk_read((char *)(buffer + j * SECTOR_SIZE), fileSystem[i].sector + j, 1) != 0) {
                    prints("-2");
                    return -2; // Error reading from disk
                }
            }
            return 0; // Successfully read
        }
    }
    prints("-1");
    return -1; // File not found
}


void fs_list() {
    for (int i = 0; i < fileSystemEntries; i++) {
        FileSystemEntry* entry = &fileSystem[i];
        prints(entry->filename);
        prints(".");
        prints(entry->extension);
        newline();;
    }
}

void fs_dir() {
    for (int i = 0; i < directoryEntries; i++) {
        DirectoryEntry* entry = &directories[i];
        prints(entry->name);
        newline();
    }
}

int fs_delete(const char* filename, const char* extension) {
    FileSystemEntry* entry = fs_find(filename, extension);
    if (entry == NULL) {
        return -1; // File not found
    }

    for (int i = entry - fileSystem; i < fileSystemEntries - 1; i++) {
        fileSystem[i] = fileSystem[i + 1];
    }
    fileSystemEntries--;
    return 0; // Success
}

int fs_save() {
    char buffer[SECTOR_SIZE];
    int sector = FS_START_SECTOR;
    int offset = 0;

    memset(buffer, 0, SECTOR_SIZE);
    for (int i = 0; i < directoryEntries; i++) {
        if (offset + MAX_DIRECTORY_NAME_LENGTH * 2 > SECTOR_SIZE) {
            if (disk_write(buffer, sector++, 1) != 0) {
                return -1; // Error writing to disk
            }
            offset = 0;
            memset(buffer, 0, SECTOR_SIZE);
        }
        memcpy(buffer + offset, directories[i].name, MAX_DIRECTORY_NAME_LENGTH);
        offset += MAX_DIRECTORY_NAME_LENGTH;
        memcpy(buffer + offset, directories[i].parent, MAX_DIRECTORY_NAME_LENGTH);
        offset += MAX_DIRECTORY_NAME_LENGTH;
    }
    if (offset > 0) {
        if (disk_write(buffer, sector++, 1) != 0) {
            return -1; // Error writing to disk
        }
    }

    offset = 0;
    memset(buffer, 0, SECTOR_SIZE);
    for (int i = 0; i < fileSystemEntries; i++) {
        if (offset + MAX_FILENAME_LENGTH + MAX_EXTENSION_LENGTH + MAX_DIRECTORY_NAME_LENGTH + 2 * sizeof(uint32_t) > SECTOR_SIZE) {
            if (disk_write(buffer, sector++, 1) != 0) {
                return -1; // Error writing to disk
            }
            offset = 0;
            memset(buffer, 0, SECTOR_SIZE);
        }
        memcpy(buffer + offset, fileSystem[i].filename, MAX_FILENAME_LENGTH);
        offset += MAX_FILENAME_LENGTH;
        memcpy(buffer + offset, fileSystem[i].extension, MAX_EXTENSION_LENGTH);
        offset += MAX_EXTENSION_LENGTH;
        memcpy(buffer + offset, fileSystem[i].directory, MAX_DIRECTORY_NAME_LENGTH);
        offset += MAX_DIRECTORY_NAME_LENGTH;
        memcpy(buffer + offset, &fileSystem[i].sector, sizeof(uint32_t));
        offset += sizeof(uint32_t);
        memcpy(buffer + offset, &fileSystem[i].size, sizeof(uint32_t));
        offset += sizeof(uint32_t);
    }
    if (offset > 0) {
        if (disk_write(buffer, sector++, 1) != 0) {
            return -1; // Error writing to disk
        }
    }

    return 0;
}

int fs_load() {
    char buffer[SECTOR_SIZE];
    int sector = FS_START_SECTOR;
    int offset = 0;

    directoryEntries = 0;
    while (directoryEntries < MAX_DIRECTORIES) {
        if (disk_read(buffer, sector++, 1) != 0) {
            return -1; // Error reading from disk
        }
        offset = 0;
        while (offset < SECTOR_SIZE && directoryEntries < MAX_DIRECTORIES) {
            if (buffer[offset] == 0) {
                break; // End of valid entries
            }
            memcpy(directories[directoryEntries].name, buffer + offset, MAX_DIRECTORY_NAME_LENGTH);
            offset += MAX_DIRECTORY_NAME_LENGTH;
            memcpy(directories[directoryEntries].parent, buffer + offset, MAX_DIRECTORY_NAME_LENGTH);
            offset += MAX_DIRECTORY_NAME_LENGTH;
            directoryEntries++;
        }
        if (buffer[offset] == 0) {
            break; // End of valid entries
        }
    }

    fileSystemEntries = 0;
    while (fileSystemEntries < MAX_FILES) {
        if (disk_read(buffer, sector++, 1) != 0) {
            return -1; // Error reading from disk
        }
        offset = 0;
        while (offset < SECTOR_SIZE && fileSystemEntries < MAX_FILES) {
            if (buffer[offset] == 0) {
                break; // End of valid entries
            }
            memcpy(fileSystem[fileSystemEntries].filename, buffer + offset, MAX_FILENAME_LENGTH);
            offset += MAX_FILENAME_LENGTH;
            memcpy(fileSystem[fileSystemEntries].extension, buffer + offset, MAX_EXTENSION_LENGTH);
            offset += MAX_EXTENSION_LENGTH;
            memcpy(fileSystem[fileSystemEntries].directory, buffer + offset, MAX_DIRECTORY_NAME_LENGTH);
            offset += MAX_DIRECTORY_NAME_LENGTH;
            memcpy(&fileSystem[fileSystemEntries].sector, buffer + offset, sizeof(uint32_t));
            offset += sizeof(uint32_t);
            memcpy(&fileSystem[fileSystemEntries].size, buffer + offset, sizeof(uint32_t));
            offset += sizeof(uint32_t);
            fileSystemEntries++;
        }
        if (buffer[offset] == 0) {
            break; // End of valid entries
        }
    }

    return 0;
}


void newline() {
    asm(
        "mov $0x0a, %al\n\t"
        "call printchr\n\t"
        "mov $0x0d, %al\n\t"
        "call printchr\n\t"
        "mov $0x0d, %al\n\t"
        "call printchr\n\t"
    );
}

asm(
    "printchr: \n\t"
    "   mov $0x0e, %ah\n\t"
    "   int $0x10\n\t"
    "   ret\n\t"
);
int disk_read(char *buffer, int sector, int num_sectors) {
    int status;
    int heads_per_cyl = 2;
    int sectors_per_track = 18;
    int cylinder = sector / (heads_per_cyl * sectors_per_track);
    int temp = sector % (heads_per_cyl * sectors_per_track);
    int head = temp / sectors_per_track;
    int sec = temp % sectors_per_track + 1;
    int ch = cylinder & 0xFF;
    int cl = (sec & 0x3F) | ((cylinder >> 2) & 0xC0);

    asm volatile (
        "int $0x13"
        : "=a" (status)
        : "a" ((0x02 << 8) | num_sectors),
          "c" ((ch << 8) | cl),
          "d" ((head << 8) | 0x00),
          "b" (buffer)
        : "cc", "memory"
    );
    return (status & 0xFF00) == 0 ? 0 : (status >> 8);
}

int disk_write(char *buffer, int sector, int num_sectors) {
    if (sector < FS_START_SECTOR) {
        return -1; // Prevent writing outside the file system area
    }

    int status;
    int heads_per_cyl = 2;
    int sectors_per_track = 18;
    int cylinder = sector / (heads_per_cyl * sectors_per_track);
    int temp = sector % (heads_per_cyl * sectors_per_track);
    int head = temp / sectors_per_track;
    int sec = temp % sectors_per_track + 1;
    int ch = cylinder & 0xFF;
    int cl = (sec & 0x3F) | ((cylinder >> 2) & 0xC0);

    asm volatile (
        "int $0x13"
        : "=a" (status)
        : "a" ((0x03 << 8) | num_sectors),
          "c" ((ch << 8) | cl),
          "d" ((head << 8) | 0x00),
          "b" (buffer)
        : "cc", "memory"
    );
    return (status & 0xFF00) == 0 ? 0 : (status >> 8);
}


void cls() { // clear screen
    asm(
        "mov $0x00, %ah\n\t"
        "mov $0x03, %al\n\t"
        "int $0x10\n\t"
    );
}
void sleepms(unsigned long ms) { // sleep milliseconds
   for (unsigned long i = 0; i < ms * 2000; i++) {
       asm("nop\n\t");
   }
}
char numToAscii(int num) {
    return '0' + num;
}
short asciiToNum(char c) {
    return c - 48;
}
void printc(char c) {
    asm(
        "nop\n\t"
        :
        : "al"(c)
    );
    asm("call printchr\n\t");
}

void prints(char *s) {
    while (*s) {
        printc(*s);
        s++;
    }
}

void printi(int i) {
    char buf[10];
    int j = 0;
    if (i < 0) {
        printc('-');
        i *= -1;
    }
    while (i > 0) {
        buf[j++] = i % 10 + '0';
        i /= 10;
    }
    while (j > 0) {
        printc(buf[--j]);
    }
}

void kernel_panic(char *msg) {
    prints("KERNEL PANIC: ");
    prints(msg);
    newline();
    while (1) {
        sleepms(100);
    }
}

char getc() {
    char c = 0;
    asm(
        "mov $0x00, %%ah\n\t"
        "int $0x16\n\t"
        : "=al"(c)
        :
    );
    return c;
}

short ifESC() {
    char c;
        asm(
        "mov $0x01, %%ah\n\t"
        "int $0x16\n\t"
        : "=al"(c)
        :
    );
    if (c == 0x1b) {
        return 1;
    }
    return 0;
}
char getch() {
    char c = 0;
    while (1) {
        c = getc();
        if (c != 0) {
            break;
        }
    }
    return c;
}

int geti() {
    char c = 0;
    int i = 0;
    while (1) {
        c = getc();
        printc(c);
        if (c >= '0' && c <= '9') {
            i = i * 10 + (c - '0');
        } else if (c == '-') {
            i *= -1;
        } else {
            break;
        }
    }
    return i;
}

short gets(char *s) { //retuns length
    int i = 0;
    while (1) {
        s[i] = getc();
        printc(s[i]);
        if (s[i] == NEWLINE) {
            s[i] = 0;
            break;
        }
        if (s[i] == 0x08) {
            i--;
            printc(' ');
            printc(0x08);
            s[i] = '\0';
            i--;
        }
        i++;
    }
    return i;
    
}
int getih() {
    int i = 0;
    while (1) {
        i = geti();
        if (i != 0) {
            break;
        }
    }
    return i;
}

unsigned long a = 1664525;
unsigned long c = 1013904223;
unsigned long m = 4294967290;

unsigned long seed;

void initialize_seed(unsigned long initial_seed) {
    seed = initial_seed;
}

unsigned long lcg() {
    seed = (a * seed + c) % m;
    return seed;
}


unsigned long get_bios_time() {
    unsigned long time = 0;
    __asm__ __volatile__ (
        "int $0x1A"
        : "=c" (((unsigned char *)&time)[1]),
          "=d" (((unsigned char *)&time)[0]),
          "=b" (((unsigned char *)&time)[2]),
          "=a" (((unsigned char *)&time)[3])
        : "a" (0x0000)
    );

    return time;
}
unsigned long random(unsigned long min, unsigned long max) {
    unsigned long range = max - min + 1;
    unsigned long random_value = lcg() % range;
    return min + random_value;
}

void WriteCharacter(unsigned char c, unsigned char forecolour, unsigned char backcolour, int x, int y){
    short attrib = (backcolour << 4) | (forecolour & 0x0F);
    volatile short * where;
    where = (volatile short *)0xB8000 + (y * 80 + x) ;
    *where = c | (attrib << 8);
}

void WriteGpixel(unsigned char backcolour, int x, int y){
    WriteCharacter(' ', 0xf, backcolour, x, y);
}

void restart() {
    __asm__ __volatile__ (
        "cli\n\t"
        "movw $0x1234, %ax\n\t"
        "movw %ax, %ds \n\t"
        "movw %ax, %es \n\t"
        "movw %ax, %fs \n\t"
        "movw %ax, %gs \n\t"
        "movw %ax, %ss \n\t"
        "ljmp $0xF000, $0xE05B \n\t"
    );
}

void kernel_main(void) {
    os_main(); // Call any other required initialization functions
}


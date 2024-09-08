#include "kernel.h"
#include "manuos.h"
#include "m_stdlib.h"
#include "simplegl.h"

/* ManuOS graphics library */

uint8_t coordX;
uint8_t coordY;

void initSGL() {

    coordX = 0;
    coordY = 0;
}

void SGLdrawSquare(int x, int y, int size, int color) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            WriteGpixel(color, x + i, y + j);
        }
    }
}

void SGLdrawLine(int x1, int y1, int x2, int y2, int color) {
    while (x1 != x2 || y1 != y2) {
        WriteGpixel(color, x1, y1);
        if (x1 < x2) {
            x1++;
        }
        if (x1 > x2) {
            x1--;
        }
        if (y1 < y2) {
            y1++;
        }
        if (y1 > y2) {
            y1--;
        }
    }
    return;
}
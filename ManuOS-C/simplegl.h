#ifndef SIMPLEGL_H
#define SIMPLEGL_H

#define SGL_VERSION 01

#define MAX_Y 25
#define MAX_X 80

void initSGL();

void SGLdrawSquare(int x, int y, int size, int color);
void SGLdrawLine(int x1, int y1, int x2, int y2, int color);


#endif
#ifndef SCREEN_H
#define SCREEN_H

#include "utils.h"

static const char COLOR_BLACK = 0;
static const char COLOR_BLUE = 1;
static const char COLOR_GREEN = 2;
static const char COLOR_CYAN = 3;
static const char COLOR_RED = 4;
static const char COLOR_MAGENTA = 5;
static const char COLOR_BROWN = 6;
static const char COLOR_LIGHT_GREY = 7;
static const char COLOR_DARK_GREY = 8;
static const char COLOR_LIGHT_BLUE = 9;
static const char COLOR_LIGHT_GREEN = 10;
static const char COLOR_LIGHT_CYAN = 11;
static const char COLOR_LIGHT_RED = 12;
static const char COLOR_LIGHT_MAGENTA = 13;
static const char COLOR_LIGHT_BROWN = 14;
static const char COLOR_WHITE = 15;

static const int CS_WIDTH=80;
static const int CS_HEIGHT=25;
int csRow;
int csColumn;
char csColor;
short* csBuffer;
int csBackLimit;

void csInit();
char csMakeColor(const char font, const char back);
short csMakeEntry(const char character, const char color);
void csSetColor(char color);
void csClear();
void csHelp();
void csScrollDown();
extern char outport(short port, char data);
void csUpdateCursor();
void csCharAt(const char character, const int x, const int y);
void csChar(const char character);
void csString(const char* data);
void csStringConst(const char* data);

#endif

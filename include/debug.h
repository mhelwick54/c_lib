#ifndef DEBUG_H
#define DEBUG_H

#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#define DEBUG_OUT stdout

void debug(char *fmt, char* msg, ...);

#endif

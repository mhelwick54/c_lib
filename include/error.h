#ifndef ERROR_H
#define ERROR_H

#include <stdio.h>
#include <stdlib.h>

#define CRITICAL 1
#define ERROR 2
#define ALLOC_FAILURE -2

#define ERR_OUT stderr

void error(int err_level, char* msg, int err_code);

#endif //ERROR_H

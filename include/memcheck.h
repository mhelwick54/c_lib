#ifndef MEMCHECK_H
#define MEMCHECK_H

#include <stdlib.h>

#include "error.h"

void mem_check(void* mem) {
	if(mem == NULL) {
		error(CRITICAL, "memory allocation failed", ALLOC_FAILURE);
	}
}

#endif //MEMCHECK_H

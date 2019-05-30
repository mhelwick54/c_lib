#include "../include/array.h"

T FN(at)(Array* arr, ...) {
	va_list args;
	va_start(args, arr);
	int dims[DIM];
	int i = 0;
	for(i = 0; i < DIM; ++i) {
		dims[i] = va_arg(args, int);
	}
	debug((void*)dims, %d, DIM);
}

void FN(insert)(Array* arr, T data, ...) {

}

void FN(delete)(Array* arr, ...) {

}

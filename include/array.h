/*******************************************************************************
 *	An array that can resize automatically to fit data, up to 3 dimensions
 *	Usage: 	#define DIM [dimensions]
 *			#define T [typename]
 *		   	#define PREFIX [typename]_
 *		   	#include "array.h"
 ******************************************************************************/

 #include <stdarg.h>
 #include <stdlib.h>

 #include "memcheck.h"

#ifndef DIM
	#define DIM 1
#endif
#ifndef PREFIX
	#define PREFIX
#endif //PREFIX
#ifndef T
	#error No template type defined
#endif //T
#define CCAT2(x, y) x##y
#define CCAT(x, y) CCAT2(x, y)
#define FN(x) CCAT(PREFIX, x)

union array {
	T* 		oneD;
	T** 	twoD;
	T*** 	threeD;
};

typedef struct Auto_Array {
	union array ptr;
	int dims[DIM];
} Array;

/*******************************************************************************
 *	Function:	type_arr_init
 *	Arguments:	Array* arr, [DIM] int dimensions
 *	Purpose:	create the array struct, allocate memory, set sizes
 *	Notes:
 ******************************************************************************/
Array* FN(arr_init)(Array* arr, ...) {
	va_list args;
	va_start(args, arr);
	if(DIM == 1) {
		int size = va_arg(args, int);
		debug("%d", "size", size);
		arr = malloc(sizeof(arr));
		arr->ptr.oneD = malloc(size * sizeof(T));
		mem_check((void*)arr->ptr.oneD);
		int i = 0;
		for(i = 0; i < size; ++i) {
			arr->ptr.oneD[i] = (T)0;
		}
		arr->dims[0] = size;
	} else if(DIM == 2) {
		int rows = va_arg(args, int);
		debug("%d", "rows", rows);
		int cols = va_arg(args, int);
		debug("%d", "cols", cols);
		arr = malloc(sizeof(arr));
		arr->ptr.twoD = malloc(rows * sizeof(T*));
		mem_check((void*)arr->ptr.twoD);
		int i = 0, j = 0;
		for(i = 0; i < rows; ++i) {
			arr->ptr.twoD[i] = malloc(cols * sizeof(T));
			mem_check((void*)arr->ptr.twoD[i]);
			for(j = 0; j < cols; ++j) {
				arr->ptr.twoD[i][j] = (T)0;
			}
		}
		arr->dims[0] = rows;
		arr->dims[1] = cols;
	} else {
		int rows = va_arg(args, int);
		debug("%d", "rows", rows);
		int cols = va_arg(args, int);
		debug("%d", "cols", cols);
		int third = va_arg(args, int);
		debug("%d", "third", third);
		arr = malloc(sizeof(arr));
		arr->ptr.threeD = malloc(rows * sizeof(T**));
		mem_check((void*)arr->ptr.threeD);
		int i = 0, j = 0, k = 0;
		for(i = 0; i < rows; ++i) {
			arr->ptr.threeD[i] = malloc(cols * sizeof(T*));
			mem_check((void*)arr->ptr.threeD[i]);
			for(j = 0; j < cols; ++j) {
				arr->ptr.threeD[i][j] = malloc(third * sizeof(T));
				mem_check((void*)arr->ptr.threeD[i][j]);
				for(k = 0; k < third; ++k) {
					arr->ptr.threeD[i][j][k] = (T)0;
				}
			}
		}
		arr->dims[0] = rows;
		arr->dims[1] = cols;
		arr->dims[2] = third;
	}
	return arr;
}

/*******************************************************************************
 *	Function:	type_at
 *	Arguments:	Array* arr, [DIM] int indices
 *	Purpose:	return the value at the given indices
 *	Notes:
 ******************************************************************************/
T FN(arr_at)(Array* arr, ...) {
	va_list args;
	va_start(args, arr);
	int dims[DIM];
	int i = 0;
	for(i = 0; i < DIM; ++i) {
		dims[i] = va_arg(args, int);
		debug("%d", "at index", dims[i]);
	}
	if(DIM == 1) {
		return *(arr->ptr.oneD + dims[0]);
	} else if(DIM == 2) {
		return *(*(arr->ptr.twoD + dims[0]) + dims[1]);
	} else {
		return *(*(*(arr->ptr.threeD + dims[0]) + dims[1]) + dims[2]);
	}
	return (T)(-1);
}

void resize_oneD(T* arr, int old_size, int new_size) {
	arr = realloc(arr, new_size * sizeof(T));
	mem_check((void*)arr);
}

void resize_twoD(T** arr, int* old_dims, int* new_dims) {
	if(new_dims[0] > old_dims[0]) {
		arr = realloc(arr, new_dims[0] * sizeof(T*));
		int i = 0;
		for(i = old_dims[0]; i < new_dims[0]; ++i) {
			arr[i] = malloc(old_dims[1] * sizeof(T));
			mem_check(arr[i]);
		}
	}
	if(new_dims[1] > old_dims[1]) {
		int i = 0;
		for(i = 0; i < new_dims[0]; ++i) {
			arr[i] = realloc(arr[i], new_dims[1] * sizeof(T));
			mem_check(arr[i]);
		}
	}
}

void resize_threeD(T*** arr, int* old_dims, int* new_dims) {

}

/*******************************************************************************
 *	Function:	type_arr_insert
 *	Arguments:	Array* arr, typename data, [DIM] int indices
 *	Purpose:	insert an element at the specified indices
 *	Notes:		if outside of current dimensions, will resize to fit
 ******************************************************************************/
void FN(arr_insert)(Array* arr, T data, ...) {
	va_list args;
	va_start(args, data);
	int dims[DIM];
	int i = 0;
	for(i = 0; i < DIM; ++i) {
		dims[i] = va_arg(args, int);
		debug("%d", "insert index", dims[i]);
	}
	if(DIM == 1) {
		if(arr->dims[0] <= dims[0]) {
			arr->dims[0] = dims[0] + 1;
			arr->ptr.oneD = realloc(arr->ptr.oneD, (dims[0] + 1) * sizeof(T));
		}
		arr->ptr.oneD[dims[0]] = data;
	} else if(DIM == 2) {
		if(arr->dims[0] <= dims[0]) {
			arr->ptr.twoD = realloc(arr->ptr.oneD, (dims[0] + 1) * sizeof(T*));
			int i = 0;
			for(i = arr->dims[0]; i < dims[0] + 1; ++i) {
				arr->ptr.twoD[i] = malloc(arr->dims[1] * sizeof(T));
			}
			arr->dims[0] = dims[0] + 1;
		}
		if(arr->dims[1] <= dims[1]) {
			int i = 0;
			for(i = 0; i < dims[0]; ++i) {
				arr->ptr.twoD[i] = realloc(arr->ptr.twoD[i], (dims[1] + 1) * sizeof(T));
				arr->dims[1] = dims[1] + 1;
			}
		}
		arr->ptr.twoD[dims[0]][dims[1]] = data;
	} else {

	}
}

void FN(arr_delete)(Array* arr, ...) {

}

#undef DIM
#undef T
#undef PREFIX
#undef CCAT
#undef CCAT2
#undef FN

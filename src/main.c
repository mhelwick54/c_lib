#include "../include/main.h"

int main() {
	Array* arr = NULL;
	arr = int_arr_init(arr, 10);
	arr->ptr.oneD[5] = 10;
	printf("%d\n", int_arr_at(arr, 5));

	return 0;
}

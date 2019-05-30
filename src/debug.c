#include "../include/debug.h"

void debug(char* fmt, char* msg, ...) {
	va_list args;
	va_start(args, msg);
	if(strcmp(fmt, "%d") == 0) {	//int
		int arg = va_arg(args, int);
		fprintf(DEBUG_OUT, "%s: %d\n", msg, arg);
	} else if(strcmp(fmt, "%c") == 0) {		//char
		int arg = va_arg(args, int);
		fprintf(DEBUG_OUT, "%s: %c\n", msg, arg);
	} else if(strcmp(fmt, "%s") == 0) {		//string
		char *arg = va_arg(args, char*);
		fprintf(DEBUG_OUT, "%s: %s\n", msg, arg);
	} else if(strcmp(fmt, "%f") == 0) {		//float
		double arg = va_arg(args, double);
		fprintf(DEBUG_OUT, "%s: %f\n", msg, arg);
	}
}

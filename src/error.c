#include "../include/error.h"

void error(int err_level, char* msg, int err_code) {
	if(err_level == CRITICAL) {
		fprintf(ERR_OUT, "critical error: %s (%d)\n", msg, err_code);
		exit(err_code);
	} else {
		fprintf(ERR_OUT, "error: %s (%d)\n", msg, err_code);
	}
}

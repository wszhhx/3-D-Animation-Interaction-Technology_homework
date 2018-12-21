#include "CallBackFuncs.h"
#include <iostream>

void error_callback(int error, const char* description)
{
	fprintf(stderr, "Error: %s\n", description);
}

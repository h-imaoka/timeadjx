#include "includes.h"

void Usage(char *szProgram);

int main(int argc, char *argv[]) {

	if (argc < 2) {
		Usage(argv[0]);
		exit(1);
	}

	if (!strcmp (argv[1], "set")) {
		CallSetSystemTimeAdjustment(atoi(argv[2]));
	}
	else if (!strcmp (argv[1], "get")) {
		CallGetSystemTimeAdjustment();
	}
	else 
		Usage(argv[0]);
	exit (0);
}

void Usage(char *szProgram) {
	printf("%s [get|set <100ns>] (Ver.0.2, 2005.02.20)\n", szProgram);
	exit(2);
}




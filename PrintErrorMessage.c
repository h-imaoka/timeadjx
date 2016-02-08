#include "includes.h"

#define OFFSET 56

void PrintErrorMessage(char *szFile, char *szFunction, int nLine) {
	LPVOID lpMsgBuf;

	FormatMessage(
	    FORMAT_MESSAGE_ALLOCATE_BUFFER |
	    FORMAT_MESSAGE_FROM_SYSTEM |
	    FORMAT_MESSAGE_IGNORE_INSERTS,
	    NULL,
	    GetLastError(),
	    MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
	    (LPTSTR) &lpMsgBuf,
	    0,
	    NULL
	);

	fprintf(stderr, "%s:%d: %s: %s\n", szFile+OFFSET, nLine, szFunction, lpMsgBuf);
	LocalFree(lpMsgBuf);
}

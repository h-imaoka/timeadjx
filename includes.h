#include <windows.h>
#include <stdio.h>


void PrintErrorMessage(char *szFile, char *szFunction, int nLine);
BOOL SetPrivilege(HANDLE hToken, LPCTSTR Privilege, BOOL bEnablePrivilege);
BOOL CallSetSystemTimeAdjustment(DWORD dwTimeAdjustment);
VOID CallGetSystemTimeAdjustment(VOID); 


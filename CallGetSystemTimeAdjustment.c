#include "includes.h"

VOID CallGetSystemTimeAdjustment(VOID) {
	DWORD dwTimeAdjustment = 0;
	DWORD dwTimeIncrement = 0;
	BOOL bTimeAdjustmentDisabled = 2;

	printf("GetSystemTimeAdjustment() Calling...\n");	
	if (!GetSystemTimeAdjustment(&dwTimeAdjustment, &dwTimeIncrement, &bTimeAdjustmentDisabled)) {
		PrintErrorMessage((__FILE__), "GetSystemTimeAdjustment(&dwTimeAdjustment, &dwTimeIncrement, &bTimeAdjustmentDisabled)", __LINE__);
		exit(1);
	}
		
//	printf("GetSystemTimeAdjustment(%ld, %ld,",dwTimeAdjustment, dwTimeIncrement);
	printf("dwTimeAdjustment: %ld [100-nanosecond unit]\n", dwTimeAdjustment);
	printf("dwTimeIncrement : %ld [100-nanosecond unit]\n", dwTimeIncrement);
	printf("bTimeAdjustmentDisabled : %s \n", bTimeAdjustmentDisabled ? "True (Sync RTC see KB232488)" : "False (Ignore RTC)");
}
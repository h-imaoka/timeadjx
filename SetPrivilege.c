#include "includes.h"


/*
 *2005/02/20: SetPrivilege() is changed from "Enabling and Disabling Privileges in C++"
  http://msdn.microsoft.com/library/en-us/secauthz/security/enabling_and_disabling_privileges_in_c__.asp
 
 *2004/12/18: First implementation: SetPrivilege() comes from "HOWTO: How to Obtain a Handle to Any Process with SeDebugPrivilege"
  http://support.microsoft.com/?scid=kb;en-us;131065
*/

BOOL SetPrivilege(
    HANDLE hToken,          // access token handle
    LPCTSTR lpszPrivilege,  // name of privilege to enable/disable
    BOOL bEnablePrivilege   // to enable or disable privilege
    ) 
{
TOKEN_PRIVILEGES tp;
LUID luid;

if ( !LookupPrivilegeValue( 
        NULL,            // lookup privilege on local system
        lpszPrivilege,   // privilege to lookup 
        &luid ) )        // receives LUID of privilege
{
    printf("LookupPrivilegeValue error: %u\n", GetLastError() ); 
    return FALSE; 
}

tp.PrivilegeCount = 1;
tp.Privileges[0].Luid = luid;
if (bEnablePrivilege)
    tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
else
    tp.Privileges[0].Attributes = 0;

// Enable the privilege or disable all privileges.

if ( !AdjustTokenPrivileges(
       hToken, 
       FALSE, 
       &tp, 
       sizeof(TOKEN_PRIVILEGES), 
       (PTOKEN_PRIVILEGES) NULL, 
       (PDWORD) NULL) )
{ 
      printf("AdjustTokenPrivileges error: %u\n", GetLastError() ); 
      return FALSE; 
} 

return TRUE;
}
#ifdef OLD_SetPrivilege
BOOL SetPrivilege(
    HANDLE hToken,          // token handle
    LPCTSTR Privilege,      // Privilege to enable/disable
    BOOL bEnablePrivilege   // TRUE to enable.  FALSE to disable
    )
{
    TOKEN_PRIVILEGES tp;
    LUID luid;
    TOKEN_PRIVILEGES tpPrevious;
    DWORD cbPrevious=sizeof(TOKEN_PRIVILEGES);

    if(!LookupPrivilegeValue( NULL, Privilege, &luid )) return FALSE;

    // 
    // first pass.  get current privilege setting
    // 
    tp.PrivilegeCount           = 1;
    tp.Privileges[0].Luid       = luid;
    tp.Privileges[0].Attributes = 0;

    AdjustTokenPrivileges(
            hToken,
            FALSE,
            &tp,
            sizeof(TOKEN_PRIVILEGES),
            &tpPrevious,
            &cbPrevious
            );

    if (GetLastError() != ERROR_SUCCESS) return FALSE;

    // 
    // second pass.  set privilege based on previous setting
    // 
    tpPrevious.PrivilegeCount       = 1;
    tpPrevious.Privileges[0].Luid   = luid;

    if(bEnablePrivilege) {
        tpPrevious.Privileges[0].Attributes |= (SE_PRIVILEGE_ENABLED);
    }
    else {
        tpPrevious.Privileges[0].Attributes ^= (SE_PRIVILEGE_ENABLED &
            tpPrevious.Privileges[0].Attributes);
    }

    AdjustTokenPrivileges(
            hToken,
            FALSE,
            &tpPrevious,
            cbPrevious,
            NULL,
            NULL
            );

    if (GetLastError() != ERROR_SUCCESS) return FALSE;

    return TRUE;
}
#endif OLD_SetPrivilege

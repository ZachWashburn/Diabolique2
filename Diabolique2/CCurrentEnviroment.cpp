#include "BaseIncludes.h"
#include "CCurrentEnviroment.h"
#include <sddl.h>

/*
Token Elevation Type: Token elevation is about User Account Control

%%1936  - Type 1 (TokenElevationTypeDefault) 
    is a full token with no privileges removed or groups disabled.  
    A full token is only used if User Account Control is disabled or if the user is the built-in Administrator account or a service account.

%%1937 - Type 2 (TokenElevationTypeFull) 
    is an elevated token with no privileges removed or groups disabled. 
    An elevated token is used when User Account Control is enabled and the user chooses to start the program using Run as administrator.  
    An elevated token is also used when an application is configured to always require administrative privilege or to always require maximum privilege, 
    and the user is a member of the Administrators group.

%%1938 - Type 3 (TokenElevationTypeLimited) 
    is the normal value when UAC is enabled and a user simply starts a program from the Start Menu.  
    It's a limited token with administrative privileges removed and administrative groups disabled. 
    The limited token is used when User Account Control is enabled, 
    the application does not require administrative privilege, 
    and the user does not choose to start the program using Run as administrator.
*/


bool CCurrentEnviroment::FetchUACLevel()
{
	WINDOWS_IMPORT_HIDE(OpenProcessToken, "Advapi32.dll");
    WINDOWS_IMPORT_HIDE(GetTokenInformation, "Advapi32.dll");
    //WINDOWS_IMPORT_HIDE(GetNamedSecurityInfo, "Advapi32.dll");
    
    TOKEN_ELEVATION_TYPE tetElevLvl;
	HANDLE hToken;
	BOOL bRet = _OpenProcessToken(m_CurrentModuleHandle, TOKEN_QUERY, &hToken);

	if (!bRet)
		return false;

    DWORD infoLen;
    bRet = _GetTokenInformation(hToken,
        TokenElevationType,     // type of info to retrieve
        &tetElevLvl,         // receives return value
        sizeof(tetElevLvl),
        &infoLen);              // receives returned length

    if (!bRet)
        return false;

    switch (tetElevLvl)
    {
    case TokenElevationTypeDefault:
    case TokenElevationTypeFull:
        m_UAC = UAC_LEVEL::k_UAC_ADMIN;
        break;
    case TokenElevationTypeLimited:
        m_UAC = UAC_LEVEL::k_UAC_GUEST;
        break;
    }

    infoLen = NULL;
    bRet = _GetTokenInformation(hToken,
        TokenMandatoryPolicy,     // type of info to retrieve
        &m_MICPolicy,         // receives return value
        sizeof(m_MICPolicy),
        &infoLen);

#if 0 // TODO : FETCH DACLs and ACE
    DWORD dwRes = 0;
    PACL pOldDACL = NULL, pNewDACL = NULL;
    PSECURITY_DESCRIPTOR pSD = NULL;
    dwRes = _GetNamedSecurityInfo(pszObjName, ObjectType,
        DACL_SECURITY_INFORMATION,
        NULL, NULL, &pOldDACL, NULL, &pSD)
#endif
    return true;
}


bool CCurrentEnviroment::GetEnv()
{
    WINDOWS_IMPORT_HIDE(GetCurrentProcess, "kernel32.dll");
    WINDOWS_IMPORT_HIDE(GetModuleFileNameA, "Kernel32.dll");

    // Set Up The Basics
    m_CurrentModuleHandle = _GetCurrentProcess();
    _GetModuleFileNameA(NULL, m_ExecutablePath, MAX_PATH);

    // Please tell us we are an admin....
    FetchUACLevel();



    return true;
}
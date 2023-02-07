#ifndef _H_CCURRENTENVIROMENT
#define _H_CCURRENTENVIROMENT

#include "BaseIncludes.h"

#ifdef _MSC_VER
#pragma once
#endif

enum class UAC_LEVEL
{
	k_UAC_INVALID = -1,
	k_UAC_GUEST = 1,
	k_UAC_LINKED_ADMIN = 2,
	k_UAC_ADMIN = 3
};

class CCurrentEnviroment
{
public:

	virtual bool GetEnv();

	virtual bool IsAdminElevated()
	{
		return m_UAC == UAC_LEVEL::k_UAC_ADMIN;
	}

	const char* GetExecutablePath(CHAR szPath[MAX_PATH] = nullptr)
	{
		if (!szPath)
			return m_ExecutablePath;


#ifdef _WIN64
		memcpy(szPath, m_ExecutablePath, sizeof(m_ExecutablePath));
#else
		unsigned int usDataInSize = sizeof(m_ExecutablePath);
		CHAR* pDataIn = m_ExecutablePath;
		_asm {
			mov ecx, usDataInSize
			mov edi, szPath
			mov esi, pDataIn
			cld // set df flag so movsb increments pointers (DF = 0)
			rep movsb // copy data 
		}
#endif
		return szPath;
	}

protected:
	virtual bool FetchUACLevel();
private:
	UAC_LEVEL m_UAC = UAC_LEVEL::k_UAC_INVALID;
	HANDLE m_CurrentModuleHandle = INVALID_HANDLE_VALUE;
	CHAR m_ExecutablePath[MAX_PATH];
	TOKEN_MANDATORY_POLICY m_MICPolicy;
};

inline CCurrentEnviroment* g_pEnv = nullptr;

#endif // _H_CCURRENTENVIROMENT
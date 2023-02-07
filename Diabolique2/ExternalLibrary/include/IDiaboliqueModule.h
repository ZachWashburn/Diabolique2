/*
	Wrapper for any Loaded Module that has data to be sent to/from The Diabolique Server
*/
#ifndef _H_IDIABOLIQUEMODULE
#define _H_IDIABOLIQUEMODULE

#ifdef _MSC_VER
#pragma once
#endif

#include <BaseIncludes.h>
#include <IDataTransfer.h>

// Default IDiaboliqueModule class
ABSTRACT_CLASS IDiaboliqueModule : public IDataTransfer
{
public:
	virtual bool Initialize(void* pArgs, size_t nDataSize) = 0;
	virtual bool ShutDown() = 0;
	virtual bool FreeLibrary() = 0;
	virtual bool SendData(void* pData, size_t nDataSize, size_t& nDataSent) = 0;
	virtual bool RecvData(void* pBuffer, size_t nBufferSize, size_t& nDataRecieved) = 0;
	virtual bool IsConnectionAlive() = 0;
};


#if defined(SERVER) || defined(_DEBUG) || defined(SERVER_CLIENT)

// Modules Should Ideally be written to provide CLI through stdin/stdout
// The initialized using the CDiaboliqueMemDLL or CDiaboliqueMemClrDLL or CDiaboliqueMemProcessController
// classes. However Adding Additional Functionality, these must be populated in the g_ModulePreProcessors std::map

// Passthrough for user text inputted into the console
// return false for no allowing of data
typedef bool(__stdcall* fnUserPassthroughFormatter_t)(std::string* input);

// Passthrough for user text to generate initialization dara
// return false for an empty message
typedef bool(__stdcall* fnGenerateInitializationData_t)(std::string input, void** ppMemory, size_t& nDataSize);

struct server_module_preprocessors_t
{
	fnUserPassthroughFormatter_t m_UserPassthrough;
	fnGenerateInitializationData_t m_GenerateInitializationData;
	int m_nType = -1;
	std::string m_Name;
};

inline std::map<int, server_module_preprocessors_t> g_ModulePreProcessors;


inline void AddNewModulePreProcessor(int nType, server_module_preprocessors_t processor)
{
	g_ModulePreProcessors[nType] = processor;
}

inline bool GetPreProcessor(int nType, server_module_preprocessors_t& processor)
{
	if (g_ModulePreProcessors.find(nType) == g_ModulePreProcessors.end())
		return false;

	processor = g_ModulePreProcessors[nType];
	return true;
}


ABSTRACT_CLASS IDiaboliqueModuleServerDefaultInitializer
{
public:
	void _INIT_AddModulePreProcessor(fnUserPassthroughFormatter_t passthrough, fnGenerateInitializationData_t init, int nType, std::string name)
	{
		server_module_preprocessors_t processor;
		processor.m_UserPassthrough = passthrough;
		processor.m_GenerateInitializationData = init;
		processor.m_Name = name;
		AddNewModulePreProcessor(nType, processor);
	}
};


#endif // #if defined(SERVER) || defined(_DEBUG) || defined(SERVER_CLIENT)
#endif // _H_IDIABOLIQUEMODULE
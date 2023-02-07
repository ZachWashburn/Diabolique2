/*

	Any Method Of Data Transfer between to seperate entities, should inherit from this class.
This allows hot swapping methods of data transfer, as well as more generalized code. 


*/
#ifndef _H_IDATATRANSFER
#define _H_IDATATRANSFER

#ifdef _MSC_VER
#pragma once
#endif

#include <BaseIncludes.h>
#include <string>

ABSTRACT_CLASS IDataTransfer
{
public:
	virtual bool Initialize(void* pArgs, size_t nDataSize) = 0;
	virtual bool ShutDown() = 0;
	virtual bool SendData(void* pData, size_t nDataSize, size_t& nDataSent) = 0;
	virtual bool RecvData(void* pBuffer, size_t nBufferSize, size_t& nDataRecieved) = 0;
	virtual bool IsConnectionAlive() = 0;
#if defined(SERVER) || defined(_DEBUG) || defined(SERVER_CLIENT)
	virtual std::string GetConnectionName() = 0;
#endif
};

#endif // _H_IDATATRANSFER
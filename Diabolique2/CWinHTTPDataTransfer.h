#ifndef _C_WINHTTPDATATRANSFER
#define _C_WINHTTPDATATRANSFER

#ifdef _MSC_VER
#pragma once
#endif

#include "BaseIncludes.h"
#include "IDataTransfer.h"


/* Actually Uses WinINET Rather Than WinHTTP Directly */



class CWinHTTPDataTransfer : public IDataTransfer
{
public:

#pragma pack(push, 1)
	struct cwinhttpdata_initalization_data_t
	{
		char m_szURL[MAX_PATH];
		// WindowsImportHide::_extract_function_arguements<
		//	decltype(WinHttpOpen)
		// >::function_params_t WinHttpOpenParams;


	};
#pragma pack(pop)

	virtual bool Initialize(void* pArgs, size_t nDataSize) = 0;
	virtual bool ShutDown() = 0;
	virtual bool SendData(void* pData, size_t nDataSize, size_t& nDataSent) = 0;
	virtual bool RecvData(void* pBuffer, size_t nBufferSize, size_t& nDataRecieved) = 0;
	virtual bool IsConnectionAlive() = 0;
#if defined(SERVER) || defined(_DEBUG) || defined(SERVER_CLIENT)
	virtual std::string GetConnectionName() = 0;
#endif



protected:


private:


};




#endif // _C_WINHTTPDATATRANSFER

#include "CDiaboliqueServer.h"
#ifdef _H_CDIABOLIQUESERVER
#include <filesystem>


void CDiaboliqueServer::FileSegmentHandle(
	CDiaboliqueServerClient* pClient,
	void* pData,
	size_t nDataSize
){

	file_transfer_segment seg;

	if (!seg.ParseFromArray(pData, nDataSize))
		return;


	m_Files.HandleFileMessage(
		seg,
		std::filesystem::path(g_pEnv->GetExecutablePath()).remove_filename().string()
		+ std::to_string(pClient->GetClientID()) + "\\"
	);
}


#endif // _H_CDIABOLIQUESERVER
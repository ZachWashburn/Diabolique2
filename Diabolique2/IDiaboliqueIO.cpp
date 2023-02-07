#include "IDiaboliqueIO.h"
#include <ProcessController/CDiabolqiueProcess.h>
#include <SocketPassThrough/CDiaSocketPassthrough.h>
#include <CPowershellPassthrough.h>

IDiaboliqueIO::IDiaboliqueIO()
{

	m_Creators[DiaboliqueModuleType_t::k_dmtProcessController] = &CreateProcessController;
	m_Creators[DiaboliqueModuleType_t::k_dmtSocketPassthrough] = &CreateSocketPassthrough;
	m_Creators[DiaboliqueModuleType_t::k_dmtPowershellPassthrough] = &CreatePowershellPassthrough;


}

bool IDiaboliqueIO::InitializeModule(int nModule, void* pBuffer, size_t nDataSize)
{
	IDataTransfer* pTransfer = m_Transfer[nModule];

	if (!pTransfer || (nModule == -1))
		return false;

	m_nCurrentModule = nModule;

	pTransfer->Initialize(pBuffer, nDataSize);
}

bool IDiaboliqueIO::HandleData(int nModule, void* pData, size_t nDataSize)
{

	m_nCurrentModule = nModule;
	
	IDataTransfer* pTransfer = m_Transfer[nModule];

	if (!pTransfer)
		return false;

	{
		size_t nTotalDataSent = 0;
		// add a timeout!
		while (nTotalDataSent < nDataSize)
		{
			size_t nDataSent = 0;
			pTransfer->SendData((char*)pData + nTotalDataSent, nDataSize - nTotalDataSent, nDataSent);
			nTotalDataSent += nDataSent;
		}
	}

	return true;
}

bool IDiaboliqueIO::RecieveDataFromModule(int nModule, void* pBuffer, size_t nDataSize, size_t& nDataRecieved)
{
	if (m_Transfer.find(nModule) == m_Transfer.end())
		return false;


	IDataTransfer* pTransfer = m_Transfer[nModule];

	if (!pTransfer)
		return false;

	if (!pTransfer->IsConnectionAlive())
	{
		delete m_Transfer[nModule];
		m_Transfer.erase(nModule);
		return false;
	}

	return pTransfer->RecvData(pBuffer, nDataSize, std::ref(nDataRecieved));

}


bool IDiaboliqueIO::RecieveDataFromCurrentModule(int& nModule, void* pBuffer, size_t nDataSize, size_t& nDataRecieved)
{
	nModule = m_nCurrentModule;
	return RecieveDataFromModule(nModule, pBuffer, nDataSize, std::ref(nDataRecieved));
}


int IDiaboliqueIO::CreateNewModule(DiaboliqueModuleType_t nType)
{

	if (m_Creators[nType] == nullptr)
		return -1;

	unsigned int i = 0; 
	for (auto it = m_Transfer.cbegin(), end = m_Transfer.cend();
		it != end && i == it->first; ++it, ++i)
	{
	}

	m_Transfer[i] = m_Creators[nType]();

	return i;
}
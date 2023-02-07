#include <CTransferFileTask.h>
#include <IDiabolique.h>

void CTransferFileTask::RunInternal()
{
	if (IsDone())
		return;

	std::string file_name = std::filesystem::path::path(pFile->GetFileName()).filename().string();
	//int nFilePos = 0;
	//while ((file.GetFileSize() > nFilePos) && file.IsOpen())
	//{
		// TODO : Task this
	file_transfer_segment seg;
	seg.set_name(file_name);
	size_t nBytesRead = 0;
	seg.set_data(pFile->ReadFile(FILESEGMENTSIZE, &nBytesRead, m_nFilePos));
	seg.set_file_size(pFile->GetFileSize());
	seg.set_pos(m_nFilePos);
	m_nFilePos += nBytesRead;
	//SendMessageToTransfer(diabolique_message_type_t::k_dmCTSFileSegment, &seg);
	//}

	std::string serialized;
	seg.SerializeToString(&serialized);

	m_TaskDataLock.lock();
	m_TaskData.push_front(std::pair<diabolique_message_type_t, std::string>(diabolique_message_type_t::k_dmCTSFileSegment, serialized));
	m_TaskDataLock.unlock();
}



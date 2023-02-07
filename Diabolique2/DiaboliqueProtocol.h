#ifndef _H_DIABOLIQUEPROTOCOL
#define _H_DIABOLIQUEPROTOCOL

#ifdef _MSC_VER
#pragma once
#endif

// snake case for protocol work
#include "IDiaboliqueIO.h"

#pragma pack(push, 1)
#define DIABOLIQUEPACKETCHECKSUM "XMU\0"
#define DIABOLIQUENETWORKBUFFERSIZE 8192
#define DIABOLIQUEMAXNETMESSAGESIZE (DIABOLIQUENETWORKBUFFERSIZE * 1000)
#define DIABOLIQUE_NET_COMPRESSION_ENABLED

// keep this since protobuf enum forces generation of enum type name strings...
enum class diabolique_message_type_t {
	k_dmATAINVALID = -1,
	k_dmSTCCreateModule = 0,
	k_dmSTCInitializeModule = 1,
	k_dmCTSModuleCreationNotify = 2,
	k_dmATAModuleData = 3,
	k_dmCTSScreenCap = 4,
	k_dmSTCScreenCapStartup = 5,
	k_dmCTSTaskStartup = 6,
	k_dmCTSFileSegment = 7,
	k_dmSTCFileSegmentServ = 8,
	k_dmSTCRequestFile = 9,
};



struct message_header_t
{
	char m_CheckSum[sizeof(DIABOLIQUEPACKETCHECKSUM)] = DIABOLIQUEPACKETCHECKSUM;
	diabolique_message_type_t m_nType = diabolique_message_type_t::k_dmATAINVALID;
#ifdef DIABOLIQUE_NET_ENCRYPTED
	bool m_bEncrypted;
#endif
#ifdef DIABOLIQUE_NET_COMPRESSION_ENABLED
	//bool m_bCompressed;
	__int32 m_nUncompressedSize = 0;
#endif
	__int32 m_nTotalSize = 0;
};

#if 0 // old style before protobufs

struct diabolique_default_module_message_t
{
	int m_nModule = -1;
	size_t m_nDataPacketSize = -1;
};

struct message_create_module_t
{
	DiaboliqueModuleType_t m_nType;
};

struct message_notify_module_list_t
{
	__int32 m_nModuleCount;
};


struct message_initialize_module_t
{
	int m_nModule;
};

struct message_module_creation_result_t
{
	__int32 m_nIndex = -1;
	DiaboliqueModuleType_t m_nType;
	bool m_bFailure = false;
};
#endif



#pragma pack(pop)
#endif // _H_DIABOLIQUEPROTOCOL

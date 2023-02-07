#ifndef _H_BASEINCLUDES
#define _H_BASEINCLUDES

#ifdef _MSC_VER
#pragma once
#endif

#include "PREPROCESSOR.h"



#include <string>
#include <vector>
#include <deque>
#include <map>
#include <thread>
#include <mutex>
#include <WindowsIncludes.h>
#include <WindowsImportHide/WindowsImportHide.h>
#include <FastLZ/fastlz.h>
#include <stddef.h>


// Util Classes
#include <CSimpleThreadPool.h>
//#include <CAsyncDataQueueBuffer.h>
#include <CThreadPauser.h>
//#include <aes_utils.h>
#include <PasteBin.h>

// compression
#include <smallz4/smallz4.h>
#include <miniz.h>

// Encryption, SSL, RSA
#include <AES/AES.h>


#include <fstream>
#include <filesystem>

#include <diabolique_system_messages.pb.h>
#include <diabolique_module_messages.pb.h>

#include <google/protobuf/message.h>




inline CSimpleThreadPool<8>* g_pThreadPool = nullptr;

void UnGrabMutex();
bool GrabMutex();

inline const char* szDecKey =
"\x75\x38\x78\x2F\x41\x3F\x44\x2A\x47\x2D\x4B\x61\x50\x64\x53\x67\x56\x6B\x59\x70\x33\x73\x36\x76\x39\x79\x24\x42\x26\x45\x29\x48";

#endif




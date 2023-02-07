#ifndef _H_AESUTILS
#define _H_AESUTILS

#ifdef _MSC_VER
#pragma once
#endif


#include <AES/AES.h>


void generate_random_buffer(unsigned char* pBuffer, size_t nBufferSize);
void* aes_encrypt_buffer(unsigned char* pData, size_t& nDataSize, unsigned char* pKey, AESKeyLength keylen);
void* aes_decrypt_buffer(unsigned char* pData, size_t nDataSize, unsigned char* pKey, size_t& nDataOutSize, AESKeyLength keylen);

#endif
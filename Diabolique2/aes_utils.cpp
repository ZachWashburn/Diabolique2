#include <aes_utils.h>

// Yes its not super secure. But really we don't need it to be
// we just need to defeat wireshark tbh

struct encrypted_buffer_header_t
{
	unsigned char iv[4 * 4 * sizeof(unsigned char)];
	unsigned int size;
};


void generate_random_buffer(unsigned char* pBuffer, size_t nBufferSize)
{
	// rand will never go over RAND_MAX
	// #define RAND_MAX 0x7fff
	// so we only take the first byte!
	// Remember conikers bad ip gen?
	for (int i = 0; i < nBufferSize; i++)
	{
		pBuffer[i] = (unsigned char)(rand() & 0x000000FF);
	}
}

// must call free on buffer returned!
void* aes_encrypt_buffer(unsigned char* pData, size_t& nDataSize, unsigned char* pKey, AESKeyLength keylen)
{
	AES aes(keylen);

	encrypted_buffer_header_t Head;

	generate_random_buffer(Head.iv, sizeof(Head.iv));

	int nLeftOver = nDataSize % aes.BlockBytesLen();
	unsigned char* _pData = nullptr;
	if(!nLeftOver) // quick hit
		_pData = aes.EncryptCBC(pData, nDataSize, pKey, Head.iv);
	else
	{
		int nSizeSav = nDataSize;
		nDataSize = nDataSize + (aes.BlockBytesLen() - nLeftOver);
		void* pData2 = malloc(nDataSize);
		memset(pData2, 0, nDataSize);
		memcpy(pData2, pData, nSizeSav);
		_pData = aes.EncryptCBC((unsigned char*)pData2, nDataSize, pKey, Head.iv);
	}

	void* pBuffer = malloc(sizeof(encrypted_buffer_header_t) + nDataSize);

	if (!pBuffer)
	{
		delete[] _pData;
		return nullptr;
	}

	Head.size = nDataSize + sizeof(encrypted_buffer_header_t);
	memcpy((char*)pBuffer + sizeof(encrypted_buffer_header_t), _pData, nDataSize);
	memcpy(pBuffer, &Head, sizeof(encrypted_buffer_header_t));
	delete[] _pData;

	nDataSize += sizeof(encrypted_buffer_header_t);

	return pBuffer;
}

void* aes_decrypt_buffer(unsigned char* pData, size_t nDataSize, unsigned char* pKey, size_t& nDataOutSize, AESKeyLength keylen)
{
	AES aes(keylen);
	encrypted_buffer_header_t* head = reinterpret_cast<encrypted_buffer_header_t*>(pData);

	if (nDataSize == 0)
		nDataSize = head->size;

	nDataOutSize = nDataSize - sizeof(encrypted_buffer_header_t);
	void* pBuffer = malloc(nDataOutSize);

	if (!pBuffer)
		return nullptr;

	unsigned char* pRawEncData = (unsigned char*)((char*)pData + sizeof(encrypted_buffer_header_t));
	

	void* _pData = aes.DecryptCBC(pRawEncData, nDataOutSize, pKey, head->iv);

	memcpy(pBuffer, _pData, nDataOutSize);

	delete[] _pData;

	return pBuffer;
}

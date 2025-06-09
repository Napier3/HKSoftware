#ifndef _SttBufferZipApi_h__
#define _SttBufferZipApi_h__



//zip buffer
//     4byte              4byte                   4byte                zip data length
//  EA15EA15     zip data src length     zip data length     ------------------------

#define STT_BUFF_ZIP_HEAD_LEN  12

inline void stt_zip_buf_init_head(BYTE *pBuffer)
{
	*pBuffer       = 0XEA;
	*(pBuffer+1) = 0X15;
	*(pBuffer+2) = 0XEA;
	*(pBuffer+3) = 0X15;
}

inline void stt_zip_buf_set_short(BYTE *pBuffer, short nValue)
{
	*pBuffer       = (BYTE) ((nValue >> 8) & 0xFF);
	*(pBuffer+1) = (BYTE) ((nValue) & 0xFF);
}

inline void stt_zip_buf_get_short(BYTE *pBuffer, short &nValue)
{
	nValue += (*(pBuffer) << 8 );
	nValue += (*(pBuffer+1));
}

inline void stt_zip_buf_set_long(BYTE *pBuffer, long nValue)
{
	*pBuffer       = (BYTE) ((nValue >> 24) & 0xFF);
	*(pBuffer+1) = (BYTE) ((nValue >> 16) & 0xFF);
	*(pBuffer+2) = (BYTE) ((nValue >> 8)  & 0xFF);
	*(pBuffer+3) = (BYTE) (nValue            & 0xFF);
}

inline void stt_zip_buf_get_long(BYTE *pBuffer, long &nValue)
{
	nValue   = (*pBuffer        << 24);
	nValue += (*(pBuffer+1) << 16);
	nValue += (*(pBuffer+2) << 8 );
	nValue += (*(pBuffer+3));
}

inline void stt_zip_buf_set_len(BYTE *pBuffer, long nSrcLen,   long nZipLen)
{
	stt_zip_buf_set_long(pBuffer+4, nSrcLen);
	stt_zip_buf_set_long(pBuffer+8, nZipLen);
}

inline void stt_zip_buf_get_len(BYTE *pBuffer, long &nSrcLen, long &nZipLen)
{
	stt_zip_buf_get_long(pBuffer+4, nSrcLen);
	stt_zip_buf_get_long(pBuffer+8, nZipLen);
}

inline long stt_zip_buf_get_len_zip(BYTE *pBuffer)
{
	long nZipLen = 0;
	stt_zip_buf_get_long(pBuffer+8, nZipLen);
	return nZipLen;
}

inline long stt_zip_buf_get_len_src(BYTE *pBuffer)
{
	long nSrcLen = 0;
	stt_zip_buf_get_long(pBuffer+4, nSrcLen);
	return nSrcLen;
}

inline bool stt_zip_buf_match_head(BYTE *pBuffer)
{
	return ( (*pBuffer == 0XEA)  &&
	           (*(pBuffer+1) = 0X15) &&
	           (*(pBuffer+2) = 0XEA) &&
	           (*(pBuffer+3) = 0X15 ) );
}

inline BYTE* stt_zip_buf_get_zip_begin(BYTE *pBuffer)
{
	return pBuffer + STT_BUFF_ZIP_HEAD_LEN;
}

void stt_zip_buf_get_zip_begin(BYTE* &pZipRcdBuf, BYTE *pEnd);

BOOL stt_buf_zip_init();
BOOL stt_buf_zip(BYTE *pSrcBuf, long nSrcLen, BYTE *pDestBuf, long &nDestLen);
BOOL stt_buf_unzip(BYTE *pSrcBuf, long nSrcLen, BYTE *pDestBuf, long &nDestLen);

void stt_zip_file(const char *strSrcFile);

#endif


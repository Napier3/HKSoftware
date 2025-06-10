#include "stdafx.h"
#include "SttRcdSocketBufferZip.h"

#include <stdio.h>
#include <stdlib.h>

#include "../../../Module/minilzo-2.10/minilzo.h"
#include "../../../Module/Log/LogPrint.h"

#include "../XLangResource_Native.h"

//#include "../../../Module/SmartCap/61850Cap/CapGlobalDef.h"
#define STT_AT02_FIXED_HEAD_DWORD			0x64056405
#define STT_AT02_FIXED_HEAD			0x05640564
#define STT_AT02_FIXED_HEAD_LEN		         4

//2020-07-17  lijunqing  不管是客户端还是服务端，都会用着这个文件，所以定义于此
//缺省为压缩
long g_nSttRcdSocketUseZip = 1;
long g_nSttRcdZipHasInit = 0;

#define HEAP_ALLOC(var,size) \
	lzo_align_t __LZO_MMODEL var [ ((size) + (sizeof(lzo_align_t) - 1)) / sizeof(lzo_align_t) ]

static HEAP_ALLOC(wrkmem, LZO1X_1_MEM_COMPRESS);



void stt_rcd_zip_buf_get_zip_begin(BYTE* &pZipRcdBuf, BYTE *pEnd)
{
	while (pZipRcdBuf < pEnd)
	{
		if (stt_rcd_zip_buf_match_head(pZipRcdBuf))
		{
			break;
		}

		pZipRcdBuf++;
	}
}

BOOL stt_rcd_buf_zip_init()
{
	if (g_nSttRcdZipHasInit)
	{
		return TRUE;
	}

	if (lzo_init() == LZO_E_OK)
	{
		g_nSttRcdZipHasInit = 1;
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

BOOL stt_rcd_buf_zip(BYTE *pSrcBuf, long nSrcLen, BYTE *pDestBuf, long &nDestLen)
{
	lzo_uint nZipLen = 0;
	int r = lzo1x_1_compress((BYTE*)pSrcBuf,nSrcLen
		,stt_rcd_zip_buf_get_zip_begin(pDestBuf), &nZipLen, wrkmem);
	stt_rcd_zip_buf_init_head(pDestBuf);
	stt_rcd_zip_buf_set_len(pDestBuf, nSrcLen, nZipLen);
	nDestLen = nZipLen + STT_RCD_BUFF_ZIP_HEAD_LEN;

#ifndef _no_use_CLogPrint
	if (r != LZO_E_OK)
	{
		/* this should NEVER happen */
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, "internal error - compression failed: %d", r);
	}
#endif

	return (r == LZO_E_OK);
}

BOOL stt_rcd_buf_unzip(BYTE *pSrcBuf, long nSrcLen, BYTE *pDestBuf, long &nDestLen)
{
	long nZipLen = 0;
	lzo_uint nNewLen = 0;
	stt_rcd_zip_buf_get_len(pSrcBuf, nSrcLen, nZipLen);

	int r = lzo1x_decompress(stt_rcd_zip_buf_get_zip_begin(pSrcBuf), nZipLen, pDestBuf ,&nNewLen,NULL);

	nDestLen = nNewLen;

	return (r == LZO_E_OK && nNewLen == nSrcLen);
}

void stt_rcd_zip_file(const char *strSrcFile)
{
	if (!stt_rcd_buf_zip_init())
	{
		return;
	}

	long nLen = strlen(strSrcFile);
	char pszZipFile[256];
	strcpy(pszZipFile, strSrcFile);
	strcat(pszZipFile, "zp");

	FILE *pFileSrc = fopen(strSrcFile, "r+b");

	if (pFileSrc == NULL)
	{
		return;
	}

	FILE *pFileZip = fopen(pszZipFile, "w+b");

	if (pFileZip == NULL)
	{
		fclose(pFileSrc);
		return;
	}

	BYTE pRread[RCD_BUFFER_MAX_LEN];
	BYTE pZip[OUT_RCD_BUFFER_MAX_LEN];
	long nZipLen = 0;
	size_t szRead = 0;

	while (!feof(pFileSrc))
	{
		szRead = fread(pRread, sizeof(BYTE), RCD_BUFFER_MAX_LEN, pFileSrc);

		if (szRead <= 0)
		{
			break;
		}

		if (stt_rcd_buf_zip(pRread, szRead, pZip, nZipLen))
		{
			fwrite(pZip, sizeof(BYTE), nZipLen, pFileZip);
		}
	}

	fclose(pFileSrc);
	fclose(pFileZip);
}

void stt_rcd_unzip_file(const char *strSrcFile,const char *pszUnZipFile)
{
	if (!stt_rcd_buf_zip_init())
	{
		return;
	}

	FILE *pFileSrc = fopen(strSrcFile, "r+b");

	if (pFileSrc == NULL)
	{
		return;
	}

	FILE *pFileUnzip = fopen(pszUnZipFile, "w+b");

	if (pFileUnzip == NULL)
	{
		fclose(pFileSrc);
		return;
	}

	BYTE pszReadDatas[RCD_BUFFER_MAX_LEN*2];
	BYTE pszMemCopyDats[RCD_BUFFER_MAX_LEN];
	BYTE pzsUnZip_Out[OUT_RCD_BUFFER_MAX_LEN];
	size_t uReadLenth = 0;

	BYTE *pCurrBytePos = NULL;
	BYTE *pEndBytePos = NULL;
	BYTE *pBackBytePos = NULL;
	long nZipLen = 0;
	long nCurrRcdRcvLen = 0;

	while (!feof(pFileSrc))
	{
		uReadLenth = fread(pszReadDatas + nCurrRcdRcvLen, sizeof(BYTE), RCD_BUFFER_MAX_LEN, pFileSrc);

		if (uReadLenth <= 0)
		{
			break;
		}

		pCurrBytePos = pszReadDatas;
		pEndBytePos = pszReadDatas +nCurrRcdRcvLen + uReadLenth;
		pBackBytePos = NULL;

		while (TRUE)
		{
			pBackBytePos = pCurrBytePos;
			stt_rcd_zip_buf_get_zip_begin(pCurrBytePos, pEndBytePos);  //跳转到正确的位置

			if (pCurrBytePos != pBackBytePos)
			{
				CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Package Loss Len = %d"), pCurrBytePos - pBackBytePos);
			}

			if (pEndBytePos - pCurrBytePos >= STT_RCD_BUFF_ZIP_HEAD_LEN)
			{//长度足够
				nZipLen = stt_rcd_zip_buf_get_len_zip(pCurrBytePos);

				if (nZipLen <= pEndBytePos - pCurrBytePos - STT_RCD_BUFF_ZIP_HEAD_LEN)
				{
					long nSrcLen = 0, nDataLen = 0;

					if (stt_rcd_buf_unzip(pCurrBytePos, nSrcLen, pzsUnZip_Out, nDataLen))
					{
						fwrite(pzsUnZip_Out, sizeof(BYTE), nDataLen, pFileUnzip);
					}
					else
					{
#ifdef NOT_USE_XLANGUAGE
						CLogPrint::LogString(XLOGLEVEL_ERROR,_T("stt_rcd_unzip_file解压缩出错"));
#else
						CLogPrint::LogFormatString(XLOGLEVEL_ERROR,/*_T("stt_rcd_unzip_file解压缩出错.")*/g_sLangTxt_Native_UnzipError.GetString());
#endif
					}

//					FireRcdBufRcvMsg_Zip(pCurrBytePos);
					pCurrBytePos += STT_RCD_BUFF_ZIP_HEAD_LEN + nZipLen;
					continue;
				}
				else
				{
					if (pszReadDatas != pCurrBytePos)
					{
						nCurrRcdRcvLen = pEndBytePos - pCurrBytePos;
						memcpy(pszMemCopyDats,pCurrBytePos, nCurrRcdRcvLen);
						memcpy(pszReadDatas,pszMemCopyDats,nCurrRcdRcvLen);
						//memcpy(pszReadDatas, pCurrBytePos, pEndBytePos - pCurrBytePos);
					}

					break;
				}
			}
			else
			{
				if (pCurrBytePos != pszReadDatas)
				{
					nCurrRcdRcvLen = pEndBytePos - pCurrBytePos;
					memcpy(pszMemCopyDats,pCurrBytePos, nCurrRcdRcvLen);
					memcpy(pszReadDatas,pszMemCopyDats,nCurrRcdRcvLen);
					//memcpy(pszReadDatas, pCurrBytePos,nCurrRcdRcvLen);
					break;
				}
			}
		}

	}

	fclose(pFileSrc);
	fclose(pFileUnzip);
}


#include "stdafx.h"
#include "SttRcdSocketBufferZip.h"

#include <stdio.h>
#include <stdlib.h>

#include "../../../Module/minilzo-2.10/minilzo.h"
#include "../../../Module/Log/LogPrint.h"

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


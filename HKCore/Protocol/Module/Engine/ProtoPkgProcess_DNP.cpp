#include "StdAfx.h"
#include "ProtoPkgProcess_DNP.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

unsigned short dnp_16_crc(unsigned char *ptr, int len)
{
	unsigned int i;
	unsigned short crc = 0x0000;

	while(len--)
	{
		crc ^= *ptr++;
		for (i = 0; i < 8; ++i)
		{
			if (crc & 1)
				crc = (crc >> 1) ^ 0xA6BC;
			else
				crc = (crc >> 1);
		}
	}

	return ~crc;
}

unsigned short dnp_16_crc(unsigned char *ptr, int len, unsigned char *ptr_crc)
{
	unsigned short crc = dnp_16_crc(ptr, len);

	*((unsigned short *)ptr_crc) = crc;
	
	return crc;
}

/*
    head  len fn adr-d  adr-s  crc
>  05 64 05 c0 04 2b 0a 00 a0 95
<  05 64 05 00 0a 00 04 2b 3f ed
>  05 64 14 c4 04 2b 0a 00 9e d4 c0 c0 01 3c 01 06 3c 02 06 3c 03 06 3c 04 06 9c 09
<  05 64 4f 44 0a 00 04 2b 8b 43 c3 e0 81 90 00 01 01 01 00 00 3f 00 00 0a 00 00 8d 8b 00 00 00 00 1e 04 01 00 00 0f 00 00 00 00 00 00 bb 33 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 ff ff 00 00 00 00 00 ff 7f 00 00 10 4b 0a 02 01 00 00 87 d7 07 00 01 01 01 01 01 01 01 01 f2 b4
*/

void dnp_buf_copy(unsigned char **ppSrc, unsigned char **ppDest, long &nRetLen, long nLen, bool bCopy)
{
	if (bCopy)
	{
		memcpy(*ppDest, *ppSrc, nLen);
	}

	*ppSrc += nLen + 2;
	nRetLen -= 2;
	*ppDest += nLen;
}

bool CProtoPkgProcess_DNP::PrcssAfterRcv(unsigned char *pBuffer, long &nBufLen)
{
	long nPkgLen = 0;
	long nRetLen = nBufLen;
	long nLeftLen = nBufLen;
	unsigned char *pSrcTail = pBuffer + nBufLen;
	unsigned char *pSrc = pBuffer;
	unsigned char *pDest = pBuffer;
	
	if (! GetPkgLen(pSrc, nLeftLen, nPkgLen))
	{
		return false;
	}

    while (true)
    {
//prcss_begin:
        if (! GetPkgLen(pSrc, nLeftLen, nPkgLen))
        {
            //goto prcss_end;
            nBufLen = nRetLen;

            if (nLeftLen > 0)
            {
                memcpy(pDest, pSrc, nLeftLen);
            }

            return true;
        }

        unsigned char *pSrcBack = pSrc;
        //head
        dnp_buf_copy(&pSrc, &pDest, nRetLen, 8, pSrc != pBuffer);

        if (nPkgLen == 5)
        {//没有报文数据，则继续
            //goto prcss_begin;
            continue;
        }

        nPkgLen -= 5;

        while (nPkgLen > 0)
        {
            if (nPkgLen >16)
            {
                dnp_buf_copy(&pSrc, &pDest, nRetLen, 16, true);
                nPkgLen -= 16;
            }
            else
            {
                dnp_buf_copy(&pSrc, &pDest, nRetLen, nPkgLen, true);
                nPkgLen = 0;
            }
        }

        nLeftLen -= pSrc - pSrcBack;

        if (nLeftLen > 0)
        {
            //goto prcss_begin;
            continue;
        }

    }
//prcss_end:

	nBufLen = nRetLen;

	if (nLeftLen > 0)
	{
		memcpy(pDest, pSrc, nLeftLen);
	}

	return true;
}

void dnp_buf_copy_write(unsigned char **ppSrc, unsigned char **ppDest, long nLen)
{
	memcpy(*ppDest, *ppSrc, nLen);
	dnp_16_crc(*ppDest, nLen, *ppDest + nLen);
	*ppSrc += nLen;
	*ppDest += nLen + 2;
}

bool CProtoPkgProcess_DNP::PrcssAfterProduce(unsigned char *pBuffer, long &nBufLen)
{
	//没有数据
	if (nBufLen == 8)
	{
		dnp_16_crc(pBuffer, nBufLen, pBuffer + 8);
		nBufLen += 2;
		return true;
	}

	long nDataLen = nBufLen - 8; //head
	long nCount = nDataLen / 16;
	long nLastLen = nDataLen - nCount * 16;

	if (nLastLen > 0)
	{
		nCount++;
	}

	long nNewBufferLen = nBufLen + nCount*2 + 2;  //data-crc:nCount*2    head-crc:2
    unsigned char *pNewBuffer = new unsigned char[nNewBufferLen+20];
    memset(pNewBuffer, 0, nNewBufferLen+20);
	unsigned char *pDest = pNewBuffer;
	unsigned char *pSrc = pBuffer;

	//copy head
	dnp_buf_copy_write(&pSrc, &pDest, 8);

	//copy-data
	for (long k=0; k<nCount; k++)
	{
		if (nDataLen > 16)
		{
			dnp_buf_copy_write(&pSrc, &pDest, 16);
			nDataLen -= 16;
		}
		else
		{
			dnp_buf_copy_write(&pSrc, &pDest, nDataLen);
		}
	}

	nBufLen = nNewBufferLen;
	memcpy(pBuffer, pNewBuffer, nNewBufferLen);
    delete pNewBuffer;

	return true;
}

bool CProtoPkgProcess_DNP::IsWholePkg(unsigned char *pBuffer, long &nBufLen)
{
	if (pBuffer[0] != 0x05 || pBuffer[1] != 0x64)
	{
		return false;
	}

	long nPkgLen = pBuffer[2];
	long nPkgDataLen = nPkgLen - 5;
	long nDataCrcCount = nPkgDataLen / 16; //pkg data : 

	if (nDataCrcCount * 16 < nPkgDataLen)
	{
		nDataCrcCount++;
	}

	long nTotalLen = (nDataCrcCount + 1) * 2;  //all CRC Len
	nTotalLen += 8;  //05 64 + len + head data

	if (nPkgLen < nTotalLen )  //head 2 + len 1 + crc 2
	{
		return false;
	}

	return true;
}

bool CProtoPkgProcess_DNP::GetPkgLen(unsigned char *pBuffer, long &nBufLen, long &nPkgLen)
{
	if (!IsWholePkg(pBuffer, nBufLen))
	{
		return false;
	}

	nPkgLen = pBuffer[2];

	return true;
}



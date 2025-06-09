#include "StdAfx.h"
#include "StringCmp.h"
#include "StringCmpBlock.h"

class _CStringCmpTempBuffer_
{
public:
	_CStringCmpTempBuffer_()
	{
		g_pStrCmpBuf1 = NULL;
		g_pStrCmpBuf2 = NULL;
		m_nLength = 0;
	}

	virtual ~_CStringCmpTempBuffer_()
	{
		Free();
	}

private:
	BYTE *g_pStrCmpBuf1, *g_pStrCmpBuf2;
	long m_nLength;

	void Free()
	{
		if (g_pStrCmpBuf1 != NULL)
		{
			delete g_pStrCmpBuf1;
			g_pStrCmpBuf1 = NULL;
		}

		if (g_pStrCmpBuf2 != NULL)
		{
			delete g_pStrCmpBuf2;
			g_pStrCmpBuf2 = NULL;
		}
	}

public:
	void InitStrCmpBuf(long nLen, BYTE **ppBuffer1, BYTE **ppBuffer2)
	{
		if (m_nLength >= nLen)
		{
			*ppBuffer1 = g_pStrCmpBuf1;
			*ppBuffer2 = g_pStrCmpBuf2;
			return;
		}
		
		Free();

		g_pStrCmpBuf1 = new BYTE[nLen+5];
		g_pStrCmpBuf2 = new BYTE[nLen+5];

		*ppBuffer1 = g_pStrCmpBuf1;
		*ppBuffer2 = g_pStrCmpBuf2;
	}
};

_CStringCmpTempBuffer_ g_o_CStringCmpTempBuffer_;

void _strcmp_init_buffer(long nLen, BYTE **ppBuffer1, BYTE **ppBuffer2)
{
	g_o_CStringCmpTempBuffer_.InitStrCmpBuf(nLen, ppBuffer1, ppBuffer2);
}

CStringCmp::CStringCmp()
{ 

}

CStringCmp::~CStringCmp()
{
	m_oStrCmpBlks1.DeleteAll();
	m_oStrCmpBlks2.DeleteAll();
}
BOOL CStringCmp::IsSameStrCmp(CString *pStr1,CString *pStr2)
{   
	if (m_pStrRef1 == pStr1 && m_pStrRef2 == pStr2)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

void CStringCmp::StrCmp(CString *pStr1,CString *pStr2)
{   
	m_pStrRef1 = pStr1;
	m_pStrRef2 = pStr2;
	m_oStrCmpBlks1.m_pStringRef = pStr1;
	m_oStrCmpBlks2.m_pStringRef = pStr2;

	m_oStrCmpBlks1.DeleteAll();
	m_oStrCmpBlks2.DeleteAll();

	int nStrLength1=pStr1->GetLength();
	int nStrLength2=pStr2->GetLength();

	if (nStrLength1 == 0 && nStrLength2 == 0)
	{
		return;
	}

	CString *pSource,*pSubString;
	
	pSource=(nStrLength1>=nStrLength2)? pStr1 :pStr2;
	pSubString=(nStrLength1>=nStrLength2)? pStr2 :pStr1;

	int nSourceArry =(nStrLength1>=nStrLength2)? nStrLength1 :nStrLength2;                                     //主串的长度
	int nSubArry =(nStrLength1>=nStrLength2)? nStrLength2 :nStrLength1;                                     //子串的长度
	BYTE *pnSourceSz = NULL;
	BYTE *pnSubSz    = NULL;
	_strcmp_init_buffer(nSourceArry, &pnSourceSz, &pnSubSz);
	memset(pnSourceSz, 0xFF, nSourceArry*sizeof(BYTE));
	memset(pnSubSz, 0xFF, nSourceArry*sizeof(BYTE));

	int SourceBegin=0,Findnext=0;
	CString StrTemp1;

	for (int i=0;i<nSubArry;i++)
	{ 
		for (int j=nSubArry-i;j>=2;j--)
		{
			StrTemp1 = pSubString->Mid(i,j);
			SourceBegin = pSource->Find(StrTemp1,Findnext);
			
			if (SourceBegin != -1)
			{
				for (int i1=SourceBegin;i1<(SourceBegin+j);i1++)
				{
					pnSourceSz[i1]=1;
				}

				for (int i2=i;i2<(i+j);i2++)
				{
					pnSubSz[i2]=1;
				}

				Findnext=SourceBegin+j;
				i=i+j-1;

				break;
			} 
		}
	}

	BYTE *pBuf_a, *pBuf_b;

	if (nSourceArry==nStrLength1)
	{
		pBuf_a = pnSourceSz;
		pBuf_b = pnSubSz;
	} 
	else 
	{
		pBuf_b = pnSourceSz;
		pBuf_a = pnSubSz;
	}

	InitBlocks(&m_oStrCmpBlks1, pBuf_a, nStrLength1, pStr1);
	InitBlocks(&m_oStrCmpBlks2, pBuf_b, nStrLength2, pStr2);
}

void CStringCmp::InitBlocks(CStringCmpBlocks *pBlocks, BYTE *pBuff, long nLen, CString *pStr)
{
	long j2 = 0;

#ifndef _UNICODE
	//ASCII编码格式下，中文会遇到两个字，前一个字节相同的情况，例如：
	//零序过流加速段定值：C1 E3 D0 F2 B9 FD C1 F7 BC D3 CB D9 B6 CE B6 A8 D6 B5
	//零序过流加速定值：  C1 E3 D0 F2 B9 FD C1 F7 BC D3 CB D9 B6 A8 D6 B5
	//段和定  第一个字节都是B6
	//ASCII编码格式下，两个字符串比较，查找到的相同子串为：
	//                    C1 E3 D0 F2 B9 FD C1 F7 BC D3 CB D9 B6
	//会多算一个字节，把汉字“段”拆成了两部分，导致乱码
	long nChinese = 0;

	for (j2=0;j2<nLen-1;j2++)
	{
		if (pStr->GetAt(j2) < 0)
		{
			nChinese++;
		}

		if (pBuff[j2] != pBuff[j2+1])
		{
			if (nChinese == 1)
			{//非完整汉字
				pBuff[j2] = pBuff[j2+1];
			}
		}

		if (nChinese == 2)
		{//ASCII编码格式下，一个汉字两个字节
			nChinese = 0;
		}
	}
#endif

    long nBegin = 0;
	CStringCmpBlock *pStringCmpBlock = NULL;

	for (j2=0;j2<nLen-1;j2++)
	{
		if (pBuff[j2] != pBuff[j2+1])
		{
			pStringCmpBlock = pBlocks->AddNew(nBegin, j2-nBegin+1, pBuff[j2], pStr);
			nBegin=j2+1;
		}
	}

	if (nBegin != nLen)
	{
		pStringCmpBlock = pBlocks->AddNew(nBegin, j2-nBegin+1, pBuff[j2], pStr);
	}

	if (pBlocks->GetCount() == 0)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("%s  none blocks"), pStr->GetString());
	}
}


BOOL CStringCmp_FilePath(const CString &strPathSrc, const CString &strPathDest)
{
	if (strPathSrc == strPathDest)
	{
		return TRUE;
	}

	CStringCmp oStrCmp;
	CStringCmpBlocks listBlks1, listBlks2;
	
	oStrCmp.StrCmp((CString*)&strPathSrc, (CString*)&strPathDest);
	oStrCmp.m_oStrCmpBlks1.GetAllBlocksByState(listBlks1, CMPSTATE_UNMATCH);
	oStrCmp.m_oStrCmpBlks2.GetAllBlocksByState(listBlks2, CMPSTATE_UNMATCH);

#ifdef _DEBUG
    CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("%s   <===>   %s"), strPathSrc.GetString(), strPathDest.GetString());
	oStrCmp.m_oStrCmpBlks1.Log(CMPSTATE_UNMATCH);
	oStrCmp.m_oStrCmpBlks2.Log(CMPSTATE_UNMATCH);
#endif

	BOOL bRet = FALSE;
	CStringCmpBlock *pBlk1 = NULL, *pBlk2 = NULL;
	
	if (listBlks1.GetCount() == 1 && listBlks2.GetCount() == 1)
	{
		pBlk1 = listBlks1.GetHead();
		pBlk2 = listBlks2.GetHead();

		if ((pBlk1->GetString().Left(1) == _T("~")) || (pBlk2->GetString().Left(1) == _T("~")) )
		{
			bRet = TRUE;
		}
	}

	listBlks2.RemoveAll();
	listBlks1.RemoveAll();

	return bRet;
}


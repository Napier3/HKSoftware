// HexEditBaseCmp.cpp : 实现文件
//

#include "stdafx.h"
#include "HexEditBaseCmp.h"


// CHexEditBaseCmp

CHexEditBaseCmp::CHexEditBaseCmp(CHexEditBase *pHex1, CHexEditBase *pHex2)
{
	CmpHexEdit(pHex1, pHex2);
}


CHexEditBaseCmp::CHexEditBaseCmp()
{
	m_pHex1 = NULL;
	m_pHex2 = NULL;
}

CHexEditBaseCmp::~CHexEditBaseCmp()
{
}

void CHexEditBaseCmp::CmpHexEdit(CHexEditBase *pHex1, CHexEditBase *pHex2)
{
	m_pHex1 = pHex1;
	m_pHex2 = pHex2;

	CHexEditBlocks *pBlocks = m_pHex1->GetHexEditBlocks();
	pBlocks->DeleteAllBloks();

	pBlocks = m_pHex2->GetHexEditBlocks();
	pBlocks->DeleteAllBloks();

	BYTE *pBuffer1 = NULL;
	UINT nLength1 = 0;
	BYTE *pBuffer2 = NULL;
	UINT nLength2 = 0;

	m_pHex1->GetAllDataRef(&pBuffer1, nLength1);
	m_pHex2->GetAllDataRef(&pBuffer2, nLength2);
	CmpHex(pBuffer1, nLength1, pBuffer2, nLength2);
}

void CHexEditBaseCmp::CmpHex(BYTE *pBuffer1, long nLength1, BYTE *pBuffer2, long nLength2)
{
	long nLength = min(nLength1, nLength2);

	CHexEditBlocks *pBlocks = m_pHex1->GetHexEditBlocks();
	pBlocks->DeleteAllBloks();
	m_pHex2->GetHexEditBlocks();
	pBlocks->DeleteAllBloks();

	if (nLength1 == 0 || nLength2 == 0)
	{
		return;
	}

	CmpHex(pBuffer1, pBuffer2, nLength);

	if (nLength1 != nLength && nLength1 > 0)
	{
		CHexEditBlocks *pBlocks = m_pHex1->GetHexEditBlocks();
		pBlocks->AddBlock(nLength, nLength1-1);
	}

	if (nLength2 != nLength && nLength2 > 0)
	{
		CHexEditBlocks *pBlocks = m_pHex2->GetHexEditBlocks();
		pBlocks->AddBlock(nLength, nLength2-1);
	}
}

void CHexEditBaseCmp::CmpHex(BYTE *pBuffer1, BYTE *pBuffer2, long nLength)
{
	if (nLength == 0)
	{
		return;
	}

	long nBegin = -1;
	long nEnd = -1;
	
	BYTE *p1 = pBuffer1;
	BYTE *pEnd = pBuffer1 + nLength;
	BYTE *p2 = pBuffer2;

	while (p1< pEnd)
	{
		if (*p1 == *p2)
		{//值相同
			if (nBegin != -1 && nEnd == -1)
			{//前面有不相同的
				nEnd = p1 - pBuffer1 - 1;
				AddCmpBlock(nBegin, nEnd);
				nBegin = -1;
				nEnd = -1;
			}
		}
		else
		{//值不相同
			if (nBegin == -1)
			{//第一个不相同的位置
				nBegin = p1 - pBuffer1;
			}
		}

		p1++;
		p2++;
	}

	if (nBegin != -1 && nEnd == -1)
	{
		nEnd = p1 - pBuffer1 - 1;
		AddCmpBlock(nBegin, nEnd);
	}
}

void CHexEditBaseCmp::AddCmpBlock(long nBegin, long nEnd)
{
	CHexEditBlocks *pBlocks = m_pHex1->GetHexEditBlocks();
	pBlocks->AddBlock(nBegin, nEnd);

	pBlocks = m_pHex2->GetHexEditBlocks();
	pBlocks->AddBlock(nBegin, nEnd);
}


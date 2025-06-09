// MemBuffer_Float.cpp: implementation of the CMemBuffer_Float class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MemBuffer_Float.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMemBuffer_Float::CMemBuffer_Float()
{
	m_nBufferLength		= 0;	
	m_nDataFillBeginPos = 0;
	m_nDataLength		= 0;
	m_pBuffer			= NULL;
	m_pdValue           = NULL;
	m_strBufferID		= "";   
	memset(m_dwFreqZeroPosition, 0, MAX_FREQ_ZERO_POS_BUFFER*sizeof(DWORD));
	m_nFreqZeroPosCount = 0;
	
}

CMemBuffer_Float::~CMemBuffer_Float()
{
	FreeBuffer();
}

void CMemBuffer_Float::BuildComplexBufferScript()
{

}


float* CMemBuffer_Float::GetBuffer()
{
	return m_pBuffer;
}

long CMemBuffer_Float::GetBufferLength()
{
	return m_nBufferLength;
}

void CMemBuffer_Float::OffsetDataFillBeginPosition(long nLen)
{
	m_nDataFillBeginPos += nLen;
	m_nDataLength += nLen;
	
	if (m_nDataFillBeginPos >= m_nBufferLength)
	{
		m_nDataFillBeginPos -= m_nBufferLength;
	}
	
	if (m_nDataLength >= m_nBufferLength)
	{
		m_nDataLength = m_nBufferLength;
	}	
}

long CMemBuffer_Float::GetDataFillBeginPosition()
{
	return m_nDataFillBeginPos;
}

void CMemBuffer_Float::Init()
{
	m_nDataFillBeginPos = 0;
	m_nDataLength		= 0;
}

long CMemBuffer_Float::GetDataLength()
{
	return m_nDataLength;
}

void CMemBuffer_Float::SetBufferLength(long lBufferLen)
{
	FreeBuffer();
	m_nBufferLength = lBufferLen;
	m_pBuffer = new float[lBufferLen+MEMBUFFER_LENGTH_EX];
	memset(m_pBuffer, 0, lBufferLen*sizeof(float));
}

void CMemBuffer_Float::AppendBuffer(float *pBuffer, long lLen)
{
	FreeBuffer();
	m_pBuffer = pBuffer;
	m_nBufferLength = lLen;
}

void CMemBuffer_Float::AppendBuffer(CMemBuffer_Float *pBuffer)
{
	FreeBuffer();
	m_pBuffer = pBuffer->GetBuffer();
}

void CMemBuffer_Float::AttachBuffer(float *pBuffer, long lLen)
{
	FreeBuffer();
	m_pBuffer = pBuffer;
	m_nBufferLength = lLen;
	m_nDataLength = m_nBufferLength;
	m_nDataFillBeginPos = 0;
}

void CMemBuffer_Float::DettachBuffer()
{
	m_pBuffer = NULL;
	m_nBufferLength		= 0;	
	m_nDataFillBeginPos = 0;
	m_nDataLength		= 0;
}


long CMemBuffer_Float::CopyBuffer(float *pBuffer, long lLen, long lGap)
{
	long lPos1Begin = -1;
	long lPos1End = -1;
	long lPos2Begin = -1;
	long lPos2End = -1;

	long lLenCopy = CopyBuffer(lLen, lGap, FALSE, lPos1Begin, lPos1End, lPos2Begin, lPos2End);

	if (lPos1Begin >= 0)
	{
		CopyBufferByPos(pBuffer, lPos1Begin, lPos1End, lGap);
	}

	if (lPos2Begin >= 0)
	{
		CopyBufferByPos(pBuffer+lPos1End-lPos1Begin, lPos2Begin, lPos2End, lGap);
	}

	lLenCopy = CopyBuffer(lLen, lGap, TRUE, lPos1Begin, lPos1End, lPos2Begin, lPos2End);
	
	return lLenCopy;
}

//pBuffer��Դ������
//lCopyBeginPos��Դ���忪ʼ������λ��
long CMemBuffer_Float::CopyBuffer(CMemBuffer_Float *pBuffer, long &lCopyBeginPos, long lGap)
{
	{
		float *pTemp = pBuffer->GetBuffer();
		if (pTemp[pBuffer->GetBufferLength()-1] == 0x0087)
		{
			int i = 0;
		}
	}
	//ȷ��Դ�������ĳ���С�ڵ���Ŀ�껺�����ĳ���
	ASSERT(pBuffer->m_nBufferLength <= m_nBufferLength);
	if(pBuffer->m_nBufferLength > m_nBufferLength)
	{
		return -1;
	}
	
	//
	if (pBuffer->m_nDataLength == 0)
	{
		return -1;
	}
	
	long lOffset = 0;
	long lLen = 0;
	long lCopyLen = 0;
	long lCopyLenRet = 0;
	float *pTemp = NULL;

	//��ǰ����λ�ô��ڿ�ʼ������λ�ã�ֻ��Ҫ����Դ���ݵ�һ������
	//����lCopyBeginPos��pBuffer->m_nDataFillBeginPosλ��
	if (pBuffer->m_nDataFillBeginPos > lCopyBeginPos)
	{
		pTemp = pBuffer->GetBuffer() + lCopyBeginPos;
		lLen = pBuffer->GetDataFillBeginPosition() - lCopyBeginPos;
		lCopyLenRet = CopyBuffer(pTemp, lLen, lGap);

		lOffset = lLen - lCopyLenRet;

//		if (lCopyLenRet == 0)
//		{
//			lCopyBeginPos = lCopyBeginPos + lCopyLenRet;//��һ�ο�����λ��=��ǰλ��+ʵ�ʿ����ĳ���
//		}
//		else if (lCopyBeginPos > 0)
//		{
//			lCopyBeginPos = lCopyBeginPos + lCopyLenRet - lOffset + lGap;
//		}
//		else //(lCopyBeginPos < 0)
//		{
//			lCopyBeginPos = lCopyBeginPos + lCopyLenRet - lOffset;
//		}
		
		lCopyBeginPos = lCopyBeginPos + lCopyLenRet;//��һ�ο�����λ��=��ǰλ��+ʵ�ʿ����ĳ���
	}
	else
	{
		//�ܵĳ���
		long nTotalLen = pBuffer->GetDataLength() - lCopyBeginPos + pBuffer->GetDataFillBeginPosition();

		//��һ�ο���������������������λ��
		pTemp = pBuffer->GetBuffer() + lCopyBeginPos;
		lLen = pBuffer->GetDataLength() - lCopyBeginPos;
		lCopyLen = CopyBuffer(pTemp, lLen, lGap);
		lOffset = lLen - lCopyLen;  //������������е�������ĩβʣ�µĳ���
		lCopyLenRet = lCopyLen;

		//�ڶ��ο���
		lLen = nTotalLen - lCopyLen;

		//�ڶ��ο�ʼ��������ʼλ��
		if(lOffset > 0)
		{
			pTemp = pBuffer->GetBuffer() - lOffset + lGap;
		}
		else if (lOffset == 0)
		{
			pTemp = pBuffer->GetBuffer();
		}
		else //lOffset < 0
		{
			pTemp = pBuffer->GetBuffer() - lOffset;
		}

		//��һ�ο�����λ��=�ڶ���ʵ�ʿ����ĳ���
		lCopyLen = CopyBuffer(pTemp, lLen, lGap);
		lCopyBeginPos = lCopyLen - lOffset; 
		lCopyLenRet += lCopyLen;
	}

	return lCopyLenRet*lGap;
}

//������������������TRUE�޸�������ַ��FALSEʱ��õ�ַ
long CMemBuffer_Float::CopyBuffer(long lLen, long lGap, BOOL bOffsetBuffer, long &lPos1Begin, long &lPos1End, long &lPos2Begin, long &lPos2End)
{
	long lLenCopy = lLen / lGap;
	long nOffset = lLen - lLenCopy * lGap;

	if (nOffset > 0)
	{
		lLenCopy++;
	}

	long lEndPos = m_nDataFillBeginPos + lLenCopy; //Ŀ�껺��������ĩλ��
	long lLenCopy1 = 0, lLenCopy2 = 0;
	
	lPos1Begin = -1;
	lPos1End   = -1;
	lPos2Begin = -1;
	lPos2End   = -1;
	
	if (lEndPos < m_nBufferLength)
	{
		lPos1Begin = m_nDataFillBeginPos;
		lPos1End   = lEndPos;
		
		if (bOffsetBuffer)
		{
			m_nDataFillBeginPos = lEndPos;
		}
	}
	else 
	{
		//��һ�ο���,��m_nDataFillBeginPos��������ĩβ
		lLenCopy1 = m_nBufferLength - m_nDataFillBeginPos;
		lPos1Begin = m_nDataFillBeginPos;
		lPos1End   = m_nBufferLength;
		
		//��һ�ο���,�ӻ�������ʼ��......
		lLenCopy2 = lLenCopy - lLenCopy1;
		lPos2Begin = 0;
		lPos2End   = lLenCopy2;
		
		if (bOffsetBuffer)
		{
			m_nDataFillBeginPos = lLenCopy2;
		}
		
	}
	
	if (bOffsetBuffer)
	{
		m_nDataLength += lLenCopy;
		
		if (m_nDataLength >= m_nBufferLength)
		{
			m_nDataLength = m_nBufferLength;
		}
	}
	
	return lLenCopy*lGap;
}

long CMemBuffer_Float::CopyBufferByPos(float *pBuffer, long lBeginPos, long lEndPos, long lGap)
{
	ASSERT (lBeginPos >= 0 && lEndPos >= 0 && lEndPos >= lBeginPos);
	if (!(lBeginPos >= 0 && lEndPos >= 0 && lEndPos >= lBeginPos))
	{
		return 0;
	}

	float *pDest = NULL;
	float *pDestEnd = NULL;
	float *pSrc = NULL;
	float *pSrcEnd = NULL;	

	pDest = m_pBuffer + lBeginPos;
	
	if (lGap == 1)
	{
		memcpy(pDest, pBuffer, (lEndPos - lBeginPos)*sizeof(float));
	}
	else
	{
		pDestEnd = m_pBuffer + lEndPos;
		pSrc = pBuffer;
		
		while (pDest < pDestEnd)
		{
			*pDest = *pSrc;
			pDest++;
			pSrc += lGap;
		}
	}

	return lGap * (lEndPos - lBeginPos);
}


long CMemBuffer_Float::AddValue(float *pValue)
{
	return AddValue(*pValue);
}

long CMemBuffer_Float::AddValue(float fValue)
{
	m_pBuffer[m_nDataFillBeginPos] = fValue;
	
	if (m_nDataFillBeginPos + 1 < m_nBufferLength)
	{
		m_nDataFillBeginPos++;
	}
	else 
	{
		m_nDataFillBeginPos = 0;
	}

	m_nDataLength ++;

	if (m_nDataLength >= m_nBufferLength)
	{
		m_nDataLength = m_nBufferLength;
	}
	
	return 1;
}

void CMemBuffer_Float::FreeBuffer()
{
	if (m_pBuffer!= NULL)
	{
		delete m_pBuffer;
		m_pBuffer = NULL;
	}
	m_nBufferLength		= 0;	
	m_nDataFillBeginPos = 0;
	m_nDataLength		= 0;
}

double CMemBuffer_Float::GetCurrValue()
{
	double dValue = 0.0;

	if (m_nDataLength <= 1)
	{
		return dValue;
	}

	float *pBuffer = GetBuffer();
	long nValuePos = 0; 

	if (m_nDataLength == m_nBufferLength)
	{
		nValuePos = m_nDataFillBeginPos - 1;

		if (nValuePos < 1)
		{
			nValuePos = m_nBufferLength - 1;
		}
	}
	else
	{
		nValuePos = m_nDataFillBeginPos - 1;
	}

	dValue = *(pBuffer + nValuePos);

	return dValue;
}

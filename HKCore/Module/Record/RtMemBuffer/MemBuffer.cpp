// MemBuffer.cpp: implementation of the CMemBufferclass.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MemBuffer.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
/*

template <class T> 
CMemBuffer<T>::CMemBuffer()
{
	m_nBufferLength		= 0;	
	m_nDataFillBeginPos = 0;
	m_nDataLength		= 0;
	m_pBuffer			= NULL;
}
*/

/*
template <class T> 
CMemBuffer<T>::~CMemBuffer()
{
	FreeBuffer();
}
*/

/*
template <class T> 
T* CMemBuffer<T>::GetBuffer()
{
	return m_pBuffer;
}

template <class T> 
long CMemBuffer<T>::GetBufferLength()
{
	return m_nBufferLength;
}

template <class T> 
long CMemBuffer<T>::GetDataFillBeginPosition()
{
	return m_nDataFillBeginPos;
}

template <class T> 
long CMemBuffer<T>::GetDataLength()
{
	return m_nDataLength;
}
*/
//
//template <class T> 
//void CMemBuffer<T>::SetBufferLength(long lBufferLen)
//{
//	FreeBuffer();
//	m_nBufferLength = lBufferLen;
//	m_pBuffer = new T[lBufferLen];
//	memset(m_pBuffer, 0, lBufferLen*sizeof(T));
//}
//
//template <class T> 
//void CMemBuffer<T>::AppendBuffer(T *pBuffer, long lLen)
//{
//	FreeBuffer();
//	m_pBuffer = pBuffer;
//	m_nBufferLength = lLen;
//}
//
//template <class T> 
//void CMemBuffer<T>::AppendBuffer(CMemBuffer*pBuffer)
//{
//	FreeBuffer();
//	m_pBuffer = pBuffer->GetBuffer();
//}
//
//template <class T> 
//long CMemBuffer<T>::CopyBuffer(T *pBuffer, long lLen, long lGap)
//{
//	long lPos1Begin = -1;
//	long lPos1End = -1;
//	long lPos2Begin = -1;
//	long lPos2End = -1;
//
//	long lLenCopy = CopyBuffer(lLen, lGap, FALSE, lPos1Begin, lPos1End, lPos2Begin, lPos2End);
//
//	if (lPos1Begin >= 0)
//	{
//		CopyBufferByPos(pBuffer, lPos1Begin, lPos1End, lGap);
//	}
//
//	if (lPos2Begin >= 0)
//	{
//		CopyBufferByPos(pBuffer+lPos1End-lPos1Begin, lPos2Begin, lPos2End, lGap);
//	}
//
//	lLenCopy = CopyBuffer(lLen, lGap, TRUE, lPos1Begin, lPos1End, lPos2Begin, lPos2End);
//	
//	return lLenCopy;
//}
//
////pBuffer��Դ������
////lCopyBeginPos��Դ���忪ʼ������λ��
//template <class T> 
//long CMemBuffer<T>::CopyBuffer(CMemBuffer*pBuffer, long &lCopyBeginPos, long lGap)
//{
//	{
//		T *pTemp = pBuffer->GetBuffer();
//		if (pTemp[pBuffer->GetBufferLength()-1] == 0x0087)
//		{
//			int i = 0;
//		}
//	}
//	//ȷ��Դ�������ĳ���С�ڵ���Ŀ�껺�����ĳ���
//	ASSERT(pBuffer->m_nBufferLength <= m_nBufferLength);
//	if(pBuffer->m_nBufferLength > m_nBufferLength)
//	{
//		return -1;
//	}
//	
//	//
//	if (pBuffer->m_nDataLength == 0)
//	{
//		return -1;
//	}
//	
//	long lOffset = 0;
//	long lLen = 0;
//	long lCopyLen = 0;
//	long lCopyLenRet = 0;
//	T *pTemp = NULL;
//
//	//��ǰ����λ�ô��ڿ�ʼ������λ�ã�ֻ��Ҫ����Դ���ݵ�һ������
//	//����lCopyBeginPos��pBuffer->m_nDataFillBeginPosλ��
//	if (pBuffer->m_nDataFillBeginPos > lCopyBeginPos)
//	{
//		pTemp = pBuffer->GetBuffer() + lCopyBeginPos;
//		lLen = pBuffer->GetDataFillBeginPosition() - lCopyBeginPos;
//		lCopyLenRet = CopyBuffer(pTemp, lLen, lGap);
//
//		lOffset = lLen - lCopyLenRet;
//
//#ifdef _use_global_log_
//		CString strLog;
//		strLog.Format("one offset = %d", lOffset);
//		debug_trace(strLog);
//#endif
////		if (lCopyLenRet == 0)
////		{
////			lCopyBeginPos = lCopyBeginPos + lCopyLenRet;//��һ�ο�����λ��=��ǰλ��+ʵ�ʿ����ĳ���
////		}
////		else if (lCopyBeginPos > 0)
////		{
////			lCopyBeginPos = lCopyBeginPos + lCopyLenRet - lOffset + lGap;
////		}
////		else //(lCopyBeginPos < 0)
////		{
////			lCopyBeginPos = lCopyBeginPos + lCopyLenRet - lOffset;
////		}
//		
//		lCopyBeginPos = lCopyBeginPos + lCopyLenRet;//��һ�ο�����λ��=��ǰλ��+ʵ�ʿ����ĳ���
//	}
//	else
//	{
//		//�ܵĳ���
//		long nTotalLen = pBuffer->GetDataLength() - lCopyBeginPos + pBuffer->GetDataFillBeginPosition();
//
//		//��һ�ο���������������������λ��
//		pTemp = pBuffer->GetBuffer() + lCopyBeginPos;
//		lLen = pBuffer->GetDataLength() - lCopyBeginPos;
//		lCopyLen = CopyBuffer(pTemp, lLen, lGap);
//		lOffset = lLen - lCopyLen;  //������������е�������ĩβʣ�µĳ���
//		lCopyLenRet = lCopyLen;
//
//		//�ڶ��ο���
//		lLen = nTotalLen - lCopyLen;
//
//		//�ڶ��ο�ʼ��������ʼλ��
//		if(lOffset > 0)
//		{
//			pTemp = pBuffer->GetBuffer() - lOffset + lGap;
//		}
//		else if (lOffset == 0)
//		{
//			pTemp = pBuffer->GetBuffer();
//		}
//		else //lOffset < 0
//		{
//			pTemp = pBuffer->GetBuffer() - lOffset;
//		}
//
//		//��һ�ο�����λ��=�ڶ���ʵ�ʿ����ĳ���
//		lCopyLen = CopyBuffer(pTemp, lLen, lGap);
//		lCopyBeginPos = lCopyLen - lOffset; 
//		lCopyLenRet += lCopyLen;
//	}
//
//	return lCopyLenRet*lGap;
//}
//
////������������������TRUE�޸�������ַ��FALSEʱ��õ�ַ
//template <class T> 
//long CMemBuffer<T>::CopyBuffer(long lLen, long lGap, BOOL bOffsetBuffer, long &lPos1Begin, long &lPos1End, long &lPos2Begin, long &lPos2End)
//{
//	long lLenCopy = lLen / lGap;
//	long nOffset = lLen - lLenCopy * lGap;
//
//	if (nOffset > 0)
//	{
//		lLenCopy++;
//	}
//
//	long lEndPos = m_nDataFillBeginPos + lLenCopy; //Ŀ�껺��������ĩλ��
//	long lLenCopy1 = 0, lLenCopy2 = 0;
//	
//	lPos1Begin = -1;
//	lPos1End   = -1;
//	lPos2Begin = -1;
//	lPos2End   = -1;
//	
//	if (lEndPos < m_nBufferLength)
//	{
//		lPos1Begin = m_nDataFillBeginPos;
//		lPos1End   = lEndPos;
//		
//		if (bOffsetBuffer)
//		{
//			m_nDataFillBeginPos = lEndPos;
//		}
//	}
//	else 
//	{
//		//��һ�ο���,��m_nDataFillBeginPos��������ĩβ
//		lLenCopy1 = m_nBufferLength - m_nDataFillBeginPos;
//		lPos1Begin = m_nDataFillBeginPos;
//		lPos1End   = m_nBufferLength;
//		
//		//��һ�ο���,�ӻ�������ʼ��......
//		lLenCopy2 = lLenCopy - lLenCopy1;
//		lPos2Begin = 0;
//		lPos2End   = lLenCopy2;
//		
//		if (bOffsetBuffer)
//		{
//			m_nDataFillBeginPos = lLenCopy2;
//		}
//		
//	}
//	
//	if (bOffsetBuffer)
//	{
//		m_nDataLength += lLenCopy;
//		
//		if (m_nDataLength >= m_nBufferLength)
//		{
//			m_nDataLength = m_nBufferLength;
//		}
//	}
//	
//	return lLenCopy*lGap;
//}
//
//template <class T> 
//long CMemBuffer<T>::CopyBufferByPos(T *pBuffer, long lBeginPos, long lEndPos, long lGap)
//{
//	ASSERT (lBeginPos >= 0 && lEndPos >= 0 && lEndPos >= lBeginPos);
//	if (!(lBeginPos >= 0 && lEndPos >= 0 && lEndPos >= lBeginPos))
//	{
//		return 0;
//	}
//
//	T *pDest = NULL;
//	T *pDestEnd = NULL;
//	T *pSrc = NULL;
//	T *pSrcEnd = NULL;	
//
//	pDest = m_pBuffer + lBeginPos;
//	
//	if (lGap == 1)
//	{
//		memcpy(pDest, pBuffer, (lEndPos - lBeginPos)*sizeof(T));
//	}
//	else
//	{
//		pDestEnd = m_pBuffer + lEndPos;
//		pSrc = pBuffer;
//		
//		while (pDest < pDestEnd)
//		{
//			*pDest = *pSrc;
//			pDest++;
//			pSrc += lGap;
//		}
//	}
//
//	return lGap * (lEndPos - lBeginPos);
//}
//
//template <class T> 
//long CMemBuffer<T>::AddValue(T *pValue)
//{
//	m_pBuffer[m_nDataFillBeginPos] = *pValue;
//
//	if (m_nDataFillBeginPos + 1 < m_nBufferLength)
//	{
//		m_nDataFillBeginPos++;
//	}
//	else 
//	{
//		m_nDataFillBeginPos = 0;
//	}
//
//	return 1;
//}
//
//template <class T> 
//long CMemBuffer<T>::AddValue(T tValue)
//{
//	m_pBuffer[m_nDataFillBeginPos] = tValue;
//	
//	if (m_nDataFillBeginPos + 1 < m_nBufferLength)
//	{
//		m_nDataFillBeginPos++;
//	}
//	else 
//	{
//		m_nDataFillBeginPos = 0;
//	}
//	
//	return 1;
//}
//
//template <class T> 
//void CMemBuffer<T>::FreeBuffer()
//{
//	if (m_pBuffer!= NULL)
//	{
//		delete m_pBuffer;
//		m_pBuffer = NULL;
//	}
//	m_nBufferLength		= 0;	
//	m_nDataFillBeginPos = 0;
//	m_nDataLength		= 0;
//}
//
//template <class T> 
//void CMemBuffer<T>::InitPara()
//{
//	m_nDataFillBeginPos = 0;
//	m_nDataLength		= 0;
//}
//
//
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
//template <class T, class T2> 
//CComplexMemBuffer<T, T2>::CComplexMemBuffer<T, T2>()
//{
//	m_pScript = NULL;
//	m_nSrcMemBufferCount = 0;
//	long nIndex = 0;
//	
//	for (nIndex=0; nIndex<COMPLEX_MEMBUFFER_SRCBUF_MAXCOUNT; nIndex++)
//	{
//		m_pSrcBuffer[nIndex] = NULL;
//	}
//	
//	//m_pScript = new CRtMemBufScript();
//}
//
//template <class T, class T2> 
//CComplexMemBuffer<T, T2>::~CComplexMemBuffer<T, T2>()
//{
//	if (m_pScript != NULL)
//	{
//		delete m_pScript;
//		m_pScript = NULL;
//	}
//}
//
//template <class T, class T2> 
//BOOL CComplexMemBuffer<T, T2>::ExecScript(long nPos1Begin, long nPos1End, long nPos2Begin, long nPos2End)
//{
//	short nVal = 0;
//	long nIndex = 0;
//	
//	for (nIndex=nPos1Begin; nIndex<nPos1End; nIndex++)
//	{
//		m_pScript->m_nIndex = nIndex;
//		m_pScript->RunExpression();
//	}
//	
//	for (nIndex=nPos2Begin; nIndex<nPos2End; nIndex++)
//	{
//		m_pScript->m_nIndex = nIndex;
//		m_pScript->RunExpression();
//	}
//	
//	return TRUE;
//}
//

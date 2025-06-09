// ComtradeDataBase.cpp: implementation of the CComtradeDataBase class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ComtradeDataBase.h"
#include "ComtradeMngr.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CComtradeDataBase::CComtradeDataBase()
{
	m_pnAttachBuffer = NULL;
	m_nChannelIndex  = 0;
// 	m_strName		 = "";
// 	m_strPhaseID	 = "";
// 	m_strCcbm		 = "";
	m_bBufferAllocOwn = TRUE;
	m_bUsed = TRUE;
}

CComtradeDataBase::~CComtradeDataBase()
{
	ClearBuffer();
}

void CComtradeDataBase::SaveChanInfo(CString& strInfor)
{
}

//没有用到
void CComtradeDataBase::ClearBuffer()
{
	if (m_bBufferAllocOwn)
	{
		if (m_pnAttachBuffer != NULL)
		{
			delete m_pnAttachBuffer;
			m_pnAttachBuffer = NULL;
		}
	}
	else
	{
		m_pnAttachBuffer = NULL;
	}
}

void CComtradeDataBase::InitBuffer_Circle(long nDataFileType,long nTotalPoints)
{
	unsigned short uTmp = 0;

	if ((m_pnAttachBuffer != NULL)&&(m_nTotalPoints>0))
	{
		uTmp = m_pnAttachBuffer[m_nTotalPoints-1];
	}

	if (GetMemBuffer_UShortNum()<nTotalPoints)
	{
		AllocBuffer(nTotalPoints);
	}

	if ((m_pnAttachBuffer != NULL)&&(nTotalPoints>0))
	{
		m_pnAttachBuffer[0] = uTmp;
	}
}

void CComtradeDataBase::AllocBuffer(long nTotalBufferLenth)
{
	ClearBuffer();

	//2020-07-26  lijunqing
	//m_nTotalPoints = nTotalPoints;
	m_pnAttachBuffer = new unsigned short[nTotalBufferLenth];
	ZeroMemory(m_pnAttachBuffer, sizeof(unsigned short) * nTotalBufferLenth);
	m_bBufferAllocOwn = TRUE;

	m_oMemBuffer_UShort.AttachBuffer(m_pnAttachBuffer, nTotalBufferLenth);
}

void CComtradeDataBase::AttachBuffer(unsigned short* pBuffer)
{
	ClearBuffer();
	ASSERT (pBuffer != NULL);
	m_bBufferAllocOwn = FALSE;
	m_pnAttachBuffer = pBuffer;
}

//定义获得通道显示个数的函数
void CComtradeDataBase::GetCountBeforeBind(int*ipBind)
{

}

long CComtradeDataBase::XmlReadOwn( CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys )
{
	CComtradeFileXmlRWKeys *pXmlKeys = (CComtradeFileXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strNameKey, oNode, m_strName);
	xml_GetAttibuteValue(pXmlKeys->m_strIDKey, oNode, m_strPhaseID);
	xml_GetAttibuteValue(pXmlKeys->m_strIndexKey, oNode, m_nChannelIndex);
	xml_GetAttibuteValue(pXmlKeys->m_strCcbmKey, oNode, m_strCcbm);

	CString strData;
	xml_GetCDATA(oNode, strData);

	if (strData.GetLength() > 0)
	{

	}

	return 0;
}

long CComtradeDataBase::XmlWriteOwn( CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys )
{
	CComtradeFileXmlRWKeys *pXmlKeys = (CComtradeFileXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strNameKey, oElement, m_strName);
	xml_SetAttributeValue(pXmlKeys->m_strIDKey, oElement, m_strPhaseID);
	xml_SetAttributeValue(pXmlKeys->m_strIndexKey, oElement, m_nChannelIndex);
	xml_SetAttributeValue(pXmlKeys->m_strCcbmKey, oElement, m_strCcbm);

	CString strData;
	xml_SetCDATA(oXMLDoc, oElement, strData);
	InitByHexDataString(strData);

	return 0;
}

BOOL CComtradeDataBase::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);
	CComtradeDataBase *p = (CComtradeDataBase*)pDest;
	p->m_nChannelIndex = m_nChannelIndex;
	p->m_strPhaseID = m_strPhaseID;
	p->m_strCcbm = m_strCcbm;
	p->m_bUsed = m_bUsed;
	p->m_nTotalPoints = m_nTotalPoints;
	return TRUE;
}

void CComtradeDataBase::InitByHexDataString(const CString &strData)
{
	long nLen = strData.GetLength() / 4;

	if (nLen == 0)
	{
		return;
	}

	AllocBuffer(nLen);

	InitByHexDataString(strData.GetString());	
}

void CComtradeDataBase::InitByHexDataString(const char *strData)
{
	HexToValue(strData, m_nTotalPoints*2, (BYTE*)m_pnAttachBuffer, 0);
}

void CComtradeDataBase::InitByHexDataString(const wchar_t *strData)
{
	HexToValue(strData, m_nTotalPoints*2, (BYTE*)m_pnAttachBuffer, 0);
}

long CComtradeDataBase::GetHexDataString(CString &strData)
{
	if (m_nTotalPoints == 0)
	{
		return 0;
	}

	long nLen = m_nTotalPoints * 4 + 1;
	char *pDestHex = new char[nLen];
	memset(pDestHex, 0, nLen);
	GetHexDataString(strData);

	strData = pDestHex;
	delete pDestHex;

	return m_nTotalPoints;
}

long CComtradeDataBase::GetHexDataString(char *strData)
{
	if (m_nTotalPoints == 0)
	{
		return 0;
	}

	ValueToHex((BYTE *)m_pnAttachBuffer, m_nTotalPoints*2, strData, FALSE, FALSE);

	return m_nTotalPoints;
}

void CComtradeDataBase::InsertCyclePoints( long nBeginPos, long nEndPos, long nInsertPos, int nCycleIndex, int nDataFileType )
{
	CMemBuffer_UShort* pShortBuffer = GetMemBuffer_UShort();

	if(!pShortBuffer)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("当前通道数据缓存为空,无法进行插值操作"));
		return;
	}

	unsigned short* pBuffer = pShortBuffer->GetBuffer();
	long nBufferSize = pShortBuffer->GetBufferLength();

	if((nBufferSize <= 0)||(pBuffer == NULL))
	{
// 		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("当前通道数据缓存长度为0,无法进行插值操作"));
		return;
	}

	long nInsertLength = nEndPos - nBeginPos + 1;

	// 根据数据类型选择合适的缓冲区和分配大小
	if (nDataFileType == COMTRADE_DATAFILE_TYPE_ASCII && IsAnalogData())
	{
		nBufferSize /=2;//COMTRADE_DATAFILE_TYPE_ASCII模式2个无符号短整型标识1个通道数据
		long nMoveLength = nBufferSize - nInsertPos;
		long nAfterBufferSize = nBufferSize + (nInsertLength * nCycleIndex);

		// 处理long类型的数据
		int* pOldBuffer = new int[nBufferSize]; 
		memset(pOldBuffer, 0, nBufferSize * sizeof(int));
		memcpy(pOldBuffer, pBuffer, nBufferSize * sizeof(int));

		AllocBuffer(nAfterBufferSize *2); // 分配更大的缓冲区
		int* pBufferLong = (int*)pShortBuffer->GetBuffer();

		// 更新波形数据
		memcpy(pBufferLong, pOldBuffer, nInsertPos * sizeof(int));

		for (int nIndex = 0; nIndex < nCycleIndex; ++nIndex)
		{
			memcpy(pBufferLong + nInsertPos + nIndex * nInsertLength, pOldBuffer + nBeginPos, nInsertLength * sizeof(int));
		}

		memcpy(pBufferLong + nInsertPos + nInsertLength * nCycleIndex, pOldBuffer + nInsertPos, nMoveLength * sizeof(int));
		m_nTotalPoints = nAfterBufferSize; // 更新点数
		delete[] pOldBuffer;
	}
	else
	{
		long nMoveLength = nBufferSize - nInsertPos;
		long nAfterBufferSize = nBufferSize + (nInsertLength * nCycleIndex);

		// 处理unsigned short类型的数据
		unsigned short* pOldBuffer = new unsigned short[nBufferSize];
		memset(pOldBuffer, 0, nBufferSize * sizeof(unsigned short));
		memcpy(pOldBuffer, pBuffer, nBufferSize * sizeof(unsigned short));

		AllocBuffer(nAfterBufferSize);
		pBuffer = pShortBuffer->GetBuffer();

		//更新波形数据
		memcpy(pBuffer, pOldBuffer, nInsertPos * sizeof(unsigned short));

		for (int nIndex = 0; nIndex < nCycleIndex; ++nIndex)
		{
			memcpy(pBuffer + nInsertPos + nIndex * nInsertLength, pOldBuffer + nBeginPos, nInsertLength * sizeof(unsigned short));
		}

		memcpy(pBuffer + nInsertPos + nInsertLength * nCycleIndex, pOldBuffer + nInsertPos, nMoveLength * sizeof(unsigned short));

		m_nTotalPoints = nAfterBufferSize; // 更新点数
		delete[] pOldBuffer;
	}

// 	//新的内存缓存区
// 	unsigned short* pOldBuffer = new unsigned short[nBufferSize];
// 	memset(pOldBuffer, 0 , nBufferSize * sizeof(unsigned short));
// 	if(!pOldBuffer)
// 	{
// 		return;
// 	}
// 	memcpy(pOldBuffer, pBuffer, nBufferSize * sizeof(unsigned short));
// 
// 
// 	AllocBuffer(nAfterBufferSize);
// 	pBuffer = pShortBuffer->GetBuffer();
// 
// 	//更新波形数据
// 	memcpy(pBuffer, pOldBuffer, nInsertPos * sizeof(unsigned short));//拷贝起点之前的数据
// 
// 	// 插入新数据，考虑循环次数
// 	for (int nIndex = 0; nIndex < nCycleIndex; ++nIndex)
// 	{
// 		memcpy(pBuffer + nInsertPos + nIndex * nInsertLength, pOldBuffer + nBeginPos, nInsertLength * sizeof(unsigned short));
// 	}
// 	memcpy(pBuffer + nInsertPos + nInsertLength * nCycleIndex, pOldBuffer + nInsertPos, nMoveLength * sizeof(unsigned short));
// 
// 	//更新新的buffer	
// 	m_nTotalPoints = nAfterBufferSize;
// // 	pShortBuffer->AttachBuffer(pBuffer,nAfterBufferSize);
// 	
// 	delete[] pOldBuffer;

}
	
void CComtradeDataBase::DeletePoints( long nBeginPos, long nEndPos, int nDataFileType)
{	
	CMemBuffer_UShort* pShortBuffer = GetMemBuffer_UShort();

	if (!pShortBuffer) 
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("当前通道数据缓存为空,无法进行删除操作"));
		return;
	}

	unsigned short* pBuffer = pShortBuffer->GetBuffer();
	int nBufferSize = pShortBuffer->GetBufferLength();

	if((nBufferSize <= 0)||(pBuffer == NULL))
	{
// 		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("当前通道数据缓存长度为0,无法进行删除操作"));
		return;
	}

	long nDeleteLength = nEndPos - nBeginPos;

	if (nDataFileType == COMTRADE_DATAFILE_TYPE_ASCII && IsAnalogData()) 
	{
		int* pLongBuffer = reinterpret_cast<int*>(pBuffer);
		int nLongBufferSize = nBufferSize / 2;
		int nAfterBufferSize = nLongBufferSize - nDeleteLength;

		int* pNewBuffer = new int[nAfterBufferSize];

		if (!pNewBuffer) 
		{
			return;
		}

		memcpy(pNewBuffer, pLongBuffer, nBeginPos * sizeof(int));
		memcpy(pNewBuffer + nBeginPos, pLongBuffer + nEndPos, (nLongBufferSize - nEndPos) * sizeof(int));

		AllocBuffer(nAfterBufferSize * 2); // 注意乘以2转换为unsigned short的大小
		memcpy(pShortBuffer->GetBuffer(), pNewBuffer, nAfterBufferSize * sizeof(int));

		delete[] pNewBuffer;
	} 
	else 
	{
		long nAfterBufferSize = nBufferSize - nDeleteLength;

		unsigned short* pNewBuffer = new unsigned short[nAfterBufferSize];

		if (!pNewBuffer) 
		{
			return ;
		}	

		memcpy(pNewBuffer, pBuffer, nBeginPos * sizeof(unsigned short));
		memcpy(pNewBuffer + nBeginPos, pBuffer + nEndPos, (nBufferSize - nEndPos) * sizeof(unsigned short));

		AllocBuffer(nAfterBufferSize);
		memcpy(pShortBuffer->GetBuffer(), pNewBuffer, nAfterBufferSize * sizeof(unsigned short));

		delete[] pNewBuffer;
	}

	m_nTotalPoints -= nDeleteLength; // 更新总点数
}


//////////////////////////////////////////////////////////////////////////
//
CComtradeDataBaseList::CComtradeDataBaseList()
{

}

CComtradeDataBaseList::~CComtradeDataBaseList()
{

}


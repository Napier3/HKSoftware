#include "StdAfx.h"
#include "WBbDataSet.h"
#include "WByteblock.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CWBbDataSet::CWBbDataSet(void)
{
	m_nDataSetID=0;;
	m_strDataSetID="";
	m_nDataSetCount=0;
	m_nGItemIndex=0;
	m_nPackDataCount=0;

	m_pWBbData = NULL;
}

CWBbDataSet::~CWBbDataSet(void)
{

}

long CWBbDataSet::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CBbDataSet::XmlReadOwn(oNode,pXmlRWKeys);

	CProtocolXmlRWKeys *pKeys = (CProtocolXmlRWKeys*)pXmlRWKeys;
	//未完成

	return 0;
}

long CWBbDataSet::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CBbDataSet::XmlWriteOwn(oXMLDoc,oElement,pXmlRWKeys);
	
	CProtocolXmlRWKeys *pKeys = (CProtocolXmlRWKeys*)pXmlRWKeys;
	//未完成

	return 0;
}

long CWBbDataSet::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{

	return 0;
}


CExBaseObject* CWBbDataSet::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	if(strClassID==CProtocolXmlRWKeys::g_pXmlRWKeys->m_strByteBlockKey)
	{
		return new CWByteBlock();
	}

	if(strClassID==CProtocolXmlRWKeys::g_pXmlRWKeys->m_strDataKey)
	{
		m_pWBbData = new CWBbData();
		return m_pWBbData;

		//return new CWBbData();
	}

	return NULL;
}

CExBaseObject* CWBbDataSet::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	
	return NULL;
}

void CWBbDataSet::InitAfterRead()
{
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = GetNext(pos);

		if (p->GetClassID() == PPCLASSID_WBBDATA)
		{
			m_pWBbData = (CWBbData *)p;
		}
	}
}

DWORD CWBbDataSet::Produce(PACKAGEBUFFERPOS &oPkgBufPos, CExBaseList *pDetail)
{// 数据集制造，默认只有1个数据
	POS pos = GetHeadPosition();
	CByteBlock *pByteBlock = NULL;

	DWORD nResult = 0;
	UINT nClassID = 0;

	// 制造字节块
	while (pos != NULL)
	{
		pByteBlock = (CByteBlock*)GetNext(pos);
		nClassID = pByteBlock->GetClassID();

		if (nClassID == PPCLASSID_WBYTEBLOCK)
		{
			nResult = pByteBlock->Produce(oPkgBufPos, pDetail);
			if (IsPpProduceError(nResult))
			{
				return nResult;
			}
		}
		else if (nClassID == PPCLASSID_WBBDATA)
		{
			//CWBbData *pDataDetail = new CWBbData();
			//pDataDetail->m_strName = pByteBlock->m_strName;
			//pDataDetail->m_strID = pByteBlock->m_strID;
			//pDetail->AddNewChild(pDataDetail);
			nResult = pByteBlock->Produce(oPkgBufPos, pDetail);
			//nResult = pByteBlock->Produce(oPkgBufPos, pDataDetail);

			if (IsPpProduceError(nResult))
			{
				return nResult;
			}
		} 			
	}	

	return nResult;
}

//////////////////////////////////////////////////////////////////////////
//复制 克隆 对比
BOOL CWBbDataSet::IsEqualOwn(CBaseObject* pObj)
{
	ASSERT (pObj == NULL);

	if (pObj == NULL)
	{
		return FALSE;
	}

	if (this == pObj)
	{
		return TRUE;
	}

	if (m_nDataSetID != ((CWBbDataSet*)pObj)->m_nDataSetID)
	{
		return FALSE;
	}

	if (m_strDataSetID != ((CWBbDataSet*)pObj)->m_strDataSetID)
	{
		return FALSE;
	}

	if (m_nDataSetCount != ((CWBbDataSet*)pObj)->m_nDataSetCount)
	{
		return FALSE;
	}

	if (m_nGItemIndex != ((CWBbDataSet*)pObj)->m_nGItemIndex)
	{
		return FALSE;
	}

	if (m_nPackDataCount != ((CWBbDataSet*)pObj)->m_nPackDataCount)
	{
		return FALSE;
	}

	return CBbDataSet::IsEqualOwn(pObj);
}

CBaseObject* CWBbDataSet::Clone()
{
	CWBbDataSet* pNew = new CWBbDataSet();
	Copy(pNew);
	return pNew;
}

BOOL CWBbDataSet::CopyOwn(CBaseObject* pDest)
{
	if (this == pDest)
	{
		return TRUE;
	}

	((CWBbDataSet*)pDest)->m_nDataSetID = m_nDataSetID;
	((CWBbDataSet*)pDest)->m_strDataSetID = m_strDataSetID;

	((CWBbDataSet*)pDest)->m_nDataSetCount = m_nDataSetCount;
	((CWBbDataSet*)pDest)->m_strDataSetCount = m_strDataSetCount;

	((CWBbDataSet*)pDest)->m_nGItemIndex = m_nGItemIndex;
	((CWBbDataSet*)pDest)->m_strGItemIndex = m_strGItemIndex;

	((CWBbDataSet*)pDest)->m_nPackDataCount = m_nPackDataCount;
	((CWBbDataSet*)pDest)->m_strPackDataCount = m_strPackDataCount;

	return CBbDataSet::CopyOwn(pDest);
}
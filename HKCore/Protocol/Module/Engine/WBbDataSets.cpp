#include "StdAfx.h"
#include "WBbDataSets.h"
#include "WByteBlock.h"
#include "WBbDataSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CWBbDataSets::CWBbDataSets(void)
{
	
}

CWBbDataSets::~CWBbDataSets(void)
{

}

long CWBbDataSets::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CBbDataSets::XmlReadOwn(oNode,pXmlRWKeys);

	return 0;
}

long CWBbDataSets::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CBbDataSets::XmlWriteOwn(oXMLDoc,oElement,pXmlRWKeys);
	return 0;
}

long CWBbDataSets::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{

	return 0;
}


CExBaseObject* CWBbDataSets::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	if(strClassID==CProtocolXmlRWKeys::g_pXmlRWKeys->m_strDataSetKey)
	{
		return new CWBbDataSet();
	}

	if(strClassID==CProtocolXmlRWKeys::g_pXmlRWKeys->m_strByteBlockKey)
	{
		return new CWByteBlock();
	}

	return NULL;
}

CExBaseObject* CWBbDataSets::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	
	return NULL;
}

DWORD CWBbDataSets::Produce(PACKAGEBUFFERPOS &oPkgBufPos, CExBaseList *pDetail)
{// 数据总集制造，默认只有1个数据集
	POS pos = GetHeadPosition();
	CByteBlock *pByteBlock = NULL;

	DWORD nResult = 0;
	UINT nClassID = 0;

	// 遍历
	while (pos != NULL)
	{
		pByteBlock = (CByteBlock*)GetNext(pos);
		nClassID = pByteBlock->GetClassID();

		if (nClassID == PPCLASSID_WBYTEBLOCK || nClassID == PPCLASSID_WBBDATASET)
		{
			nResult = pByteBlock->Produce(oPkgBufPos, pDetail);
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
BOOL CWBbDataSets::IsEqualOwn(CBaseObject* pObj)
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

	return CBbDataSets::IsEqualOwn(pObj);
}

CBaseObject* CWBbDataSets::Clone()
{
	CWBbDataSets* pNew = new CWBbDataSets();
	Copy(pNew);
	return pNew;
}

BOOL CWBbDataSets::CopyOwn(CBaseObject* pDest)
{
	if (this == pDest)
	{
		return TRUE;
	}

	return CBbDataSets::CopyOwn(pDest);
}
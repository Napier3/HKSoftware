#include "StdAfx.h"
#include "RptBkmk.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CRptBkmk::CRptBkmk(void)
{
	m_dwIndex = 0;
	m_pBkmk = NULL;
}

CRptBkmk::~CRptBkmk(void)
{
}

void CRptBkmk::GetRowCol(UINT &nRow, UINT &nCol)
{
	nCol = m_dwIndex & 0x0000FFFF;
	nRow = m_dwIndex >> 16;
	nRow = nRow & 0x0000FFFF;
}

void CRptBkmk::SetRowCol(UINT nRow,  UINT nCol)
{
	m_dwIndex = (nRow << 16) + nCol;
}

long CRptBkmk::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	m_strID = oNode.Gettext();
	m_strName = m_strID;

	GetIndexFromID();

	CGbXMLKeys *pGbXmlKeys = (CGbXMLKeys*)pXmlRWKeys;
	xml_GetAttibuteValue(pGbXmlKeys->m_strBkmkDataAttrIDKey,oNode,m_strDataAttrID);
	xml_GetAttibuteValue(pGbXmlKeys->m_strBkmkProcessKey,oNode,m_strProcess);
	xml_GetAttibuteValue(pGbXmlKeys->m_strBkmkFillModeKey,oNode,m_strFillMode);
	xml_GetAttibuteValue(pGbXmlKeys->m_strMgrpCmbnModeKey,oNode,m_strMgrpCmbnMode);

	return 0; 
}

long CRptBkmk::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	oElement.put_text(m_strID);
	//oElement->Puttext(m_strID);

	CGbXMLKeys *pGbXmlKeys = (CGbXMLKeys*)pXmlRWKeys;
	xml_SetAttributeValue(pGbXmlKeys->m_strBkmkDataAttrIDKey,oElement,m_strDataAttrID);
	xml_SetAttributeValue(pGbXmlKeys->m_strBkmkProcessKey,oElement, m_strProcess);
	xml_SetAttributeValue(pGbXmlKeys->m_strBkmkFillModeKey,oElement, m_strFillMode);

	if (m_strMgrpCmbnMode.GetLength() > 0)
	{
		xml_SetAttributeValue(pGbXmlKeys->m_strMgrpCmbnModeKey, oElement, m_strMgrpCmbnMode);
	}

	return 0;
}


//缓冲区串行化
long CRptBkmk::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer,m_dwIndex);
		BinarySerializeCalLen(oBinaryBuffer,m_strDataAttrID);
		BinarySerializeCalLen(oBinaryBuffer,m_strProcess);
		BinarySerializeCalLen(oBinaryBuffer,m_strFillMode);
		BinarySerializeCalLen(oBinaryBuffer,m_strMgrpCmbnMode);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer,m_dwIndex);
		BinarySerializeRead(oBinaryBuffer,m_strDataAttrID);
		
		if (oBinaryBuffer.m_dwVersion >= GBVERSION_1_10)
		{
			BinarySerializeRead(oBinaryBuffer,m_strProcess);
		}

		if (oBinaryBuffer.m_dwVersion >= GBVERSION_1_20)
		{
			BinarySerializeRead(oBinaryBuffer,m_strFillMode);
		}

		if (oBinaryBuffer.m_dwVersion >= GBVERSION_1_29)
		{
			BinarySerializeRead(oBinaryBuffer,m_strMgrpCmbnMode);
		}
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer,m_dwIndex);
		BinarySerializeWrite(oBinaryBuffer,m_strDataAttrID);
		BinarySerializeWrite(oBinaryBuffer,m_strProcess);
		BinarySerializeWrite(oBinaryBuffer,m_strFillMode);
		BinarySerializeWrite(oBinaryBuffer,m_strMgrpCmbnMode);
	}

	return 0;
}

//CRptBkmk的Copy先不做处理 2010-07-30 zah
BOOL CRptBkmk::CopyOwn(CBaseObject* pDest)
{
	ASSERT(pDest != NULL);

	if(this == pDest)
		return TRUE;

	((CRptBkmk*)pDest)->m_dwIndex = m_dwIndex;		//索引，标签后的数字
	((CRptBkmk*)pDest)->m_strDataAttrID = m_strDataAttrID;	
	((CRptBkmk*)pDest)->m_strProcess = m_strProcess;	
	((CRptBkmk*)pDest)->m_strFillMode = m_strFillMode;	
	((CRptBkmk*)pDest)->m_strMgrpCmbnMode = m_strMgrpCmbnMode;	
	CExBaseObject::CopyOwn(pDest);

	return TRUE;
}

CBaseObject* CRptBkmk::Clone()
{
	CRptBkmk *pNew = new CRptBkmk();
	Copy(pNew);
	return pNew;
}

CExBaseList* _FindRptBkmkByID(CExBaseList *pList, const CString &strID, CExBaseList *pListDest)
{
	ASSERT (pList != NULL);
	CRptBkmk *pBkmk = NULL;
	UINT nClassID = 0;
	
	if (pList->IsBaseObject())
	{
		return NULL;
	}

	nClassID = pList->GetClassID();

	if (nClassID == RPTCLASSID_RPTDATA  || nClassID == RPTCLASSID_RPTAREA)
	{
		pBkmk = (CRptBkmk*)pList->FindByID(strID);
		pListDest->AddTail(pBkmk);
	}
	else
	{
		POS pos = pList->GetHeadPosition();
		CExBaseList *pSubList = NULL;

		while (pos != NULL)
		{
			pSubList = (CExBaseList*)pList->GetNext(pos);
			_FindRptBkmkByID(pSubList, strID, pListDest);
		}
	}

	return pListDest;
}


CWordBkmk::CWordBkmk()
{
	m_pBkmk = NULL;
}

CWordBkmk::~CWordBkmk()
{

}


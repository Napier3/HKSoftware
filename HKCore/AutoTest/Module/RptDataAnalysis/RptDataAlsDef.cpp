//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//RptDataAlsDef.cpp  CRptDataAlsDef


#include "stdafx.h"
#include "RptDataAlsDef.h"

CRptDataAlsDef::CRptDataAlsDef()
{
	//初始化属性

	//初始化成员变量
}

CRptDataAlsDef::~CRptDataAlsDef()
{
}

long CRptDataAlsDef::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CRptAnalysisXmlRWKeys *pXmlKeys = (CRptAnalysisXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strNameKey, oNode, m_strName);
	xml_GetAttibuteValue(pXmlKeys->m_strItem_PathKey, oNode, m_strItemPath);
	xml_GetAttibuteValue(pXmlKeys->m_strId_ValueKey, oNode, m_strValueID);

	SplitItemPath();

	return 0;
}

long CRptDataAlsDef::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CRptAnalysisXmlRWKeys *pXmlKeys = (CRptAnalysisXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strNameKey, oElement, m_strName);
	xml_SetAttributeValue(pXmlKeys->m_strItem_PathKey, oElement, m_strItemPath);
	xml_SetAttributeValue(pXmlKeys->m_strId_ValueKey, oElement, m_strValueID);
	return 0;
}

long CRptDataAlsDef::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strName);
		BinarySerializeCalLen(oBinaryBuffer, m_strItemPath);
		BinarySerializeCalLen(oBinaryBuffer, m_strValueID);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strName);
		BinarySerializeRead(oBinaryBuffer, m_strItemPath);
		BinarySerializeRead(oBinaryBuffer, m_strValueID);

		SplitItemPath();
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strName);
		BinarySerializeWrite(oBinaryBuffer, m_strItemPath);
		BinarySerializeWrite(oBinaryBuffer, m_strValueID);
	}
	return 0;
}

void CRptDataAlsDef::InitAfterRead()
{
}

BOOL CRptDataAlsDef::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CRptDataAlsDef *p = (CRptDataAlsDef*)pObj;

	if(m_strName != p->m_strName)
	{
		return FALSE;
	}

	if(m_strItemPath != p->m_strItemPath)
	{
		return FALSE;
	}

	if(m_strValueID != p->m_strValueID)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CRptDataAlsDef::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CRptDataAlsDef *p = (CRptDataAlsDef*)pDest;

	p->m_strName = m_strName;
	p->m_strItemPath = m_strItemPath;
	p->m_strValueID = m_strValueID;
	return TRUE;
}

CBaseObject* CRptDataAlsDef::Clone()
{
	CRptDataAlsDef *p = new CRptDataAlsDef();
	Copy(p);
	return p;
}

void CRptDataAlsDef::SplitItemPath()
{
	long nPos = 0;
	long nPrev = 0;
	long nLen = m_strItemPath.GetLength();

	while (TRUE)
	{
		nPos = m_strItemPath.Find('$', nPrev);

		if (nPos > 0)
		{
			m_astrItemID.Add(m_strItemPath.Mid(nPrev, nPos-nPrev));
		}
		else
		{
			m_astrItemID.Add(m_strItemPath.Mid(nPrev));
			break;
		}

		nPrev = nPos+1;
	}
}

BOOL CRptDataAlsDef::MatchItem(CExBaseObject *pItem)
{
	long nIndex = m_astrItemID.GetSize() - 1;
	BOOL bRet = TRUE;

	if (nIndex < 0 || pItem == NULL)
	{
		return FALSE;
	}

	while (nIndex >= 0 && pItem != NULL)
	{
		if (pItem == NULL)
		{
			break;
		}

		if (pItem->m_strID != m_astrItemID.GetAt(nIndex))
		{
			bRet = FALSE;
			break; 
		}

		nIndex--;
		pItem = (CExBaseObject *)pItem->GetParent();
	}

	return bRet;
}


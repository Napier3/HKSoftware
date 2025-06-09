#include "StdAfx.h"
#include "RptArea.h"
#include "RptBkmk.h"

#include "../../XLanguageResourceAts.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CRptArea::CRptArea(void)
{
	m_pBkmkBegin = NULL;
	m_pBkmkEnd = NULL;
	m_strName = g_sLangTxt_AreaDefin/*L"区域定义"*/;
	m_strID = L"Area";
}

CRptArea::~CRptArea(void)
{
	DeleteAll();
}

//新建标签对象,根据特定的规则自动生成IRptBkmk的标签
// CExBaseObject* CRptArea::AddNew()
// {
// 	CRptBkmk *pRptBkmk = new CRptBkmk();
// 	ASSERT(pRptBkmk != NULL);
// 	AddTail(pRptBkmk);
// 	pRptBkmk->SetParent(this);
// 	
// 	return pRptBkmk;
// }
// 
// CExBaseObject* CRptArea::AddNew2(const CString  strRptBkmk)
// {
// 	CRptBkmk *pRptBkmk = new CRptBkmk();
// 	ASSERT(pRptBkmk != NULL);
// 
// 	//pRptBkmk->m_strName = strRptBkmk;
// 	pRptBkmk->m_strID = strRptBkmk;
// 	AddTail(pRptBkmk);
// 	pRptBkmk->SetParent(this);
// 
// 	return pRptBkmk;
// }

//ReadXML && WriteXML
long CRptArea::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);
	//CGbXMLKeys *pKeys = (CGbXMLKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(CGbXMLKeys::AreaTypeKey(), oNode, m_strAreaType);

	return 0;
}

CExBaseObject* CRptArea::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CGbXMLKeys *pKeys = (CGbXMLKeys*)pXmlRWKeys;

	if (strClassID == pKeys->m_strBkmkKey)
	{
		return new CRptBkmk();
	}
	else
	{
		return NULL;
	}

}

long CRptArea::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
		
	xml_SetAttributeValue(CGbXMLKeys::AreaTypeKey(), oElement, m_strAreaType);

	return 0;
}

long CRptArea::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer,m_strAreaType);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		if (oBinaryBuffer.m_dwVersion >= GBVERSION_1_28)
		{
			BinarySerializeRead(oBinaryBuffer,m_strAreaType);
		}
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer,m_strAreaType);
	}

	return 0;
}

CExBaseObject* CRptArea::CreateNewChild(long nClassID)
{
	if(nClassID == RPTCLASSID_RPTBKMK)
	{
		return new CRptBkmk();
	}

	return NULL;
}

void CRptArea::InitAfterRead()
{
	if (GetCount() != 2)
	{
		return;
	}

	m_pBkmkBegin = (CRptBkmk*)GetHead();
	m_pBkmkEnd = (CRptBkmk*)GetTail();

	if (m_pBkmkBegin == NULL || m_pBkmkEnd == NULL)
	{
        CLogPrint::LogFormatString(NULL, XLOGLEVEL_ERROR, _T("Report area \"%s\" error"), m_strID.GetString());
	}
}


CBaseObject* CRptArea::Clone()
{
	CRptArea *pNew = new CRptArea();
	Copy(pNew);
	return pNew;
}

BOOL CRptArea::CopyOwn(CBaseObject* pDest)
{
	ASSERT(pDest != NULL);

	if(this == pDest)
		return TRUE;

	((CRptArea*)pDest)->m_strAreaType = m_strAreaType;

	return TRUE;
}

void CRptArea::ClearDWData()
{
	POS pos = GetHeadPosition();
	CRptBkmk *pBkmk = NULL;

	while (pos != NULL)
	{
		pBkmk = (CRptBkmk*)GetNext(pos);
		pBkmk->m_dwItemData = 0;
	}
}

BOOL CRptArea::IsRptAdjustArea()
{
	if (m_strAreaType.GetLength() == 0)
	{
		return TRUE;
	}

	return m_strAreaType == RPT_AREA_TYPE_ADJUST;
}

BOOL CRptArea::IsRptMgrpCmbArea()
{
	return m_strAreaType == RPT_AREA_TYPE_MGRP;
}

void CRptArea::SetRptAdjustArea()
{
	m_strAreaType = RPT_AREA_TYPE_ADJUST;
}

void CRptArea::SetRptMgrpCmbArea()
{
	m_strAreaType = RPT_AREA_TYPE_MGRP;
}

void CRptArea::SetRptAreaType(const CString &strType)
{
	m_strAreaType = strType;
}

void CRptArea::DeleteArea()
{
	DeleteAll();
	m_pBkmkBegin = NULL;
	m_pBkmkEnd = NULL;
}

void CRptArea::InitAreaBkmkID(CRptBkmk *pBkmk, DWORD &dwBkmkIndex)
{
	if (m_strAreaType.GetLength() > 0)
	{
        pBkmk->m_strID.Format(_T("%s_Bkmk_%d"), m_strAreaType.GetString(), dwBkmkIndex);
	}
	else
	{
		pBkmk->m_strID.Format(_T("Bkmk_%d"), dwBkmkIndex);
	}
}


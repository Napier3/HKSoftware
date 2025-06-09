//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//RptTemp_Items.cpp  CRptTemp_Items


#include "stdafx.h"
#include "RptTemp_Items.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CRptTemp_Items::CRptTemp_Items()
{
	//初始化属性
	m_nRpt_Title = 0;
	m_ntitle_level = 0;

	//初始化成员变量
	m_bHasGen = FALSE;
	m_pItems = NULL;
}

CRptTemp_Items::~CRptTemp_Items()
{
	m_oList.RemoveAll();
}

long CRptTemp_Items::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CTestMacroRptTemplateXmlRWKeys *pXmlKeys = (CTestMacroRptTemplateXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strRpt_TitleKey, oNode, m_nRpt_Title);
	xml_GetAttibuteValue(pXmlKeys->m_strTitle_LevelKey, oNode, m_ntitle_level);
	return 0;
}

long CRptTemp_Items::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CTestMacroRptTemplateXmlRWKeys *pXmlKeys = (CTestMacroRptTemplateXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strRpt_TitleKey, oElement, m_nRpt_Title);
	xml_SetAttributeValue(pXmlKeys->m_strTitle_LevelKey, oElement, m_ntitle_level);
	return 0;
}

long CRptTemp_Items::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_nRpt_Title);
		BinarySerializeCalLen(oBinaryBuffer, m_ntitle_level);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_nRpt_Title);
		BinarySerializeRead(oBinaryBuffer, m_ntitle_level);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_nRpt_Title);
		BinarySerializeWrite(oBinaryBuffer, m_ntitle_level);
	}
	return 0;
}

void CRptTemp_Items::InitAfterRead()
{
}

BOOL CRptTemp_Items::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CRptTemp_Items *p = (CRptTemp_Items*)pObj;

	if(m_nRpt_Title != p->m_nRpt_Title)
	{
		return FALSE;
	}

	if(m_ntitle_level != p->m_ntitle_level)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CRptTemp_Items::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CRptTemp_Items *p = (CRptTemp_Items*)pDest;

	p->m_nRpt_Title = m_nRpt_Title;
	p->m_ntitle_level = m_ntitle_level;
	return TRUE;
}

CBaseObject* CRptTemp_Items::Clone()
{
	CRptTemp_Items *p = new CRptTemp_Items();
	Copy(p);
	return p;
}

CBaseObject* CRptTemp_Items::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CRptTemp_Items *p = new CRptTemp_Items();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CRptTemp_Items::CanPaste(UINT nClassID)
{
	if (nClassID == MNGRCLASSID_CRPTTEMP_ITEMS)
	{
		return TRUE;
	}

	if (nClassID == MNGRCLASSID_CRPTTEMP_MACROCHARITEMS)
	{
		return TRUE;
	}

	if (nClassID == MNGRCLASSID_CRPTTEMP_MACROTEST)
	{
		return TRUE;
	}

	if (nClassID == MNGRCLASSID_CRPTTEMP_REPORTTEMPLATEDEF)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CRptTemp_Items::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CTestMacroRptTemplateXmlRWKeys *pXmlKeys = (CTestMacroRptTemplateXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCRptTemp_ItemsKey)
	{
		pNew = new CRptTemp_Items();
	}
//	else if (strClassID == pXmlKeys->m_strCRptTemp_MacroCharItemsKey)
//	{
//		pNew = new CRptTemp_MacroCharItems();
//	}
//	else if (strClassID == pXmlKeys->m_strCRptTemp_MacroTestKey)
//	{
//		pNew = new CRptTemp_MacroTest();
//	}
	else if (strClassID == pXmlKeys->m_strCRptTemp_ReportTemplateKey)
	{
		pNew = new CRptTemp_ReportTemplate();
	}

	return pNew;
}

CExBaseObject* CRptTemp_Items::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == MNGRCLASSID_CRPTTEMP_ITEMS)
	{
		pNew = new CRptTemp_Items();
	}
//	else if (nClassID == MNGRCLASSID_CRPTTEMP_MACROCHARITEMS)
//	{
//		pNew = new CRptTemp_MacroCharItems();
//	}
//	else if (nClassID == MNGRCLASSID_CRPTTEMP_MACROTEST)
//	{
//		pNew = new CRptTemp_MacroTest();
//	}
	else if (nClassID == MNGRCLASSID_CRPTTEMP_REPORTTEMPLATE)
	{
		pNew = new CRptTemp_ReportTemplate();
	}

	return pNew;
}

long CRptTemp_Items::GetMacroTestCount()
{
	long nCount = 0;
	POS pos = GetHeadPosition();
	CExBaseObject *pObj = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		pObj = GetNext(pos);
		nClassID = pObj->GetClassID();

		if (nClassID != MNGRCLASSID_CRPTTEMP_MACROTEST)
		{
			continue;
		}

		nCount++;
	}

	return nCount;
}

//CRptTemp_MacroTest* CRptTemp_Items::GetMacroTestByIndex(long nIndex)
//{
//	CRptTemp_MacroTest* pFind = NULL;
//	long nFind = 0;
//	POS pos = GetHeadPosition();
//	CExBaseObject *pObj = NULL;
//	UINT nClassID = 0;

//	while (pos != NULL)
//	{
//		pObj = GetNext(pos);
//		nClassID = pObj->GetClassID();

//		if (nClassID != MNGRCLASSID_CRPTTEMP_MACROTEST)
//		{
//			continue;
//		}

//		if (nFind == nIndex)
//		{
//			pFind = (CRptTemp_MacroTest*)pObj;
//			break;
//		}

//		nFind++;
//	}

//	return pFind;
//}

void CRptTemp_Items::AddTailToIndexList(CExBaseObject *pObj)
{
	m_oList.AddTail(pObj);
}

void CRptTemp_Items::RemoveIndexList(CExBaseObject *pObj)
{
	m_oList.Remove(pObj);
}

BOOL CRptTemp_Items::IsAncestorOf(CRptTemp_Items *pChildItems)
{
	if (pChildItems == NULL)
	{
		return FALSE;
	}

	CExBaseObject *pParent = pChildItems;
	BOOL bRet = FALSE;

	while (pParent != NULL)
	{
		if (pParent == this)
		{
			bRet = TRUE;
			break;
		}

		pParent = (CExBaseObject *)pParent->GetParent();
	}

	return bRet;
}

//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Tags.cpp  CTags


#include "stdafx.h"
#include "Tags.h"

#ifndef NOT_USE_XLANGUAGE
#include "../XLanguage/XLanguageResource.h"
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CTags::CTags()
{
	//初始化属性

	//初始化成员变量
}

CTags::~CTags()
{
}

long CTags::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CDataMngrXmlRWKeys *pXmlKeys = (CDataMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strIDKey, oNode, m_strID);
	return 0;
}

long CTags::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CDataMngrXmlRWKeys *pXmlKeys = (CDataMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strIDKey, oElement, m_strID);
	return 0;
}

long CTags::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strID);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strID);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strID);
	}
	return 0;
}

void CTags::InitAfterRead()
{
}

BOOL CTags::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CTags *p = (CTags*)pObj;

	if(m_strID != p->m_strID)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CTags::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CTags *p = (CTags*)pDest;

	p->m_strID = m_strID;
	return TRUE;
}

CBaseObject* CTags::Clone()
{
	CTags *p = new CTags();
	Copy(p);
	return p;
}

long CTags::InitListCtrlColumns(CListCtrl *pListCtrl)
{
#ifdef NOT_USE_XLANGUAGE
	pListCtrl->InsertColumn(0, _T("编号"));
#else
	pListCtrl->InsertColumn(0, g_sLangTxt_Index/*_T("编号")*/);
#endif

	pListCtrl->SetColumnWidth(0, 80);
	pListCtrl->InsertColumn(1, _T("ID"));
	pListCtrl->SetColumnWidth(1, 80);
	pListCtrl->SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	return 0;
}

long CTags::UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex)
{
	CString strTemp;
	strTemp.Format(_T("%d"), lItemIndex+1);
	pListCtrl->SetItemText(lItemIndex, 0, strTemp);
	pListCtrl->SetItemText(lItemIndex, 1, m_strID);
	pListCtrl->SetItemData(lItemIndex, (DWORD)this);
	return 0;
}

CExBaseObject* CTags::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CDataMngrXmlRWKeys *pXmlKeys = (CDataMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCTagKey)
	{
		pNew = new CTag();
	}

	return pNew;
}

CExBaseObject* CTags::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == DTMCLASSID_CTAG)
	{
		pNew = new CTag();
	}

	return pNew;
}

CTag* CTags::FindByDataType(const CString &strDataType)
{
	POS pos = GetHeadPosition();
	CTag *pTag = NULL;
	CTag *pFind = NULL;

	while (pos != NULL)
	{
		pTag = (CTag *)GetNext(pos);

		if (pTag->m_strDataType == strDataType)
		{
			pFind = pTag;
			break;
		}
	}

	return pFind;
}

CTag* CTags::AddNew(const CString &strID, const CString &strValue, const CString &strDataType)
{
	CTag *pTag = new CTag();
	pTag->SetParent(this);
	pTag->m_strID  =strID;
	pTag->m_strValue = strValue;
	pTag->m_strDataType = strDataType;
	AddTail(pTag);
	return pTag;
}

CTag* CTags::FindByTagID(const CString &strTagID)
{
	POS pos = GetHeadPosition();
	CTag *pTag = NULL;
	CTag *pFind = NULL;

	while (pos != NULL)
	{
		pTag = (CTag *)GetNext(pos);

		if (pTag->m_strID == strTagID)
		{
			pFind = pTag;
			break;
		}
	}

	return pFind;
}

CTag* CTags::FindByTagIDIcmp(const CString &strTagID)
{
	POS pos = GetHeadPosition();
	CTag *pTag = NULL;
	CTag *pFind = NULL;
	CString strSrc = strTagID;
	strSrc.MakeLower();
	CString strTemp;

	while (pos != NULL)
	{
		pTag = (CTag *)GetNext(pos);
		strTemp = pTag->m_strID;
		strTemp.MakeLower();

		if (strTemp == strSrc)
		{
			pFind = pTag;
			break;
		}
	}

	return pFind;
}

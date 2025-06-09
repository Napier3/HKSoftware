//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//DataType.cpp  CDataType


#include "stdafx.h"
#include "DataType.h"

#ifndef NOT_USE_XLANGUAGE
#include "../XLanguage/XLanguageResource.h"
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CDataType::CDataType()
{
	//初始化属性

	//初始化成员变量
}

CDataType::~CDataType()
{
}

long CDataType::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CDataMngrXmlRWKeys *pXmlKeys = (CDataMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CDataType::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CDataMngrXmlRWKeys *pXmlKeys = (CDataMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CDataType::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
	}
	else if(oBinaryBuffer.IsReadMode())
	{
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
	}
	return 0;
}

void CDataType::InitAfterRead()
{
}

BOOL CDataType::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CDataType *p = (CDataType*)pObj;

	return TRUE;
}

BOOL CDataType::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CDataType *p = (CDataType*)pDest;

	return TRUE;
}

CBaseObject* CDataType::Clone()
{
	CDataType *p = new CDataType();
	Copy(p);
	return p;
}

CBaseObject* CDataType::CloneEx(BOOL bCopyOwn,BOOL bCopyChildren)
{
	CDataType *p = new CDataType();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

long CDataType::InitListCtrlColumns(CListCtrl *pListCtrl)
{
#ifdef NOT_USE_XLANGUAGE
	pListCtrl->InsertColumn(0, _T("编号"));
#else
	pListCtrl->InsertColumn(0, g_sLangTxt_Index/*_T("编号")*/);
#endif
	pListCtrl->SetColumnWidth(0, 80);
	pListCtrl->InsertColumn(1, _T("Name"));
	pListCtrl->SetColumnWidth(1, 80);
	pListCtrl->InsertColumn(2, _T("ID"));
	pListCtrl->SetColumnWidth(2, 80);
	pListCtrl->SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	return 0;
}

long CDataType::UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex)
{
	CString strTemp;
	strTemp.Format(_T("%d"), lItemIndex+1);
	pListCtrl->SetItemText(lItemIndex, 0, strTemp);
	pListCtrl->SetItemText(lItemIndex, 1, m_strName);
	pListCtrl->SetItemText(lItemIndex, 2, m_strID);
	pListCtrl->SetItemData(lItemIndex, (DWORD)this);
	return 0;
}

CExBaseObject* CDataType::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CDataMngrXmlRWKeys *pXmlKeys = (CDataMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCDataTypeValueKey)
	{
		pNew = new CDataTypeValue();
	}

	return pNew;
}

CExBaseObject* CDataType::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == DTMCLASSID_CDATATYPEVALUE)
	{
		pNew = new CDataTypeValue();
	}

	return pNew;
}

CDataTypeValue* CDataType::FindByIndex(const CString &strIndex)
{
	CDataTypeValue *p = NULL;
	CDataTypeValue *pFind = NULL;
	POS pos = GetHeadPosition();
	long nIndex1 = 0,nIndex2 = 0;
	nIndex2 = CString_To_long(strIndex);

	if (strIndex.IsEmpty())
	{
		return NULL;
	}

	long nLenth = strIndex.GetLength();
	unsigned short uValue = 0;

	for (int nIndex = 0;nIndex<nLenth;nIndex++)
	{
		uValue = strIndex.GetAt(nIndex);

// 		if (uValue == '-')
// 		{
// 			continue;
// 		}

		if (uValue == '.')
		{
			continue;
		}

		if ((uValue >= '0')&&(uValue <= '9'))
		{
			continue;
		}

		return NULL;
	}
	
	while (pos != NULL)
	{
		p = (CDataTypeValue*)GetNext(pos);
		nIndex1 = CString_To_long(p->m_strIndex);//zhouhj 2024.6.26 防止传进来的字符串为浮点或其它
		
		if (nIndex1 == nIndex2)
		{
			pFind = p;
			break;
		}
	}
	
	return pFind;
}


CDataTypeValue* CDataType::FindByIndex(long nIndex)
{
	POS pos = GetHeadPosition();
	CDataTypeValue *pValue = NULL;
	CDataTypeValue *pFind = NULL;
	CString strIndex;
	strIndex.Format(_T("%d"), nIndex);

	while (pos != NULL)
	{
		pValue = (CDataTypeValue*)GetNext(pos);

		if (pValue->m_strIndex == strIndex)
		{
			pFind = pValue;
			break;
		}
	}

	return pFind;
}

CDataTypeValue* CDataType::AddNewValue(const CString &strName, const CString &strID, long nIndex)
{
	CDataTypeValue *pValue = new CDataTypeValue();
	pValue->m_strName = strName;
	pValue->m_strID = strID;
	pValue->m_strIndex.Format(_T("%d"), nIndex);
	AddNewChild(pValue);
	return pValue;
}

CDataTypeValue* CDataType::AddNewValue(const CString &strName, const CString &strID, const CString &strIndex)
{
	CDataTypeValue *pValue = new CDataTypeValue();
	pValue->m_strName = strName;
	pValue->m_strID = strID;
	pValue->m_strIndex = strIndex;
	AddNewChild(pValue);
	return pValue;
}

CDataTypeValue* CDataType::AddNewValue(const CString &strID, long nIndex)
{
	return AddNewValue(strID, strID, nIndex);
}

CDataTypeValue* CDataType::AddNewValue(const CString &strID, const CString &strIndex)
{
	return AddNewValue(strID, strID, strIndex);
}


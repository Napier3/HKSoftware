//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//ShortDatas.cpp  CShortDatas


#include "stdafx.h"
#include "ShortDatas.h"

#ifndef NOT_USE_XLANGUAGE
#include "../XLanguage/XLanguageResource.h"
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


CShortDatas::CShortDatas()
{
	//初始化属性

	//初始化成员变量
}

CShortDatas::~CShortDatas()
{
}

long CShortDatas::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CDataMngrXmlRWKeys *pXmlKeys = (CDataMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CShortDatas::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CDataMngrXmlRWKeys *pXmlKeys = (CDataMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CShortDatas::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CShortDatas::InitAfterRead()
{
}

BOOL CShortDatas::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CShortDatas *p = (CShortDatas*)pObj;

	return TRUE;
}

BOOL CShortDatas::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CShortDatas *p = (CShortDatas*)pDest;

	return TRUE;
}

CBaseObject* CShortDatas::Clone()
{
	CShortDatas *p = new CShortDatas();
	Copy(p);
	return p;
}

long CShortDatas::InitListCtrlColumns(CListCtrl *pListCtrl)
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

long CShortDatas::UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex)
{
	CString strTemp;
	strTemp.Format(_T("%d"), lItemIndex+1);
	pListCtrl->SetItemText(lItemIndex, 0, strTemp);
	pListCtrl->SetItemText(lItemIndex, 1, m_strName);
	pListCtrl->SetItemText(lItemIndex, 2, m_strID);
	pListCtrl->SetItemData(lItemIndex, (DWORD)this);
	return 0;
}

CExBaseObject* CShortDatas::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CDataMngrXmlRWKeys *pXmlKeys = (CDataMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCShortDataKey)
	{
		pNew = new CShortData();
	}

	return pNew;
}

CExBaseObject* CShortDatas::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == DTMCLASSID_CSHORTDATA)
	{
		pNew = new CShortData();
	}

	return pNew;
}

void  CShortDatas::AppendValues( CValues *pValues)
{
	CShortData *pData = NULL;
	POS pos = GetHeadPosition();
	CValue *pValue = NULL;

	while (pos != NULL)
	{
		pData = (CShortData*)GetNext(pos);
		pValues->AddValue(pData->m_strID, pData->m_strValue);
	}
}

CValues* CShortDatas::GetValues()
{
	CValues *pValues = new CValues();
	POS pos = GetHeadPosition();
	CShortData *pData = NULL;

	while (pos != NULL)
	{
		pData = (CShortData *)GetNext(pos);
		pValues->AddNew(pData->m_strID, pData->m_strName, pData->m_strValue);
	}

	return pValues;
}

CShortData* CShortDatas::AddNew2(const CString &strName,const CString &strID, const CString &strUnit, const CString &strDataTypeID
								 , const CString &strValue, LONG nReserved,const CString &strFormat,const CString &strRemark, BOOL bAddSame)
{
	CShortData *pData = NULL;
	
	if (bAddSame)
	{
		pData = new CShortData();
		AddNewChild(pData);
	}
	else
	{
		pData = (CShortData *)FindByID(strID);

		if (pData == NULL)
		{
			pData = new CShortData();
			AddNewChild(pData);
		}
	}

	pData->m_strName = strName;
	pData->m_strID = strID;
	pData->m_strUnit = strUnit;
	pData->m_strDataTypeID = strDataTypeID;
	pData->m_strValue = strValue;
	pData->m_strFormat = strFormat;
	pData->m_strRemark = strRemark;
	pData->m_nReserved = nReserved;
	return pData;
}

void CShortDatas::ResetDatas()
{
	POS pos = GetHeadPosition();
	CShortData *pData = NULL;

	while (pos != NULL)
	{
		pData = (CShortData *)GetNext(pos);
		pData->ResetData();
	}

}

void CShortDatas::StringSerialize(CStringSerializeBuffer &oBinaryBuffer)
{
	POS pos = GetHeadPosition();
	CShortData *pData = NULL;

	while (pos != NULL)
	{
		pData = (CShortData *)GetNext(pos);
		pData->StringSerialize(oBinaryBuffer);
	}
}


void CShortDatas::Parser(CEquationBuffer *pEquation)
{
	CShortData* pObject = NULL;
	POS pos = GetHeadPosition();
	CString strValue;

	while (pos != NULL)
	{
		pObject = (CShortData*)GetNext(pos);

		if (pObject != NULL)
		{
			strValue = _T("");
			pEquation->ParseString(pObject->m_strID, strValue);

			if(strValue.GetLength() > 0)
			{
				pObject->m_strValue = strValue;
			}
		}
	}
}

//2021-8-10  lijunqing
void CShortDatas::InitDatasValue(CShortDatas *pSrcDatas)
{
	CShortData* pData = NULL;
	CShortData* pFind = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		pData = (CShortData*)GetNext(pos);
		pFind = (CShortData*)pSrcDatas->FindByID(pData->m_strID);

		if (pFind != NULL)
		{
			pData->m_strValue = pFind->m_strValue;
		}
	}
}

void CShortDatas::SetDataValue(const CString &strID, const CString &strValue, BOOL bAddNew)
{
	CShortData* pData = NULL;
	pData = (CShortData*)FindByID(strID);

	if (pData == NULL)
	{
		if (bAddNew)
		{
			return;
		}

		pData = new CShortData();
		pData->m_strID = strID;
		pData->m_strName = strID;
		AddNewChild(pData);
	}

	pData->m_strValue = strValue;
}


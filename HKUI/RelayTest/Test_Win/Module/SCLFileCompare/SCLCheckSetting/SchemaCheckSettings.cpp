//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SchemaCheckSettings.cpp  CSchemaCheckSettings


#include "stdafx.h"
#include "SchemaCheckSettings.h"

CSchemaCheckSettings::CSchemaCheckSettings()
{
	//初始化属性

	//初始化成员变量
}

CSchemaCheckSettings::~CSchemaCheckSettings()
{
}

long CSchemaCheckSettings::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CCSchemaCheckSettingObjectXmlRWKeys *pXmlKeys = (CCSchemaCheckSettingObjectXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CSchemaCheckSettings::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CCSchemaCheckSettingObjectXmlRWKeys *pXmlKeys = (CCSchemaCheckSettingObjectXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CSchemaCheckSettings::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
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

void CSchemaCheckSettings::InitAfterRead()
{
}

BOOL CSchemaCheckSettings::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CSchemaCheckSettings *p = (CSchemaCheckSettings*)pObj;

	return TRUE;
}

BOOL CSchemaCheckSettings::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CSchemaCheckSettings *p = (CSchemaCheckSettings*)pDest;

	return TRUE;
}

CBaseObject* CSchemaCheckSettings::Clone()
{
	CSchemaCheckSettings *p = new CSchemaCheckSettings();
	Copy(p);
	return p;
}

long CSchemaCheckSettings::InitListCtrlColumns(CListCtrl *pListCtrl)
{
	pListCtrl->InsertColumn(0, _T("编号"));
	pListCtrl->SetColumnWidth(0, 80);
	pListCtrl->SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	return 0;
}

long CSchemaCheckSettings::UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex)
{
	CString strTemp;
	strTemp.Format(_T("%d"), lItemIndex+1);
	pListCtrl->SetItemText(lItemIndex, 0, strTemp);
	pListCtrl->SetItemData(lItemIndex, (WORD)this);
	return 0;
}

BOOL CSchemaCheckSettings::CanPaste(UINT nClassID)
{
	if (nClassID == MNGRCLASSID_CSCHEMACHECKSETTING)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CSchemaCheckSettings::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CCSchemaCheckSettingObjectXmlRWKeys *pXmlKeys = (CCSchemaCheckSettingObjectXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCSchemaCheckSettingKey)
	{
		pNew = new CSchemaCheckSetting();
	}

	return pNew;
}

CExBaseObject* CSchemaCheckSettings::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == MNGRCLASSID_CSCHEMACHECKSETTING)
	{
		pNew = new CSchemaCheckSetting();
	}

	return pNew;
}

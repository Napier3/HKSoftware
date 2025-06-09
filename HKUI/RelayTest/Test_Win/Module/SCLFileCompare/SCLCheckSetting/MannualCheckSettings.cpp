//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//MannualCheckSettings.cpp  CMannualCheckSettings


#include "stdafx.h"
#include "MannualCheckSettings.h"

CMannualCheckSettings::CMannualCheckSettings()
{
	//初始化属性

	//初始化成员变量
}

CMannualCheckSettings::~CMannualCheckSettings()
{
}

long CMannualCheckSettings::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CCSchemaCheckSettingObjectXmlRWKeys *pXmlKeys = (CCSchemaCheckSettingObjectXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CMannualCheckSettings::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CCSchemaCheckSettingObjectXmlRWKeys *pXmlKeys = (CCSchemaCheckSettingObjectXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CMannualCheckSettings::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CMannualCheckSettings::InitAfterRead()
{
}

BOOL CMannualCheckSettings::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CMannualCheckSettings *p = (CMannualCheckSettings*)pObj;

	return TRUE;
}

BOOL CMannualCheckSettings::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CMannualCheckSettings *p = (CMannualCheckSettings*)pDest;

	return TRUE;
}

CBaseObject* CMannualCheckSettings::Clone()
{
	CMannualCheckSettings *p = new CMannualCheckSettings();
	Copy(p);
	return p;
}

long CMannualCheckSettings::InitListCtrlColumns(CListCtrl *pListCtrl)
{
	pListCtrl->InsertColumn(0, _T("编号"));
	pListCtrl->SetColumnWidth(0, 80);
	pListCtrl->SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	return 0;
}

long CMannualCheckSettings::UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex)
{
	CString strTemp;
	strTemp.Format(_T("%d"), lItemIndex+1);
	pListCtrl->SetItemText(lItemIndex, 0, strTemp);
	pListCtrl->SetItemData(lItemIndex, (WORD)this);
	return 0;
}

BOOL CMannualCheckSettings::CanPaste(UINT nClassID)
{
	if (nClassID == MNGRCLASSID_CMANNUALCHECKSETTING)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CMannualCheckSettings::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CCSchemaCheckSettingObjectXmlRWKeys *pXmlKeys = (CCSchemaCheckSettingObjectXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCMannualCheckSettingKey)
	{
		pNew = new CMannualCheckSetting();
	}

	return pNew;
}

CExBaseObject* CMannualCheckSettings::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == MNGRCLASSID_CMANNUALCHECKSETTING)
	{
		pNew = new CMannualCheckSetting();
	}

	return pNew;
}

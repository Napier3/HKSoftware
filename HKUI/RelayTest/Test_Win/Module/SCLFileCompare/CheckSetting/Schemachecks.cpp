//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Schemachecks.cpp  Schemachecks


#include "stdafx.h"
#include "Schemachecks.h"

Schemachecks::Schemachecks()
{
	//初始化属性

	//初始化成员变量
}

Schemachecks::~Schemachecks()
{
}

long Schemachecks::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CSCLCheckSettingMngrXmlRWKeys *pXmlKeys = (CSCLCheckSettingMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long Schemachecks::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CSCLCheckSettingMngrXmlRWKeys *pXmlKeys = (CSCLCheckSettingMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long Schemachecks::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void Schemachecks::InitAfterRead()
{
}

BOOL Schemachecks::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	Schemachecks *p = (Schemachecks*)pObj;

	return TRUE;
}

BOOL Schemachecks::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	Schemachecks *p = (Schemachecks*)pDest;

	return TRUE;
}

CBaseObject* Schemachecks::Clone()
{
	Schemachecks *p = new Schemachecks();
	Copy(p);
	return p;
}

long Schemachecks::InitListCtrlColumns(CListCtrl *pListCtrl)
{
	pListCtrl->InsertColumn(0, _T("编号"));
	pListCtrl->SetColumnWidth(0, 80);
	pListCtrl->SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	return 0;
}

long Schemachecks::UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex)
{
	CString strTemp;
	strTemp.Format(_T("%d"), lItemIndex+1);
	pListCtrl->SetItemText(lItemIndex, 0, strTemp);
	pListCtrl->SetItemData(lItemIndex, (WORD)this);
	return 0;
}

BOOL Schemachecks::CanPaste(UINT nClassID)
{
	if (nClassID == MNGRCLASSID_SCHEMACHECK)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* Schemachecks::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CSCLCheckSettingMngrXmlRWKeys *pXmlKeys = (CSCLCheckSettingMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strSchemacheckKey)
	{
		pNew = new Schemacheck();
	}

	return pNew;
}

CExBaseObject* Schemachecks::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == MNGRCLASSID_SCHEMACHECK)
	{
		pNew = new Schemacheck();
	}

	return pNew;
}

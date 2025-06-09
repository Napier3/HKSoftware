//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttSafetyMsgCfgs.cpp  CSttSafetyMsgCfgs


#include "stdafx.h"
#include "SttSafetyMsgCfgs.h"
#include "../../../XLangResource_Native.h"

CSttSafetyMsgCfgs::CSttSafetyMsgCfgs()
{
	//初始化属性

	//初始化成员变量
}

CSttSafetyMsgCfgs::~CSttSafetyMsgCfgs()
{
}

long CSttSafetyMsgCfgs::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CSttSafetyMsgCfgXmlRWKeys *pXmlKeys = (CSttSafetyMsgCfgXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strNameKey, oNode, m_strName);
	return 0;
}

long CSttSafetyMsgCfgs::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CSttSafetyMsgCfgXmlRWKeys *pXmlKeys = (CSttSafetyMsgCfgXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strNameKey, oElement, m_strName);
	return 0;
}

long CSttSafetyMsgCfgs::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strName);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strName);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strName);
	}
	return 0;
}

void CSttSafetyMsgCfgs::InitAfterRead()
{
}

BOOL CSttSafetyMsgCfgs::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CSttSafetyMsgCfgs *p = (CSttSafetyMsgCfgs*)pObj;

	if(m_strName != p->m_strName)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CSttSafetyMsgCfgs::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CSttSafetyMsgCfgs *p = (CSttSafetyMsgCfgs*)pDest;

	p->m_strName = m_strName;
	return TRUE;
}

CBaseObject* CSttSafetyMsgCfgs::Clone()
{
	CSttSafetyMsgCfgs *p = new CSttSafetyMsgCfgs();
	Copy(p);
	return p;
}

long CSttSafetyMsgCfgs::InitListCtrlColumns(CListCtrl *pListCtrl)
{
	pListCtrl->InsertColumn(0, /*_T("编号")*/g_sLangTxt_Index);
	pListCtrl->SetColumnWidth(0, 80);
	pListCtrl->InsertColumn(1, _T("Name"));
	pListCtrl->SetColumnWidth(1, 80);
	pListCtrl->SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	return 0;
}

long CSttSafetyMsgCfgs::UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex)
{
	CString strTemp;
	strTemp.Format(_T("%d"), lItemIndex+1);
	pListCtrl->SetItemText(lItemIndex, 0, strTemp);
	pListCtrl->SetItemText(lItemIndex, 1, m_strName);
//	pListCtrl->SetItemData(lItemIndex, (WORD)this);
	return 0;
}

BOOL CSttSafetyMsgCfgs::CanPaste(UINT nClassID)
{
	if (nClassID == SSMCFGCLASSID_CSTTSAFETYMSGCFG)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CSttSafetyMsgCfgs::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CSttSafetyMsgCfgXmlRWKeys *pXmlKeys = (CSttSafetyMsgCfgXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCSttSafetyMsgCfgKey)
	{
		pNew = new CSttSafetyMsgCfg();
	}

	return pNew;
}

CExBaseObject* CSttSafetyMsgCfgs::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == SSMCFGCLASSID_CSTTSAFETYMSGCFG)
	{
		pNew = new CSttSafetyMsgCfg();
	}

	return pNew;
}

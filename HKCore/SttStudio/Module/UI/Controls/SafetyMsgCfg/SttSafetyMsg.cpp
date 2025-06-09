//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttSafetyMsg.cpp  CSttSafetyMsg


#include "stdafx.h"
#include "SttSafetyMsg.h"
#include "../../../XLangResource_Native.h"
CSttSafetyMsg::CSttSafetyMsg()
{
	//初始化属性

	//初始化成员变量
}

CSttSafetyMsg::~CSttSafetyMsg()
{
}

long CSttSafetyMsg::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CSttSafetyMsgCfgXmlRWKeys *pXmlKeys = (CSttSafetyMsgCfgXmlRWKeys*)pXmlRWKeys;

	xml_GetCDATA(oNode, m_strMsg,pXmlKeys->m_strMsgKey);
	return 0;
}

long CSttSafetyMsg::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CSttSafetyMsgCfgXmlRWKeys *pXmlKeys = (CSttSafetyMsgCfgXmlRWKeys*)pXmlRWKeys;

	xml_SetCDATA(oXMLDoc,oElement, m_strMsg,pXmlKeys->m_strMsgKey);
	return 0;
}

long CSttSafetyMsg::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strMsg);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strMsg);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strMsg);
	}
	return 0;
}

void CSttSafetyMsg::InitAfterRead()
{
}

BOOL CSttSafetyMsg::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CSttSafetyMsg *p = (CSttSafetyMsg*)pObj;

	if(m_strMsg != p->m_strMsg)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CSttSafetyMsg::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CSttSafetyMsg *p = (CSttSafetyMsg*)pDest;

	p->m_strMsg = m_strMsg;
	return TRUE;
}

CBaseObject* CSttSafetyMsg::Clone()
{
	CSttSafetyMsg *p = new CSttSafetyMsg();
	Copy(p);
	return p;
}

long CSttSafetyMsg::InitListCtrlColumns(CListCtrl *pListCtrl)
{
	pListCtrl->InsertColumn(0, /*_T("编号")*/g_sLangTxt_Index);
	pListCtrl->SetColumnWidth(0, 80);
	pListCtrl->InsertColumn(1, _T("Name"));
	pListCtrl->SetColumnWidth(1, 80);
	pListCtrl->InsertColumn(2, _T("ID"));
	pListCtrl->SetColumnWidth(2, 80);
	pListCtrl->InsertColumn(3, _T("Msg"));
	pListCtrl->SetColumnWidth(3, 80);
	pListCtrl->SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	return 0;
}

long CSttSafetyMsg::UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex)
{
	CString strTemp;
	strTemp.Format(_T("%d"), lItemIndex+1);
	pListCtrl->SetItemText(lItemIndex, 0, strTemp);
	pListCtrl->SetItemText(lItemIndex, 1, m_strName);
	pListCtrl->SetItemText(lItemIndex, 2, m_strID);
	pListCtrl->SetItemText(lItemIndex, 3, m_strMsg);
    //pListCtrl->SetItemData(lItemIndex, (WORD)this);
	return 0;
}


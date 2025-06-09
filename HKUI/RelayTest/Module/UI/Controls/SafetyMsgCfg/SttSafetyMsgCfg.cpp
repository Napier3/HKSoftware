//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttSafetyMsgCfg.cpp  CSttSafetyMsgCfg


#include "stdafx.h"
#include "SttSafetyMsgCfg.h"
#include "../../../XLangResource_Native.h"
CSttSafetyMsgCfg::CSttSafetyMsgCfg()
{
	//初始化属性

	//初始化成员变量
}

CSttSafetyMsgCfg::~CSttSafetyMsgCfg()
{
}

long CSttSafetyMsgCfg::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CSttSafetyMsgCfgXmlRWKeys *pXmlKeys = (CSttSafetyMsgCfgXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CSttSafetyMsgCfg::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CSttSafetyMsgCfgXmlRWKeys *pXmlKeys = (CSttSafetyMsgCfgXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CSttSafetyMsgCfg::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CSttSafetyMsgCfg::InitAfterRead()
{
}

BOOL CSttSafetyMsgCfg::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CSttSafetyMsgCfg *p = (CSttSafetyMsgCfg*)pObj;

	return TRUE;
}

BOOL CSttSafetyMsgCfg::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CSttSafetyMsgCfg *p = (CSttSafetyMsgCfg*)pDest;

	return TRUE;
}

CBaseObject* CSttSafetyMsgCfg::Clone()
{
	CSttSafetyMsgCfg *p = new CSttSafetyMsgCfg();
	Copy(p);
	return p;
}

long CSttSafetyMsgCfg::InitListCtrlColumns(CListCtrl *pListCtrl)
{
	pListCtrl->InsertColumn(0, /*_T("编号")*/g_sLangTxt_Index);
	pListCtrl->SetColumnWidth(0, 80);
	pListCtrl->InsertColumn(1, _T("Name"));
	pListCtrl->SetColumnWidth(1, 80);
	pListCtrl->InsertColumn(2, _T("ID"));
	pListCtrl->SetColumnWidth(2, 80);
	pListCtrl->SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	return 0;
}

long CSttSafetyMsgCfg::UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex)
{
	CString strTemp;
	strTemp.Format(_T("%d"), lItemIndex+1);
	pListCtrl->SetItemText(lItemIndex, 0, strTemp);
	pListCtrl->SetItemText(lItemIndex, 1, m_strName);
	pListCtrl->SetItemText(lItemIndex, 2, m_strID);
//	pListCtrl->SetItemData(lItemIndex, (WORD)this);
	return 0;
}

BOOL CSttSafetyMsgCfg::CanPaste(UINT nClassID)
{
	if (nClassID == SSMCFGCLASSID_CSTTSAFETYMSG)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CSttSafetyMsgCfg::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CSttSafetyMsgCfgXmlRWKeys *pXmlKeys = (CSttSafetyMsgCfgXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCSttSafetyMsgKey)
	{
		pNew = new CSttSafetyMsg();
	}

	return pNew;
}

CExBaseObject* CSttSafetyMsgCfg::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == SSMCFGCLASSID_CSTTSAFETYMSG)
	{
		pNew = new CSttSafetyMsg();
	}

	return pNew;
}

CSttSafetyMsg* CSttSafetyMsgCfg::FindByMsg(const CString &strMsgs)
{
	POS pos = GetHeadPosition();
	CSttSafetyMsg *pFind = NULL;

	while (pos != NULL)
	{
		CSttSafetyMsg *pMsg = (CSttSafetyMsg *)GetNext(pos);

		if (pMsg->m_strMsg == strMsgs)
		{
			pFind = pMsg;
			break;
		}
	}

	return pFind;
}
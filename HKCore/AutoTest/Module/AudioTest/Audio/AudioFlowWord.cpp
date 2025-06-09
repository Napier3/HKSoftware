//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//AudioFlowWord.cpp  CAudioFlowWord


#include "stdafx.h"
#include "AudioFlowWord.h"

CAudioFlowWord::CAudioFlowWord()
{
	//初始化属性

	//初始化成员变量
}

CAudioFlowWord::~CAudioFlowWord()
{
}

long CAudioFlowWord::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CAudioData::XmlReadOwn(oNode, pXmlRWKeys);

	CVoiceWordXmlRWKeys *pXmlKeys = (CVoiceWordXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strFlagKey, oNode, m_strFlag);
	xml_GetAttibuteValue(pXmlKeys->m_strTip_Word_IdKey, oNode, m_strTip_Word_Id);
	xml_GetAttibuteValue(pXmlKeys->m_strOrder_Word_IdKey, oNode, m_strOrder_Word_Id);
	return 0;
}

long CAudioFlowWord::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CAudioData::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CVoiceWordXmlRWKeys *pXmlKeys = (CVoiceWordXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strFlagKey, oElement, m_strFlag);
	xml_SetAttributeValue(pXmlKeys->m_strTip_Word_IdKey, oElement, m_strTip_Word_Id);
	xml_SetAttributeValue(pXmlKeys->m_strOrder_Word_IdKey, oElement, m_strOrder_Word_Id);
	return 0;
}

long CAudioFlowWord::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CAudioData::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strFlag);
		BinarySerializeCalLen(oBinaryBuffer, m_strTip_Word_Id);
		BinarySerializeCalLen(oBinaryBuffer, m_strOrder_Word_Id);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strFlag);
		BinarySerializeRead(oBinaryBuffer, m_strTip_Word_Id);
		BinarySerializeRead(oBinaryBuffer, m_strOrder_Word_Id);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strFlag);
		BinarySerializeWrite(oBinaryBuffer, m_strTip_Word_Id);
		BinarySerializeWrite(oBinaryBuffer, m_strOrder_Word_Id);
	}
	return 0;
}

void CAudioFlowWord::InitAfterRead()
{
}

BOOL CAudioFlowWord::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CAudioData::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CAudioFlowWord *p = (CAudioFlowWord*)pObj;

	if(m_strFlag != p->m_strFlag)
	{
		return FALSE;
	}

	if(m_strTip_Word_Id != p->m_strTip_Word_Id)
	{
		return FALSE;
	}

	if(m_strOrder_Word_Id != p->m_strOrder_Word_Id)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CAudioFlowWord::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CAudioData::CopyOwn(pDest);

	CAudioFlowWord *p = (CAudioFlowWord*)pDest;

	p->m_strFlag = m_strFlag;
	p->m_strTip_Word_Id = m_strTip_Word_Id;
	p->m_strOrder_Word_Id = m_strOrder_Word_Id;
	return TRUE;
}

CBaseObject* CAudioFlowWord::Clone()
{
	CAudioFlowWord *p = new CAudioFlowWord();
	Copy(p);
	return p;
}

long CAudioFlowWord::InitListCtrlColumns(CListCtrl *pListCtrl)
{
	pListCtrl->InsertColumn(0, _T("编号"));
	pListCtrl->SetColumnWidth(0, 80);
	pListCtrl->InsertColumn(1, _T("Name"));
	pListCtrl->SetColumnWidth(1, 80);
	pListCtrl->InsertColumn(2, _T("ID"));
	pListCtrl->SetColumnWidth(2, 80);
	pListCtrl->InsertColumn(3, _T("Flag"));
	pListCtrl->SetColumnWidth(3, 80);
	pListCtrl->InsertColumn(4, _T("Tip_Word"));
	pListCtrl->SetColumnWidth(4, 80);
	pListCtrl->InsertColumn(5, _T("Order_Word_Id"));
	pListCtrl->SetColumnWidth(5, 80);
	pListCtrl->SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	return 0;
}

long CAudioFlowWord::UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex)
{
	CString strTemp;
	strTemp.Format(_T("%d"), lItemIndex+1);
	pListCtrl->SetItemText(lItemIndex, 0, strTemp);
	pListCtrl->SetItemText(lItemIndex, 1, m_strName);
	pListCtrl->SetItemText(lItemIndex, 2, m_strID);
	pListCtrl->SetItemText(lItemIndex, 3, m_strFlag);
	pListCtrl->SetItemText(lItemIndex, 4, m_strTip_Word_Id);
	pListCtrl->SetItemText(lItemIndex, 5, m_strOrder_Word_Id);
	pListCtrl->SetItemData(lItemIndex, (WORD)this);
	return 0;
}

BOOL CAudioFlowWord::CanPaste(UINT nClassID)
{
	if (nClassID == VWCLASSID_CAUDIOWORD)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CAudioFlowWord::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CVoiceWordXmlRWKeys *pXmlKeys = (CVoiceWordXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCAudioWordKey)
	{
		pNew = new CAudioWord();
	}

	return pNew;
}

CExBaseObject* CAudioFlowWord::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == VWCLASSID_CAUDIOWORD)
	{
		pNew = new CAudioWord();
	}

	return pNew;
}

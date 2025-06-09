//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//AudioKeyWord.cpp  CAudioKeyWord


#include "stdafx.h"
#include "AudioKeyWord.h"

CAudioKeyWord::CAudioKeyWord()
{
	//初始化属性

	//初始化成员变量
}

CAudioKeyWord::~CAudioKeyWord()
{
}

long CAudioKeyWord::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CAudioData::XmlReadOwn(oNode, pXmlRWKeys);

	CVoiceWordXmlRWKeys *pXmlKeys = (CVoiceWordXmlRWKeys*)pXmlRWKeys;

	//xml_GetAttibuteValue(pXmlKeys->m_strValueKey, oNode, m_strValue);
	xml_GetAttibuteValue(pXmlKeys->m_strOrder_Word_IdKey, oNode, m_strOrder_Word_Id);
	return 0;
}

long CAudioKeyWord::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CAudioData::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CVoiceWordXmlRWKeys *pXmlKeys = (CVoiceWordXmlRWKeys*)pXmlRWKeys;

	//xml_SetAttributeValue(pXmlKeys->m_strValueKey, oElement, m_strValue);
	xml_SetAttributeValue(pXmlKeys->m_strOrder_Word_IdKey, oElement, m_strOrder_Word_Id);
	return 0;
}

long CAudioKeyWord::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CAudioData::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		//BinarySerializeCalLen(oBinaryBuffer, m_strValue);
		BinarySerializeCalLen(oBinaryBuffer, m_strOrder_Word_Id);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		//BinarySerializeRead(oBinaryBuffer, m_strValue);
		BinarySerializeRead(oBinaryBuffer, m_strOrder_Word_Id);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		//BinarySerializeWrite(oBinaryBuffer, m_strValue);
		BinarySerializeWrite(oBinaryBuffer, m_strOrder_Word_Id);
	}
	return 0;
}

void CAudioKeyWord::InitAfterRead()
{
}

BOOL CAudioKeyWord::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CAudioData::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CAudioKeyWord *p = (CAudioKeyWord*)pObj;

	//if(m_strValue != p->m_strValue)
	//{
	//	return FALSE;
	//}

	if(m_strOrder_Word_Id != p->m_strOrder_Word_Id)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CAudioKeyWord::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CAudioData::CopyOwn(pDest);

	CAudioKeyWord *p = (CAudioKeyWord*)pDest;

	//p->m_strValue = m_strValue;
	p->m_strOrder_Word_Id = m_strOrder_Word_Id;
	return TRUE;
}

CBaseObject* CAudioKeyWord::Clone()
{
	CAudioKeyWord *p = new CAudioKeyWord();
	Copy(p);
	return p;
}

long CAudioKeyWord::InitListCtrlColumns(CListCtrl *pListCtrl)
{
	pListCtrl->InsertColumn(0, _T("编号"));
	pListCtrl->SetColumnWidth(0, 80);
	pListCtrl->InsertColumn(1, _T("Name"));
	pListCtrl->SetColumnWidth(1, 80);
	pListCtrl->InsertColumn(2, _T("ID"));
	pListCtrl->SetColumnWidth(2, 80);
	//pListCtrl->InsertColumn(3, _T("Value"));
	//pListCtrl->SetColumnWidth(3, 80);
	pListCtrl->InsertColumn(4, _T("Order_Word_Id"));
	pListCtrl->SetColumnWidth(4, 80);
	pListCtrl->SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	return 0;
}

long CAudioKeyWord::UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex)
{
	CString strTemp;
	strTemp.Format(_T("%d"), lItemIndex+1);
	pListCtrl->SetItemText(lItemIndex, 0, strTemp);
	pListCtrl->SetItemText(lItemIndex, 1, m_strName);
	pListCtrl->SetItemText(lItemIndex, 2, m_strID);
	//pListCtrl->SetItemText(lItemIndex, 3, m_strValue);
	pListCtrl->SetItemText(lItemIndex, 4, m_strOrder_Word_Id);
	pListCtrl->SetItemData(lItemIndex, (WORD)this);
	return 0;
}

BOOL CAudioKeyWord::CanPaste(UINT nClassID)
{
	if (nClassID == VWCLASSID_CAUDIODATA)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CAudioKeyWord::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CVoiceWordXmlRWKeys *pXmlKeys = (CVoiceWordXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCAudioDataKey)
	{
		pNew = new CAudioData();
	}

	return pNew;
}

CExBaseObject* CAudioKeyWord::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == VWCLASSID_CAUDIODATA)
	{
		pNew = new CAudioData();
	}

	return pNew;
}

//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//AudioReplyKeyWord.cpp  CAudioReplyKeyWord


#include "stdafx.h"
#include "AudioReplyKeyWord.h"

CAudioReplyKeyWord::CAudioReplyKeyWord()
{
	//初始化属性

	//初始化成员变量
}

CAudioReplyKeyWord::~CAudioReplyKeyWord()
{
}

long CAudioReplyKeyWord::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CAudioData::XmlReadOwn(oNode, pXmlRWKeys);

	CVoiceWordXmlRWKeys *pXmlKeys = (CVoiceWordXmlRWKeys*)pXmlRWKeys;

	//xml_GetAttibuteValue(pXmlKeys->m_strValueKey, oNode, m_strValue);
	return 0;
}

long CAudioReplyKeyWord::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CAudioData::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CVoiceWordXmlRWKeys *pXmlKeys = (CVoiceWordXmlRWKeys*)pXmlRWKeys;

	//xml_SetAttributeValue(pXmlKeys->m_strValueKey, oElement, m_strValue);
	return 0;
}

long CAudioReplyKeyWord::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CAudioData::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		//BinarySerializeCalLen(oBinaryBuffer, m_strValue);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		//BinarySerializeRead(oBinaryBuffer, m_strValue);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		//BinarySerializeWrite(oBinaryBuffer, m_strValue);
	}
	return 0;
}

void CAudioReplyKeyWord::InitAfterRead()
{
}

BOOL CAudioReplyKeyWord::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CAudioData::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CAudioReplyKeyWord *p = (CAudioReplyKeyWord*)pObj;

	/*if(m_strValue != p->m_strValue)
	{
		return FALSE;
	}*/

	return TRUE;
}

BOOL CAudioReplyKeyWord::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CAudioData::CopyOwn(pDest);

	CAudioReplyKeyWord *p = (CAudioReplyKeyWord*)pDest;

	p->m_strValue = m_strValue;
	return TRUE;
}

CBaseObject* CAudioReplyKeyWord::Clone()
{
	CAudioReplyKeyWord *p = new CAudioReplyKeyWord();
	Copy(p);
	return p;
}

long CAudioReplyKeyWord::InitListCtrlColumns(CListCtrl *pListCtrl)
{
	pListCtrl->InsertColumn(0, _T("编号"));
	pListCtrl->SetColumnWidth(0, 80);
	pListCtrl->InsertColumn(1, _T("Name"));
	pListCtrl->SetColumnWidth(1, 80);
	pListCtrl->InsertColumn(2, _T("ID"));
	pListCtrl->SetColumnWidth(2, 80);
	//pListCtrl->InsertColumn(3, _T("Value"));
	//pListCtrl->SetColumnWidth(3, 80);
	pListCtrl->SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	return 0;
}

long CAudioReplyKeyWord::UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex)
{
	CString strTemp;
	strTemp.Format(_T("%d"), lItemIndex+1);
	pListCtrl->SetItemText(lItemIndex, 0, strTemp);
	pListCtrl->SetItemText(lItemIndex, 1, m_strName);
	pListCtrl->SetItemText(lItemIndex, 2, m_strID);
	//pListCtrl->SetItemText(lItemIndex, 3, m_strValue);
	pListCtrl->SetItemData(lItemIndex, (WORD)this);
	return 0;
}

BOOL CAudioReplyKeyWord::CanPaste(UINT nClassID)
{
	if (nClassID == VWCLASSID_CAUDIODATA)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CAudioReplyKeyWord::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CVoiceWordXmlRWKeys *pXmlKeys = (CVoiceWordXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCAudioDataKey)
	{
		pNew = new CAudioData();
	}

	return pNew;
}

CExBaseObject* CAudioReplyKeyWord::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == VWCLASSID_CAUDIODATA)
	{
		pNew = new CAudioData();
	}

	return pNew;
}

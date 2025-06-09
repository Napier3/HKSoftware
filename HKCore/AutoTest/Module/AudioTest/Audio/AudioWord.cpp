//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//AudioWord.cpp  CAudioWord


#include "stdafx.h"
#include "AudioWord.h"

CAudioWord::CAudioWord()
{
	//初始化属性

	//初始化成员变量
}

CAudioWord::~CAudioWord()
{
}

long CAudioWord::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CAudioData::XmlReadOwn(oNode, pXmlRWKeys);

	CVoiceWordXmlRWKeys *pXmlKeys = (CVoiceWordXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strLevelKey, oNode, m_strLevel);
	//xml_GetAttibuteValue(pXmlKeys->m_strValueKey, oNode, m_strValue);
	return 0;
}

long CAudioWord::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CAudioData::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CVoiceWordXmlRWKeys *pXmlKeys = (CVoiceWordXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strLevelKey, oElement, m_strLevel);
	//xml_SetAttributeValue(pXmlKeys->m_strValueKey, oElement, m_strValue);
	return 0;
}

long CAudioWord::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CAudioData::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strLevel);
		//BinarySerializeCalLen(oBinaryBuffer, m_strValue);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strLevel);
		//BinarySerializeRead(oBinaryBuffer, m_strValue);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strLevel);
		//BinarySerializeWrite(oBinaryBuffer, m_strValue);
	}
	return 0;
}

void CAudioWord::InitAfterRead()
{
}

BOOL CAudioWord::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CAudioData::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CAudioWord *p = (CAudioWord*)pObj;

	if(m_strLevel != p->m_strLevel)
	{
		return FALSE;
	}

	/*if(m_strValue != p->m_strValue)
	{
		return FALSE;
	}*/

	return TRUE;
}

BOOL CAudioWord::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CAudioData::CopyOwn(pDest);

	CAudioWord *p = (CAudioWord*)pDest;

	p->m_strLevel = m_strLevel;
//	p->m_strValue = m_strValue;
	return TRUE;
}

CBaseObject* CAudioWord::Clone()
{
	CAudioWord *p = new CAudioWord();
	Copy(p);
	return p;
}

long CAudioWord::InitListCtrlColumns(CListCtrl *pListCtrl)
{
	pListCtrl->InsertColumn(0, _T("编号"));
	pListCtrl->SetColumnWidth(0, 80);
	pListCtrl->InsertColumn(1, _T("Name"));
	pListCtrl->SetColumnWidth(1, 80);
	pListCtrl->InsertColumn(2, _T("ID"));
	pListCtrl->SetColumnWidth(2, 80);
	pListCtrl->InsertColumn(3, _T("Level"));
	pListCtrl->SetColumnWidth(3, 80);
	//pListCtrl->InsertColumn(4, _T("Value"));
	//pListCtrl->SetColumnWidth(4, 80);
	pListCtrl->SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	return 0;
}

long CAudioWord::UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex)
{
	CString strTemp;
	strTemp.Format(_T("%d"), lItemIndex+1);
	pListCtrl->SetItemText(lItemIndex, 0, strTemp);
	pListCtrl->SetItemText(lItemIndex, 1, m_strName);
	pListCtrl->SetItemText(lItemIndex, 2, m_strID);
	pListCtrl->SetItemText(lItemIndex, 3, m_strLevel);
	//pListCtrl->SetItemText(lItemIndex, 4, m_strValue);
	pListCtrl->SetItemData(lItemIndex, (WORD)this);
	return 0;
}

BOOL CAudioWord::CanPaste(UINT nClassID)
{
	if (nClassID == VWCLASSID_CAUDIODATA)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CAudioWord::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CVoiceWordXmlRWKeys *pXmlKeys = (CVoiceWordXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCAudioDataKey)
	{
		pNew = new CAudioData();
	}

	return pNew;
}

CExBaseObject* CAudioWord::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == VWCLASSID_CAUDIODATA)
	{
		pNew = new CAudioData();
	}

	return pNew;
}

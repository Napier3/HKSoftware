//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//AudioOrderWords.cpp  CAudioOrderWords


#include "stdafx.h"
#include "AudioOrderWords.h"

CAudioOrderWords::CAudioOrderWords()
{
	//初始化属性

	//初始化成员变量
}

CAudioOrderWords::~CAudioOrderWords()
{
}

long CAudioOrderWords::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CAudioData::XmlReadOwn(oNode, pXmlRWKeys);

	CVoiceWordXmlRWKeys *pXmlKeys = (CVoiceWordXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CAudioOrderWords::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CAudioData::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CVoiceWordXmlRWKeys *pXmlKeys = (CVoiceWordXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CAudioOrderWords::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CAudioData::SerializeOwn(oBinaryBuffer);

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

void CAudioOrderWords::InitAfterRead()
{
}

BOOL CAudioOrderWords::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CAudioData::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CAudioOrderWords *p = (CAudioOrderWords*)pObj;

	return TRUE;
}

BOOL CAudioOrderWords::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CAudioData::CopyOwn(pDest);

	CAudioOrderWords *p = (CAudioOrderWords*)pDest;

	return TRUE;
}

CBaseObject* CAudioOrderWords::Clone()
{
	CAudioOrderWords *p = new CAudioOrderWords();
	Copy(p);
	return p;
}

long CAudioOrderWords::InitListCtrlColumns(CListCtrl *pListCtrl)
{
	pListCtrl->InsertColumn(0, _T("编号"));
	pListCtrl->SetColumnWidth(0, 80);
	pListCtrl->InsertColumn(1, _T("Name"));
	pListCtrl->SetColumnWidth(1, 80);
	pListCtrl->InsertColumn(2, _T("ID"));
	pListCtrl->SetColumnWidth(2, 80);
	pListCtrl->SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	return 0;
}

long CAudioOrderWords::UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex)
{
	CString strTemp;
	strTemp.Format(_T("%d"), lItemIndex+1);
	pListCtrl->SetItemText(lItemIndex, 0, strTemp);
	pListCtrl->SetItemText(lItemIndex, 1, m_strName);
	pListCtrl->SetItemText(lItemIndex, 2, m_strID);
	pListCtrl->SetItemData(lItemIndex, (WORD)this);
	return 0;
}

BOOL CAudioOrderWords::CanPaste(UINT nClassID)
{
	if (nClassID == VWCLASSID_CAUDIOORDERWORD)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CAudioOrderWords::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CVoiceWordXmlRWKeys *pXmlKeys = (CVoiceWordXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCAudioOrderWordKey)
	{
		pNew = new CAudioOrderWord();
	}

	return pNew;
}

CExBaseObject* CAudioOrderWords::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == VWCLASSID_CAUDIOORDERWORD)
	{
		pNew = new CAudioOrderWord();
	}

	return pNew;
}

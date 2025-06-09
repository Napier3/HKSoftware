//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//AudioTestWords.cpp  CAudioTestWords


#include "stdafx.h"
#include "AudioTestWords.h"

CAudioTestWords::CAudioTestWords()
{
	//初始化属性

	//初始化成员变量
}

CAudioTestWords::~CAudioTestWords()
{
}

long CAudioTestWords::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CAudioData::XmlReadOwn(oNode, pXmlRWKeys);

	CVoiceWordXmlRWKeys *pXmlKeys = (CVoiceWordXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CAudioTestWords::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CAudioData::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CVoiceWordXmlRWKeys *pXmlKeys = (CVoiceWordXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CAudioTestWords::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CAudioTestWords::InitAfterRead()
{
}

BOOL CAudioTestWords::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CAudioData::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CAudioTestWords *p = (CAudioTestWords*)pObj;

	return TRUE;
}

BOOL CAudioTestWords::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CAudioData::CopyOwn(pDest);

	CAudioTestWords *p = (CAudioTestWords*)pDest;

	return TRUE;
}

CBaseObject* CAudioTestWords::Clone()
{
	CAudioTestWords *p = new CAudioTestWords();
	Copy(p);
	return p;
}

long CAudioTestWords::InitListCtrlColumns(CListCtrl *pListCtrl)
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

long CAudioTestWords::UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex)
{
	CString strTemp;
	strTemp.Format(_T("%d"), lItemIndex+1);
	pListCtrl->SetItemText(lItemIndex, 0, strTemp);
	pListCtrl->SetItemText(lItemIndex, 1, m_strName);
	pListCtrl->SetItemText(lItemIndex, 2, m_strID);
	pListCtrl->SetItemData(lItemIndex, (WORD)this);
	return 0;
}

BOOL CAudioTestWords::CanPaste(UINT nClassID)
{
	if (nClassID == VWCLASSID_CAUDIOORDERWORDS)
	{
		return TRUE;
	}

	if (nClassID == VWCLASSID_CAUDIOFLOWWORDS)
	{
		return TRUE;
	}

	if (nClassID == VWCLASSID_CAUDIOKEYWORDS)
	{
		return TRUE;
	}

	if (nClassID == VWCLASSID_CAUDIOTIPWORDS)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CAudioTestWords::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CVoiceWordXmlRWKeys *pXmlKeys = (CVoiceWordXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCAudioOrderWordsKey)
	{
		pNew = new CAudioOrderWords();
	}
	else if (strClassID == pXmlKeys->m_strCAudioFlowWordsKey)
	{
		pNew = new CAudioFlowWords();
	}
	else if (strClassID == pXmlKeys->m_strCAudioKeyWordsKey)
	{
		pNew = new CAudioKeyWords();
	}
	else if (strClassID == pXmlKeys->m_strCAudioTipWordsKey)
	{
		pNew = new CAudioTipWords();
	}

	return pNew;
}

CExBaseObject* CAudioTestWords::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == VWCLASSID_CAUDIOORDERWORDS)
	{
		pNew = new CAudioOrderWords();
	}
	else if (nClassID == VWCLASSID_CAUDIOFLOWWORDS)
	{
		pNew = new CAudioFlowWords();
	}
	else if (nClassID == VWCLASSID_CAUDIOKEYWORDS)
	{
		pNew = new CAudioKeyWords();
	}
	else if (nClassID == VWCLASSID_CAUDIOTIPWORDS)
	{
		pNew = new CAudioTipWords();
	}

	return pNew;
}

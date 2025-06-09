//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//CharacterArea.cpp  CCharacterArea


#include "stdafx.h"
#include "CharacterArea.h"

CCharacterArea::CCharacterArea()
{
	//初始化属性

	//初始化成员变量
}

CCharacterArea::~CCharacterArea()
{
}

long CCharacterArea::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CCharacteristicXmlRWKeys *pXmlKeys = (CCharacteristicXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CCharacterArea::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CCharacteristicXmlRWKeys *pXmlKeys = (CCharacteristicXmlRWKeys*)pXmlRWKeys;

	return 0;
}

BOOL CCharacterArea::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CCharacterArea *p = (CCharacterArea*)pObj;

	return TRUE;
}

BOOL CCharacterArea::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CCharacterArea *p = (CCharacterArea*)pDest;

	return TRUE;
}

CBaseObject* CCharacterArea::Clone()
{
	CCharacterArea *p = new CCharacterArea();
	Copy(p);
	return p;
}

BOOL CCharacterArea::CanPaste(UINT nClassID)
{
	if (nClassID == CHARCLASSID_CCHARELEMENTLENS)
	{
		return TRUE;
	}

	if (nClassID == CHARCLASSID_CCHARELEMENTARC)
	{
		return TRUE;
	}

	if (nClassID == CHARCLASSID_CCHARELEMENTARCD)
	{
		return TRUE;
	}

	if (nClassID == CHARCLASSID_CCHARELEMENTARCP)
	{
		return TRUE;
	}

	if (nClassID == CHARCLASSID_CCHARELEMENTLINE)
	{
		return TRUE;
	}

	if (nClassID == CHARCLASSID_CCHARELEMENTLINED)
	{
		return TRUE;
	}

	if (nClassID == CHARCLASSID_CCHARELEMENTLINEP)
	{
		return TRUE;
	}

	if (nClassID == CHARCLASSID_CCHARELEMENTMHO)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CCharacterArea::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CCharacteristicXmlRWKeys *pXmlKeys = (CCharacteristicXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCCharElementLensKey)
	{
		pNew = new CCharElementLens();
	}
	else if (strClassID == pXmlKeys->m_strCCharElementArcKey)
	{
		pNew = new CCharElementArc();
	}
	else if (strClassID == pXmlKeys->m_strCCharElementArcdKey)
	{
		pNew = new CCharElementArcd();
	}
	else if (strClassID == pXmlKeys->m_strCCharElementArcpKey)
	{
		pNew = new CCharElementArcp();
	}
	else if (strClassID == pXmlKeys->m_strCCharElementLineKey)
	{
		pNew = new CCharElementLine();
	}
	else if (strClassID == pXmlKeys->m_strCCharElementLinedKey)
	{
		pNew = new CCharElementLined();
	}
	else if (strClassID == pXmlKeys->m_strCCharElementLinepKey)
	{
		pNew = new CCharElementLinep();
	}
	else if (strClassID == pXmlKeys->m_strCCharElementMhoKey)
	{
		pNew = new CCharElementMho();
	}

	return pNew;
}

CExBaseObject* CCharacterArea::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == CHARCLASSID_CCHARELEMENTLENS)
	{
		pNew = new CCharElementLens();
	}
	else if (nClassID == CHARCLASSID_CCHARELEMENTARC)
	{
		pNew = new CCharElementArc();
	}
	else if (nClassID == CHARCLASSID_CCHARELEMENTARCD)
	{
		pNew = new CCharElementArcd();
	}
	else if (nClassID == CHARCLASSID_CCHARELEMENTARCP)
	{
		pNew = new CCharElementArcp();
	}
	else if (nClassID == CHARCLASSID_CCHARELEMENTLINE)
	{
		pNew = new CCharElementLine();
	}
	else if (nClassID == CHARCLASSID_CCHARELEMENTLINED)
	{
		pNew = new CCharElementLined();
	}
	else if (nClassID == CHARCLASSID_CCHARELEMENTLINEP)
	{
		pNew = new CCharElementLinep();
	}
	else if (nClassID == CHARCLASSID_CCHARELEMENTMHO)
	{
		pNew = new CCharElementMho();
	}

	return pNew;
}

long CCharacterArea::InsertToListCtrl(CListCtrl *pListCtrl)
{
	CString strElementIndex;
	CString strXml;
	CCharElement *pObj;
	long lItemIndex = 0;

	pListCtrl->DeleteAllItems();

	POS pos = GetHeadPosition();
	while(pos)
	{
		pObj =(CCharElement *)GetNext(pos);
		strElementIndex.Format(_T("%d"), lItemIndex+1);
		strXml = pObj->ReturnXml();
		pListCtrl->InsertItem( lItemIndex,strElementIndex );
		pListCtrl->SetItemText(lItemIndex, 1, strXml);
		pListCtrl->SetItemData(lItemIndex, (DWORD)pObj);
		lItemIndex ++;
	}
	return lItemIndex;
}


long CCharacterArea::InitListCtrlColumns(CListCtrl *pListCtrl)
{
	pListCtrl->InsertColumn(0, _T("Num"));
	pListCtrl->SetColumnWidth(0, 66);
	pListCtrl->InsertColumn(1, _T("曲线参数"));
	pListCtrl->SetColumnWidth(1, 250);
	pListCtrl->SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	return 0;
}


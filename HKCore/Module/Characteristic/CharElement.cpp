//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//CharElement.cpp  CCharElement


#include "stdafx.h"
#include "CharElement.h"

CCharElement::CCharElement()
{
	//初始化属性

	//初始化成员变量
}

CCharElement::~CCharElement()
{
}

long CCharElement::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CCharacteristicXmlRWKeys *pXmlKeys = (CCharacteristicXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strDirKey, oNode, m_strDir);
	return 0;
}

long CCharElement::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CCharacteristicXmlRWKeys *pXmlKeys = (CCharacteristicXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strDirKey, oElement, m_strDir);
	return 0;
}

BOOL CCharElement::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CCharElement *p = (CCharElement*)pDest;

	p->m_strDir = m_strDir;
	return TRUE;
}

CBaseObject* CCharElement::Clone()
{
	CCharElement *p = new CCharElement();
	Copy(p);
	return p;
}

long CCharElement::InsertToListCtrl(CListCtrl *pListCtrl,long lItemIndex)
{
	CString strTemp;
	strTemp.Format(_T("%d"), lItemIndex+1);
	pListCtrl->InsertItem( lItemIndex,strTemp );
	pListCtrl->SetItemText(lItemIndex, 1, ReturnXml());
	pListCtrl->SetItemData(lItemIndex, (DWORD)this);
	return 0;
}

long CCharElement::UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex)
{
	CString strTemp;
	strTemp.Format(_T("%d"), lItemIndex+1);
	pListCtrl->SetItemText( lItemIndex,0,strTemp );
	pListCtrl->SetItemText(lItemIndex, 1, ReturnXml());
	pListCtrl->SetItemData(lItemIndex, (DWORD)this);
	return 0;
}

CString CCharElement::ReturnXml()
{
	CString str;
	str.Format(_T("xml"));
	return str;
}
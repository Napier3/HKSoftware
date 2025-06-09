//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//CharInterfaceVariable.cpp  CCharInterfaceVariable


#include "stdafx.h"
#include "CharInterfaceVariable.h"

CCharInterfaceVariable::CCharInterfaceVariable()
{
	//初始化属性

	//初始化成员变量
}

CCharInterfaceVariable::~CCharInterfaceVariable()
{
}

long CCharInterfaceVariable::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CCharacteristicXmlRWKeys *pXmlKeys = (CCharacteristicXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strValueKey, oNode, m_strValue);
	return 0;
}

long CCharInterfaceVariable::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CCharacteristicXmlRWKeys *pXmlKeys = (CCharacteristicXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strValueKey, oElement, m_strValue);
	return 0;
}

BOOL CCharInterfaceVariable::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CCharInterfaceVariable *p = (CCharInterfaceVariable*)pObj;

	if(m_strValue != p->m_strValue)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CCharInterfaceVariable::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CCharInterfaceVariable *p = (CCharInterfaceVariable*)pDest;

	p->m_strValue = m_strValue;
	return TRUE;
}

CBaseObject* CCharInterfaceVariable::Clone()
{
	CCharInterfaceVariable *p = new CCharInterfaceVariable();
	Copy(p);
	return p;
}

long CCharInterfaceVariable::InsertToListCtrl(CListCtrl *pListCtrl,long lItemIndex)
{
	CString strTemp;
	strTemp.Format(_T("%d"), lItemIndex+1);
	pListCtrl->InsertItem( lItemIndex,strTemp );
	pListCtrl->SetItemText(lItemIndex, 1, m_strID);
	pListCtrl->SetItemText(lItemIndex, 2, m_strName);
	pListCtrl->SetItemText(lItemIndex, 3, m_strValue);
	pListCtrl->SetItemData(lItemIndex, (DWORD)this);  //绑定数据
	return 0;
}

long CCharInterfaceVariable::UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex)
{
	CString strTemp;
	strTemp.Format(_T("%d"), lItemIndex+1);
	pListCtrl->SetItemText( lItemIndex,0,strTemp );
	pListCtrl->SetItemText(lItemIndex, 1, m_strID);
	pListCtrl->SetItemText(lItemIndex, 2, m_strName);
	pListCtrl->SetItemText(lItemIndex, 3, m_strValue);
	pListCtrl->SetItemData(lItemIndex, (DWORD)this);
	return 0;
}
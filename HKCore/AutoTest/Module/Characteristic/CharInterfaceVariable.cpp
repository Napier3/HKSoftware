//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//CharInterfaceVariable.cpp  CCharInterfaceVariable


#include "stdafx.h"
#include "CharInterfaceVariable.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CCharInterfaceVariable::CCharInterfaceVariable()
{
	//初始化属性
	m_strName = _T("Var");
	m_strID   = m_strName;
	m_strValue = _T("1");
	//m_pDataObjRef = NULL;

	//初始化成员变量
}

CCharInterfaceVariable::~CCharInterfaceVariable()
{
}

long CCharInterfaceVariable::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CCharacteristicXmlRWKeys *pXmlKeys = (CCharacteristicXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strValueKey, oNode, m_strValue);
	xml_GetAttibuteValue(pXmlKeys->m_strScriptKey, oNode, m_strScript);

	return 0;
}

long CCharInterfaceVariable::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CCharacteristicXmlRWKeys *pXmlKeys = (CCharacteristicXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strValueKey, oElement, m_strValue);
	xml_SetAttributeValue(pXmlKeys->m_strScriptKey, oElement, m_strScript);
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

// 	if(m_strValue != p->m_strValue)
// 	{
// 		return FALSE;
// 	}

	//只判断脚本是否一致
	if(m_strScript != p->m_strScript)
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
	p->m_strScript = m_strScript;

	return TRUE;
}

CBaseObject* CCharInterfaceVariable::Clone()
{
	CCharInterfaceVariable *p = new CCharInterfaceVariable();
	Copy(p);
	return p;
}


long CCharInterfaceVariable::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strValue);
		BinarySerializeCalLen(oBinaryBuffer, m_strScript);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strValue);
		BinarySerializeRead(oBinaryBuffer, m_strScript);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strValue);
		BinarySerializeWrite(oBinaryBuffer, m_strScript);
	}

	return 0;
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

BOOL CCharInterfaceVariable::GetVariableValue(CString &strValue)
{
	//CharVar_CalScriptValue(this);

	strValue = m_strValue;

	return TRUE;
}

void CCharInterfaceVariable::InitVariableValue()
{
// 	m_pDataObjRef = CharVar_GetScriptValObj(this);
// 
// 	if (m_pDataObjRef != NULL)
// 	{
// 		CharVar_CalScriptValue(m_pDataObjRef, m_strValue);
// 	}
	
	CharVar_CalScriptValue(this);
}


//////////////////////////////////////////////////////////////////////////
#ifdef _CHAR_LIB_DEV_
BOOL CharVar_CalScriptValue(CCharInterfaceVariable *pCharVar)
{
    return FALSE;
}

CExBaseObject* CharVar_GetScriptValObj(CCharInterfaceVariable *pCharVar)
{
    return NULL;
}

CString* CharVar_CalScriptValue(CExBaseObject *pData)
{
    return &pData->m_strID;
}

void CharVar_CalScriptValue(CExBaseObject *pData, CString &strValue)
{

}
#endif


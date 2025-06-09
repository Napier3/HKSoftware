//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//CharacteristicTmplate.cpp  CCharacteristicTmplate


#include "stdafx.h"
#include "CharacteristicTmplate.h"

CCharacteristicTmplate::CCharacteristicTmplate()
{
	//初始化属性

	//初始化成员变量
	m_pCharacteristic = NULL;
	m_pCharacteristicInterface = NULL;
}

CCharacteristicTmplate::~CCharacteristicTmplate()
{
}

long CCharacteristicTmplate::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CCharacteristicXmlRWKeys *pXmlKeys = (CCharacteristicXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CCharacteristicTmplate::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CCharacteristicXmlRWKeys *pXmlKeys = (CCharacteristicXmlRWKeys*)pXmlRWKeys;

	return 0;
}

void CCharacteristicTmplate::InitAfterRead()
{
	POS pos = GetHeadPosition();
	CBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = GetNext(pos);
		nClassID = p->GetClassID();

		if (nClassID == CHARCLASSID_CCHARACTERISTIC)
		{
			m_pCharacteristic = (CCharacteristic*)p;
		}
		else if (nClassID == CHARCLASSID_CCHARINTERFACE)
		{
			m_pCharacteristicInterface = (CCharInterface*)p;
		}
	}

	if (m_pCharacteristic == NULL)
	{
		m_pCharacteristic = (CCharacteristic*)AddNewChild(new CCharacteristic());
	}

	if (m_pCharacteristicInterface == NULL)
	{
		m_pCharacteristicInterface = (CCharInterface*)AddNewChild(new CCharInterface());
	}

}

BOOL CCharacteristicTmplate::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CCharacteristicTmplate *p = (CCharacteristicTmplate*)pDest;

	return TRUE;
}

BOOL CCharacteristicTmplate::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CCharacteristicTmplate *p = (CCharacteristicTmplate*)pObj;

	return TRUE;
}

CBaseObject* CCharacteristicTmplate::Clone()
{
	CCharacteristicTmplate *p = new CCharacteristicTmplate();
	Copy(p);
	return p;
}

CExBaseObject* CCharacteristicTmplate::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CCharacteristicXmlRWKeys *pXmlKeys = (CCharacteristicXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCCharInterfaceKey)
	{
		pNew = new CCharInterface();
	}
	else if (strClassID == pXmlKeys->m_strCCharacteristicKey)
	{
		pNew = new CCharacteristic();
	}

	return pNew;
}

CExBaseObject* CCharacteristicTmplate::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == CHARCLASSID_CCHARINTERFACE)
	{
		pNew = new CCharInterface();
	}
	else if (nClassID == CHARCLASSID_CCHARACTERISTIC)
	{
		pNew = new CCharacteristic();
	}

	return pNew;
}

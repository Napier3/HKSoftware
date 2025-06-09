//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Characteristics.cpp  CCharacteristics


#include "stdafx.h"
#include "Characteristics.h"

CCharacteristics::CCharacteristics()
{
	//初始化属性

	//初始化成员变量
}

CCharacteristics::~CCharacteristics()
{
}

long CCharacteristics::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CCharacteristicXmlRWKeys *pXmlKeys = (CCharacteristicXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CCharacteristics::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CCharacteristicXmlRWKeys *pXmlKeys = (CCharacteristicXmlRWKeys*)pXmlRWKeys;

	return 0;
}

void CCharacteristics::InitAfterRead()
{
}

BOOL CCharacteristics::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CCharacteristics *p = (CCharacteristics*)pObj;

	return TRUE;
}

BOOL CCharacteristics::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CCharacteristics *p = (CCharacteristics*)pDest;

	return TRUE;
}

CBaseObject* CCharacteristics::Clone()
{
	CCharacteristics *p = new CCharacteristics();
	Copy(p);
	return p;
}

BOOL CCharacteristics::CanPaste(UINT nClassID)
{
	if (nClassID == CHARCLASSID_CCHARACTERISTIC)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CCharacteristics::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CCharacteristicXmlRWKeys *pXmlKeys = (CCharacteristicXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCCharacteristicKey)
	{
		pNew = new CCharacteristic();
	}

	return pNew;
}

CExBaseObject* CCharacteristics::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == CHARCLASSID_CCHARACTERISTIC)
	{
		pNew = new CCharacteristic();
	}

	return pNew;
}

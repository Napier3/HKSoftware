//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//CharMacroDraws.cpp  CCharMacroDraws


#include "stdafx.h"
#include "CharMacroDraws.h"

CCharMacroDraws::CCharMacroDraws()
{
	//初始化属性

	//初始化成员变量
}

CCharMacroDraws::~CCharMacroDraws()
{
}

long CCharMacroDraws::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CCharacteristicXmlRWKeys *pXmlKeys = (CCharacteristicXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CCharMacroDraws::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CCharacteristicXmlRWKeys *pXmlKeys = (CCharacteristicXmlRWKeys*)pXmlRWKeys;

	return 0;
}

void CCharMacroDraws::InitAfterRead()
{
}

BOOL CCharMacroDraws::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CCharMacroDraws *p = (CCharMacroDraws*)pObj;

	return TRUE;
}

BOOL CCharMacroDraws::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CCharMacroDraws *p = (CCharMacroDraws*)pDest;

	return TRUE;
}

CBaseObject* CCharMacroDraws::Clone()
{
	CCharMacroDraws *p = new CCharMacroDraws();
	Copy(p);
	return p;
}

BOOL CCharMacroDraws::CanPaste(UINT nClassID)
{
	if (nClassID == CHARCLASSID_CCHARMACRODRAWLINE)
	{
		return TRUE;
	}

	if (nClassID == CHARCLASSID_CCHARMACRODRAWPOINT)
	{
		return TRUE;
	}

	return FALSE;
}


CExBaseObject* CCharMacroDraws::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == CHARCLASSID_CCHARMACRODRAWLINE)
	{
		pNew = new CCharMacroDrawLine();
	}
	else if (nClassID == CHARCLASSID_CCHARMACRODRAWPOINT)
	{
		pNew = new CCharMacroDrawPoint();
	}

	return pNew;
}
CExBaseObject* CCharMacroDraws::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CCharacteristicXmlRWKeys *pXmlKeys = (CCharacteristicXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCCharMacroDrawLineKey)
	{
		pNew = new CCharMacroDrawLine();
	}
	else if (strClassID == pXmlKeys->m_strCCharMacroDrawPointKey)
	{
		pNew = new CCharMacroDrawPoint();
	}

	return pNew;
}

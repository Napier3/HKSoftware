//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//CharacteristicLib.cpp  CCharacteristicLib


#include "stdafx.h"
#include "CharacteristicLib.h"

CCharacteristicLib::CCharacteristicLib()
{
	//��ʼ������

	//��ʼ����Ա����
}

CCharacteristicLib::~CCharacteristicLib()
{
}

long CCharacteristicLib::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CCharacteristicXmlRWKeys *pXmlKeys = (CCharacteristicXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CCharacteristicLib::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CCharacteristicXmlRWKeys *pXmlKeys = (CCharacteristicXmlRWKeys*)pXmlRWKeys;

	return 0;
}

void CCharacteristicLib::InitAfterRead()
{
}

BOOL CCharacteristicLib::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CCharacteristicLib *p = (CCharacteristicLib*)pObj;

	return TRUE;
}

BOOL CCharacteristicLib::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CCharacteristicLib *p = (CCharacteristicLib*)pDest;

	return TRUE;
}

CBaseObject* CCharacteristicLib::Clone()
{
	CCharacteristicLib *p = new CCharacteristicLib();
	Copy(p);
	return p;
}

CExBaseObject* CCharacteristicLib::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CCharacteristicXmlRWKeys *pXmlKeys = (CCharacteristicXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCCharacteristicTmplateKey)
	{
		pNew = new CCharacteristicTmplate();
	}

	return pNew;
}

CExBaseObject* CCharacteristicLib::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == CHARCLASSID_CCHARACTERISTICTMPLATE)
	{
		pNew = new CCharacteristicTmplate();
	}

	return pNew;
}

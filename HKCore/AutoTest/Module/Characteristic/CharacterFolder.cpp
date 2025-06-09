//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//CharacterFolder.cpp  CCharacterFolder


#include "stdafx.h"
#include "CharacterFolder.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CCharacterFolder::CCharacterFolder()
{
	//初始化属性

	//初始化成员变量
}

CCharacterFolder::~CCharacterFolder()
{
}

long CCharacterFolder::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseList::XmlReadOwn(oNode, pXmlRWKeys);

	CCharacteristicXmlRWKeys *pXmlKeys = (CCharacteristicXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CCharacterFolder::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseList::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CCharacteristicXmlRWKeys *pXmlKeys = (CCharacteristicXmlRWKeys*)pXmlRWKeys;

	return 0;
}

void CCharacterFolder::InitAfterRead()
{
	char_CChaTmplate_to_Characteristic(this);
}

BOOL CCharacterFolder::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CCharacterFolder *p = (CCharacterFolder*)pObj;

	return TRUE;
}

BOOL CCharacterFolder::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CCharacterFolder *p = (CCharacterFolder*)pDest;

	return TRUE;
}

CBaseObject* CCharacterFolder::Clone()
{
	CCharacterFolder *p = new CCharacterFolder();
	Copy(p);
	return p;
}

CExBaseObject* CCharacterFolder::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CCharacteristicXmlRWKeys *pXmlKeys = (CCharacteristicXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCCharacteristicTmplateKey)
	{
		pNew = new CCharacteristicTmplate();
	}
	else if (strClassID == pXmlKeys->m_strCCharacterFolderKey)
	{
		pNew = new CCharacterFolder();
	}
	else if (strClassID == pXmlKeys->m_strCCharacteristicKey)
	{
		pNew = new CCharacteristic();
	}

	return pNew;
}

CExBaseObject* CCharacterFolder::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == CHARCLASSID_CCHARACTERISTICTMPLATE)
	{
		pNew = new CCharacteristicTmplate();
	}
	else if (nClassID == CHARCLASSID_CCHARFOLDER)
	{
		pNew = new CCharacterFolder();
	}
	else if (nClassID == CHARCLASSID_CCHARACTERISTIC)
	{
		pNew = new CCharacteristic();
	}

	return pNew;
}

CCharacteristic* CCharacterFolder::FindCharTempByName(const CString &strName)
{
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;
	CCharacteristic *pFind = NULL;

	while (pos != NULL)
	{
		p = (CExBaseObject *)GetNext(pos);

		if (p->GetClassID() == CHARCLASSID_CCHARACTERISTIC)
		{
			if (p->m_strName == strName)
			{
				pFind = (CCharacteristic *)p;
				break;
			}
		}
	}

	return pFind;
}

CCharacteristic* CCharacterFolder::FindCharTempByID(const CString &strID)
{
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;
	CCharacteristic *pFind = NULL;

	while (pos != NULL)
	{
		p = (CExBaseObject *)GetNext(pos);

		if (p->GetClassID() == CHARCLASSID_CCHARACTERISTICTMPLATE)
		{
			if (p->m_strID == strID)
			{
				pFind = (CCharacteristic *)p;
				break;
			}
		}
	}

	return pFind;
}

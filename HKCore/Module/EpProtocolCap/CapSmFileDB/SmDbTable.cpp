//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//SmDbTable.cpp  CSmDbTable


#include "stdafx.h"
#include "SmDbTable.h"

CSmDbTable::CSmDbTable()
{
	//��ʼ������

	//��ʼ����Ա����
}

CSmDbTable::~CSmDbTable()
{
}

long CSmDbTable::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CSmFileDBXmlRWKeys *pXmlKeys = (CSmFileDBXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CSmDbTable::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CSmFileDBXmlRWKeys *pXmlKeys = (CSmFileDBXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CSmDbTable::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
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

void CSmDbTable::InitAfterRead()
{
}

BOOL CSmDbTable::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CSmDbTable *p = (CSmDbTable*)pObj;

	return TRUE;
}

BOOL CSmDbTable::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CSmDbTable *p = (CSmDbTable*)pDest;

	return TRUE;
}

CBaseObject* CSmDbTable::Clone()
{
	CSmDbTable *p = new CSmDbTable();
	Copy(p);
	return p;
}

CExBaseObject* CSmDbTable::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CSmFileDBXmlRWKeys *pXmlKeys = (CSmFileDBXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CSmDbTable::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}

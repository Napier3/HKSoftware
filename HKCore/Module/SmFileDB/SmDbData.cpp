//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//SmDbData.cpp  CSmDbData


#include "stdafx.h"
#include "SmDbData.h"

CSmDbData::CSmDbData()
{
	//��ʼ������

	//��ʼ����Ա����
}

CSmDbData::~CSmDbData()
{
}

long CSmDbData::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CSmFileDBXmlRWKeys *pXmlKeys = (CSmFileDBXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CSmDbData::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CSmFileDBXmlRWKeys *pXmlKeys = (CSmFileDBXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CSmDbData::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CSmDbData::InitAfterRead()
{
}

BOOL CSmDbData::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CSmDbData *p = (CSmDbData*)pObj;

	return TRUE;
}

BOOL CSmDbData::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CSmDbData *p = (CSmDbData*)pDest;

	return TRUE;
}

CBaseObject* CSmDbData::Clone()
{
	CSmDbData *p = new CSmDbData();
	Copy(p);
	return p;
}


//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//EpCapGenDatas.cpp  CEpCapGenDatas


#include "stdafx.h"
#include "EpCapGenDatas.h"

CEpCapGenDatas::CEpCapGenDatas()
{
	//��ʼ������

	//��ʼ����Ա����
}

CEpCapGenDatas::~CEpCapGenDatas()
{
}

long CEpCapGenDatas::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CEpCapDatasGeneratorXmlRWKeys *pXmlKeys = (CEpCapDatasGeneratorXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CEpCapGenDatas::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CEpCapDatasGeneratorXmlRWKeys *pXmlKeys = (CEpCapDatasGeneratorXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CEpCapGenDatas::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CEpCapGenDatas::InitAfterRead()
{
}

BOOL CEpCapGenDatas::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CEpCapGenDatas *p = (CEpCapGenDatas*)pObj;

	return TRUE;
}

BOOL CEpCapGenDatas::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CEpCapGenDatas *p = (CEpCapGenDatas*)pDest;

	return TRUE;
}

CBaseObject* CEpCapGenDatas::Clone()
{
	CEpCapGenDatas *p = new CEpCapGenDatas();
	Copy(p);
	return p;
}

BOOL CEpCapGenDatas::CanPaste(UINT nClassID)
{
	if (nClassID == ECGCLASSID_CEPCAPGENDATA)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CEpCapGenDatas::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CEpCapDatasGeneratorXmlRWKeys *pXmlKeys = (CEpCapDatasGeneratorXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCEpCapGenDataKey)
	{
		pNew = new CEpCapGenData();
	}

	return pNew;
}

CExBaseObject* CEpCapGenDatas::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == ECGCLASSID_CEPCAPGENDATA)
	{
		pNew = new CEpCapGenData();
	}

	return pNew;
}

//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//GbCharAxises.cpp  CGbCharAxises


#include "stdafx.h"
#include "GbCharAxises.h"

CGbCharAxises::CGbCharAxises()
{
	//��ʼ������

	//��ʼ����Ա����
}

CGbCharAxises::~CGbCharAxises()
{
}

long CGbCharAxises::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CGbCharDefMngrXmlRWKeys *pXmlKeys = (CGbCharDefMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CGbCharAxises::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CGbCharDefMngrXmlRWKeys *pXmlKeys = (CGbCharDefMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CGbCharAxises::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

BOOL CGbCharAxises::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CGbCharAxises *p = (CGbCharAxises*)pObj;

	return TRUE;
}

BOOL CGbCharAxises::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CGbCharAxises *p = (CGbCharAxises*)pDest;

	return TRUE;
}

CBaseObject* CGbCharAxises::Clone()
{
	CGbCharAxises *p = new CGbCharAxises();
	Copy(p);
	return p;
}

CExBaseObject* CGbCharAxises::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CGbCharDefMngrXmlRWKeys *pXmlKeys = (CGbCharDefMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCGbCharAxisKey)
	{
		pNew = new CGbCharAxis();
	}

	return pNew;
}

CExBaseObject* CGbCharAxises::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == CHRCLASSID_CGBCHARAXIS)
	{
		pNew = new CGbCharAxis();
	}

	return pNew;
}

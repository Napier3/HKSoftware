//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//GbCharPLine.cpp  CGbCharPLine


#include "stdafx.h"
#include "GbCharPLine.h"

CGbCharPLine::CGbCharPLine()
{
	//��ʼ������

	//��ʼ����Ա����
}

CGbCharPLine::~CGbCharPLine()
{
}

long CGbCharPLine::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CGbCharLine::XmlReadOwn(oNode, pXmlRWKeys);
	CGbCharDefMngrXmlRWKeys *pXmlKeys = (CGbCharDefMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CGbCharPLine::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CGbCharLine::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CGbCharDefMngrXmlRWKeys *pXmlKeys = (CGbCharDefMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CGbCharPLine::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CGbCharLine::SerializeOwn(oBinaryBuffer);
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

BOOL CGbCharPLine::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CGbCharLine::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CGbCharPLine *p = (CGbCharPLine*)pObj;

	return TRUE;
}

BOOL CGbCharPLine::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CGbCharLine::CopyOwn(pDest);

	CGbCharPLine *p = (CGbCharPLine*)pDest;

	return TRUE;
}

CBaseObject* CGbCharPLine::Clone()
{
	CGbCharPLine *p = new CGbCharPLine();
	Copy(p);
	return p;
}


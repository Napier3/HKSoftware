//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//GbCharPLiner.cpp  CGbCharPLiner


#include "stdafx.h"
#include "GbCharPLiner.h"

CGbCharPLiner::CGbCharPLiner()
{
	//��ʼ������

	//��ʼ����Ա����
}

CGbCharPLiner::~CGbCharPLiner()
{
}

long CGbCharPLiner::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CGbCharLiner::XmlReadOwn(oNode, pXmlRWKeys);
	CGbCharDefMngrXmlRWKeys *pXmlKeys = (CGbCharDefMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CGbCharPLiner::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CGbCharLiner::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CGbCharDefMngrXmlRWKeys *pXmlKeys = (CGbCharDefMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CGbCharPLiner::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CGbCharLiner::SerializeOwn(oBinaryBuffer);
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

BOOL CGbCharPLiner::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CGbCharLiner::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CGbCharPLiner *p = (CGbCharPLiner*)pObj;

	return TRUE;
}

BOOL CGbCharPLiner::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CGbCharLiner::CopyOwn(pDest);

	CGbCharPLiner *p = (CGbCharPLiner*)pDest;

	return TRUE;
}

CBaseObject* CGbCharPLiner::Clone()
{
	CGbCharPLiner *p = new CGbCharPLiner();
	Copy(p);
	return p;
}


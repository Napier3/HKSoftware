//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//GbCharFunc.cpp  CGbCharFunc


#include "stdafx.h"
#include "GbCharFunc.h"

CGbCharFunc::CGbCharFunc()
{
	//��ʼ������

	//��ʼ����Ա����
}

CGbCharFunc::~CGbCharFunc()
{
}

long CGbCharFunc::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CGbCharDefMngrXmlRWKeys *pXmlKeys = (CGbCharDefMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CGbCharFunc::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CGbCharDefMngrXmlRWKeys *pXmlKeys = (CGbCharDefMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CGbCharFunc::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

BOOL CGbCharFunc::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CGbCharFunc *p = (CGbCharFunc*)pObj;

	return TRUE;
}

BOOL CGbCharFunc::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CGbCharFunc *p = (CGbCharFunc*)pDest;

	return TRUE;
}

CBaseObject* CGbCharFunc::Clone()
{
	CGbCharFunc *p = new CGbCharFunc();
	Copy(p);
	return p;
}

CExBaseObject* CGbCharFunc::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CGbCharDefMngrXmlRWKeys *pXmlKeys = (CGbCharDefMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCGbChar_y_f_xKey)
	{
		pNew = new CGbChar_y_f_x();
	}

	return pNew;
}

CExBaseObject* CGbCharFunc::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == CHRCLASSID_CGBCHAR_Y_F_X)
	{
		pNew = new CGbChar_y_f_x();
	}

	return pNew;
}

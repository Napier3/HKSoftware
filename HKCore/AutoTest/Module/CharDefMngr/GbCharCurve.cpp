//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//GbCharCurve.cpp  CGbCharCurve


#include "stdafx.h"
#include "GbCharCurve.h"

CGbCharCurve::CGbCharCurve()
{
	//��ʼ������

	//��ʼ����Ա����
}

CGbCharCurve::~CGbCharCurve()
{
}

long CGbCharCurve::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CGbCharDefMngrXmlRWKeys *pXmlKeys = (CGbCharDefMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CGbCharCurve::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CGbCharDefMngrXmlRWKeys *pXmlKeys = (CGbCharDefMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CGbCharCurve::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

BOOL CGbCharCurve::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CGbCharCurve *p = (CGbCharCurve*)pObj;

	return TRUE;
}

BOOL CGbCharCurve::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CGbCharCurve *p = (CGbCharCurve*)pDest;

	return TRUE;
}

CBaseObject* CGbCharCurve::Clone()
{
	CGbCharCurve *p = new CGbCharCurve();
	Copy(p);
	return p;
}

CExBaseObject* CGbCharCurve::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CGbCharDefMngrXmlRWKeys *pXmlKeys = (CGbCharDefMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCGbCharArcKey)
	{
		pNew = new CGbCharArc();
	}
	else if (strClassID == pXmlKeys->m_strCGbCharLineKey)
	{
		pNew = new CGbCharLine();
	}
	else if (strClassID == pXmlKeys->m_strCGbCharLinerKey)
	{
		pNew = new CGbCharLiner();
	}
	else if (strClassID == pXmlKeys->m_strCGbCharLinesKey)
	{
		pNew = new CGbCharLines();
	}
	else if (strClassID == pXmlKeys->m_strCGbCharPArcKey)
	{
		pNew = new CGbCharPArc();
	}
	else if (strClassID == pXmlKeys->m_strCGbCharPLineKey)
	{
		pNew = new CGbCharPLine();
	}
	else if (strClassID == pXmlKeys->m_strCGbCharPLinerKey)
	{
		pNew = new CGbCharPLiner();
	}
	else if (strClassID == pXmlKeys->m_strCGbCharPLinesKey)
	{
		pNew = new CGbCharPLines();
	}

	return pNew;
}

CExBaseObject* CGbCharCurve::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == CHRCLASSID_CGBCHARARC)
	{
		pNew = new CGbCharArc();
	}
	else if (nClassID == CHRCLASSID_CGBCHARLINE)
	{
		pNew = new CGbCharLine();
	}
	else if (nClassID == CHRCLASSID_CGBCHARLINER)
	{
		pNew = new CGbCharLiner();
	}
	else if (nClassID == CHRCLASSID_CGBCHARLINES)
	{
		pNew = new CGbCharLines();
	}
	else if (nClassID == CHRCLASSID_CGBCHARPARC)
	{
		pNew = new CGbCharPArc();
	}
	else if (nClassID == CHRCLASSID_CGBCHARPLINE)
	{
		pNew = new CGbCharPLine();
	}
	else if (nClassID == CHRCLASSID_CGBCHARPLINER)
	{
		pNew = new CGbCharPLiner();
	}
	else if (nClassID == CHRCLASSID_CGBCHARPLINES)
	{
		pNew = new CGbCharPLines();
	}

	return pNew;
}

//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//AtsSvrTestAppEx.cpp  CAtsSvrTestAppEx


#include "stdafx.h"
#include "AtsSvrTestAppEx.h"

CAtsSvrTestAppEx::CAtsSvrTestAppEx()
{
	//初始化属性

	//初始化成员变量
}

CAtsSvrTestAppEx::~CAtsSvrTestAppEx()
{
}

long CAtsSvrTestAppEx::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CAtsSvrRsTestApp::XmlReadOwn(oNode, pXmlRWKeys);
	CAtsServiceXmlRWKeys *pXmlKeys = (CAtsServiceXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CAtsSvrTestAppEx::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CAtsSvrRsTestApp::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CAtsServiceXmlRWKeys *pXmlKeys = (CAtsServiceXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CAtsSvrTestAppEx::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CAtsSvrRsTestApp::SerializeOwn(oBinaryBuffer);
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

void CAtsSvrTestAppEx::InitAfterRead()
{
}

BOOL CAtsSvrTestAppEx::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CAtsSvrRsTestApp::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CAtsSvrTestAppEx *p = (CAtsSvrTestAppEx*)pObj;

	return TRUE;
}

BOOL CAtsSvrTestAppEx::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CAtsSvrRsTestApp::CopyOwn(pDest);

	CAtsSvrTestAppEx *p = (CAtsSvrTestAppEx*)pDest;

	return TRUE;
}

CBaseObject* CAtsSvrTestAppEx::Clone()
{
	CAtsSvrTestAppEx *p = new CAtsSvrTestAppEx();
	Copy(p);
	return p;
}

BOOL CAtsSvrTestAppEx::CanPaste(UINT nClassID)
{
	if (nClassID == ATSVRCLASSID_CATSSVRRSTESTAPPREF)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CAtsSvrTestAppEx::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CAtsServiceXmlRWKeys *pXmlKeys = (CAtsServiceXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCAtsSvrRsTestAppRefKey)
	{
		pNew = new CAtsSvrRsTestAppRef();
	}

	return pNew;
}

CExBaseObject* CAtsSvrTestAppEx::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == ATSVRCLASSID_CATSSVRRSTESTAPPREF)
	{
		pNew = new CAtsSvrRsTestAppRef();
	}

	return pNew;
}

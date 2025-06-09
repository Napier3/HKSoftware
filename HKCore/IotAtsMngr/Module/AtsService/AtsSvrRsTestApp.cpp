//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//AtsSvrRsTestApp.cpp  CAtsSvrRsTestApp


#include "stdafx.h"
#include "AtsSvrRsTestApp.h"

CAtsSvrRsTestApp::CAtsSvrRsTestApp()
{
	//初始化属性

	//初始化成员变量
}

CAtsSvrRsTestApp::~CAtsSvrRsTestApp()
{
}

long CAtsSvrRsTestApp::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CAtsServiceXmlRWKeys *pXmlKeys = (CAtsServiceXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strTypeKey, oNode, m_strtype);
	return 0;
}

long CAtsSvrRsTestApp::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CAtsServiceXmlRWKeys *pXmlKeys = (CAtsServiceXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strTypeKey, oElement, m_strtype);
	return 0;
}

long CAtsSvrRsTestApp::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strtype);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strtype);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strtype);
	}
	return 0;
}

void CAtsSvrRsTestApp::InitAfterRead()
{
}

BOOL CAtsSvrRsTestApp::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CAtsSvrRsTestApp *p = (CAtsSvrRsTestApp*)pDest;

	p->m_strtype = m_strtype;
	return TRUE;
}

BOOL CAtsSvrRsTestApp::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CAtsSvrRsTestApp *p = (CAtsSvrRsTestApp*)pObj;

	if(m_strtype != p->m_strtype)
	{
		return FALSE;
	}

	return TRUE;
}

CBaseObject* CAtsSvrRsTestApp::Clone()
{
	CAtsSvrRsTestApp *p = new CAtsSvrRsTestApp();
	Copy(p);
	return p;
}


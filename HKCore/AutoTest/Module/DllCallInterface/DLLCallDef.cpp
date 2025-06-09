//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//DLLCall.cpp  CDllCallDef


#include "stdafx.h"
#include "DLLCallDef.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CDllCallDef::CDllCallDef()
{
	//初始化属性

	//初始化成员变量
}

CDllCallDef::~CDllCallDef()
{
}

long CDllCallDef::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CDllCallXmlRWKeys *pXmlKeys = (CDllCallXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strProgidKey, oNode, m_strProgid);
	return 0;
}

long CDllCallDef::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CDllCallXmlRWKeys *pXmlKeys = (CDllCallXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strProgidKey, oElement, m_strProgid);
	return 0;
}

long CDllCallDef::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strProgid);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strProgid);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strProgid);
	}
	return 0;
}

void CDllCallDef::InitAfterRead()
{
}

BOOL CDllCallDef::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CDllCallDef *p = (CDllCallDef*)pObj;

	if(m_strProgid != p->m_strProgid)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CDllCallDef::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CDllCallDef *p = (CDllCallDef*)pDest;

	p->m_strProgid = m_strProgid;
	return TRUE;
}

CBaseObject* CDllCallDef::Clone()
{
	CDllCallDef *p = new CDllCallDef();
	Copy(p);
	return p;
}

BOOL CDllCallDef::CanPaste(UINT nClassID)
{
	if (nClassID == DLCLCLASSID_CDLLFUNCTION)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CDllCallDef::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CDllCallXmlRWKeys *pXmlKeys = (CDllCallXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCDLLFunctionKey)
	{
		pNew = new CDLLFunction();
	}

	return pNew;
}

CExBaseObject* CDllCallDef::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == DLCLCLASSID_CDLLFUNCTION)
	{
		pNew = new CDLLFunction();
	}

	return pNew;
}
